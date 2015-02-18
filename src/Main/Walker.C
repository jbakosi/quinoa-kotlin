//******************************************************************************
/*!
  \file      src/Main/Walker.C
  \author    J. Bakosi
  \date      Wed 28 Jan 2015 11:18:59 AM MST
  \copyright 2012-2015, Jozsef Bakosi.
  \brief     Random walker Charm++ main chare
  \details   Random walker Charm++ main chare. This file contains the definition
    of the Charm++ main chare, equivalent to main() in Charm++-land.
*/
//******************************************************************************

#include <pup_stl.h>

#include <Config.h>
#include <RNG.h>
#include <RNGStack.h>
#include <DiffEqStack.h>
#include <WalkerPrint.h>
#include <WalkerDriver.h>
#include <Walker/CmdLine/Parser.h>
#include <walker.decl.h>
#include <Init.h>

//! \brief Charm handle to the main proxy, facilitates call-back to finalize,
//!    etc., must be in global scope, unique per executable
CProxy_Main mainProxy;

//! Walker declarations and definitions
namespace walker {

//! Global-scope data. Initialized by the main chare and distibuted to all PEs
//! by the Charm++ runtime system. Though semantically not const, all these
//! global data should be considered read-only. See also
//! http://charm.cs.illinois.edu/manuals/html/charm++/manual.html. The data
//! below is global-scope because they must be available to all PEs which could
//! be on different machines.

//! Defaults of input deck, facilitates detection what is set by user
ctr::InputDeck g_inputdeck_defaults;
//! Input deck filled by parser, containing all input data
ctr::InputDeck g_inputdeck;
//! Random number generators selected by user
std::map< tk::ctr::RawRNGType, tk::RNG > g_rng;
//! Differential equations selected by user
std::vector< DiffEq > g_diffeqs;

//! Distributor Charm++ proxy facilitating call-back to Distributor by the
//! individual integrators
CProxy_Distributor g_DistributorProxy;

//! Pack/Unpack selected RNGs. This Pack/Unpack method (re-)creates the full RNG
//! stack since it needs to (re-)bind function pointers on different processing
//! elements. Therefore we circumvent Charm's usual pack/unpack for this type,
//! and thus sizing does not make sense: sizing is a no-op. We could initialize
//! the stack in RNGTestDriver's constructor and let this function re-create the
//! stack only when unpacking, but that leads to repeating the same code twice:
//! once in RNGTestDriver's constructor, once here. Another option is to use
//! this pack/unpack routine to both initially create (when packing) and to
//! re-create (when unpacking) the stack, which eliminates the need for
//! pre-creating the object in RNGTestDriver's constructor and therefore
//! eliminates the repeated code. This explains the guard for sizing: the code
//! below is called for packing only (in serial) and packing and unpacking (in
//! parallel).
inline
void operator|( PUP::er& p, std::map< tk::ctr::RawRNGType, tk::RNG >& rng ) {
  if (!p.isSizing()) {
    tk::RNGStack stack(
      #ifdef HAS_MKL
      g_inputdeck.get< tag::param, tag::rngmkl >(),
      #endif
      g_inputdeck.get< tag::param, tag::rngsse >() );
    rng = stack.selected( g_inputdeck.get< tag::selected, tag::rng >() );
  }
}

//! Pack/Unpack selected differential equations. This Pack/Unpack method
//! (re-)creates the DiffEq factory since it needs to (re-)bind function
//! pointers on different processing elements. Therefore we circumvent Charm's
//! usual pack/unpack for this type, and thus sizing does not make sense: sizing
//! is a no-op. We could initialize the factory in WalkerDriver's constructor
//! and let this function re-create the stack only when unpacking, but that
//! leads to repeating the same code twice: once in WalkerDriver's constructor,
//! once here. Another option is to use this pack/unpack routine to both
//! initially create (when packing) and to re-create (when unpacking) the
//! factory, which eliminates the need for pre-creating the object in
//! WalkerDriver's constructor and therefore eliminates the repeated code. This
//! explains the guard for sizing: the code below is called for packing only (in
//! serial) and packing and unpacking (in parallel).
inline
void operator|( PUP::er& p, std::vector< DiffEq >& eqs ) {
  if (!p.isSizing()) eqs = DiffEqStack().selected();
}

} // walker::

//! \brief Charm++ main chare for the random walker executable, walker.
//! \details Note that this object should not be in a namespace.
class Main : public CBase_Main {

  public:
    //! \brief Constructor
    //! \details The main chare constructor is the main entry point of the
    //!   program, called by the Charm++ runtime system. The constructor does
    //!   basic initialization steps, e.g., parser the command-line, prints out
    //!   some useful information to screen (in verbose mode), and instantiates
    //!   a driver. Since Charm++ is fully asynchronous, the constructure
    //!   usually spawns asynchronous objects and immediately exits. Thus in the
    //!   body of the main chare constructor we fire up an 'execute' chare,
    //!   which then calls back to Main::execute(). Finishing the main chare
    //!   constructor the Charm++ runtime system then starts the
    //!   network-migration of all global-scope data (if any). The execute chare
    //!   calling back to Main::execute() signals the end of the migration of
    //!   the global-scope data. Then we are ready to execute the driver. Since
    //!   the random walker is parallel and asynchronous, its driver fires up
    //!   additional Charm++ chare objects which then call back to
    //!   Main::finalize() at some point in the future when all work has been
    //!   finished. finalize() then exits by calling Charm++'s CkExit(),
    //!   shutting down the runtime system.
    //! \see http://charm.cs.illinois.edu/manuals/html/charm++/manual.html
    Main( CkArgMsg* msg )
    try :
      // Parse command line into m_cmdline using default simple pretty printer
      m_cmdParser( msg->argc, msg->argv, tk::Print(), m_cmdline ),
      // Create pretty printer initializing output streams based on command line
      m_print( m_cmdline.get< tag::verbose >() ? std::cout : std::clog ),
      // Create Walker driver
      m_driver( tk::Main< walker::WalkerDriver >
                        ( msg->argc, msg->argv,
                          m_cmdline,
                          tk::HeaderType::WALKER,
                          WALKER_EXECUTABLE,
                          m_print ) ),
      m_timer(1)        // Start new timer measuring the total runtime
    {
      delete msg;
      mainProxy = thisProxy;
      // Fire up an asynchronous execute object, which when created at some
      // future point in time will call back to this->execute(). This is
      // necessary so that this->execute() can access already migrated
      // global-scope data.
      CProxy_execute::ckNew();
      // Start new timer measuring the migration of global-scope data
      m_timer.emplace_back();
    } catch (...) { processException(); }

    //! Execute driver created and initialized by constructor
    void execute() {
      m_timestamp.emplace("Migration of global-scope data", m_timer[1].hms());
      m_driver.execute();       // fires up async chares
    }

    //! Normal exit point
    void finalize() {
      if (!m_timer.empty()) {
        m_timestamp.emplace( "Total runtime", m_timer[0].hms() );
        m_print.time( "Timers (h:m:s)", m_timestamp );
        m_print.endpart();
      }
      CkExit();
    }

    //! Add time stamp contributing to final timers output
    void timestamp( std::string label, tk::real stamp )
    { m_timestamp.emplace( label, tk::hms( stamp ) ); }

    //! Process an exception
    void processException() {
      try {
        throw;      // rethrow exception to deal with it here
      }
        // Catch our exceptions
        catch ( tk::Exception& qe ) {
          qe.handleException();
        }
        // Catch std::exception and transform it into Exception without
        // file:line:func information
        catch ( std::exception& se ) {
          tk::Exception qe( se.what() );
          qe.handleException();
        }
        // Catch uncaught exception
        catch (...) {
          tk::Exception qe( "Non-standard exception" );
          qe.handleException();
        }

      // Tell the runtime system to exit
      finalize();
    }

  private:
    walker::ctr::CmdLine m_cmdline;                   //!< Command line
    walker::CmdLineParser m_cmdParser;                //!< Command line parser
    walker::WalkerPrint m_print;                      //!< Pretty printer
    walker::WalkerDriver m_driver;                    //!< Driver
    std::vector< tk::Timer > m_timer;                 //!< Timers

    //! Time stamps in h:m:s with labels
    std::map< std::string, tk::Timer::Watch > m_timestamp;
};

//! Charm++ chare execute: by the time this object is constructed, the Charm++
//! runtime system has finished migrating all global-scoped read-only objects
//! which happens after the main chare constructor has finished.
struct execute : CBase_execute { execute() { mainProxy.execute(); } };

#include <walker.def.h>