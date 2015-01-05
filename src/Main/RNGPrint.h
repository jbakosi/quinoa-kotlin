//******************************************************************************
/*!
  \file      src/Main/RNGPrint.h
  \author    J. Bakosi
  \date      Wed 17 Dec 2014 04:43:22 PM MST
  \copyright 2012-2014, Jozsef Bakosi.
  \brief     Printer with RNGs
  \details   Printer with RNGs
*/
//******************************************************************************
#ifndef RNGPrint_h
#define RNGPrint_h

#include <Print.h>
#include <RNGParam.h>
#include <Options/RNG.h>

namespace tk {

//! RNGPrint : Print
class RNGPrint : public Print {

  public:
    //! Constructor
    explicit RNGPrint( std::ostream& str = std::clog,
                       std::ostream& qstr = std::cout ) : Print( str, qstr ) {}

    #ifdef HAS_MKL
    //! Print all fields of MKL RNG parameters
    void MKLParams( const std::vector< ctr::RNGType >& vec,
                    const ctr::RNGMKLParameters& map ) const;
    #endif

    //! Print all fields of RNGSSE parameters
    void RNGSSEParams( const std::vector< ctr::RNGType >& vec,
                       const ctr::RNGSSEParameters& map ) const;

  private:
    #ifdef HAS_MKL
    //! Echo information on MKL random number generator
    void echoMKLParams( const ctr::RNGMKLParam& p ) const;
    #endif

    //! Echo information on RNGSSE random number generator
    void echoRNGSSEParams( const ctr::RNGSSEParam& p,
                           const ctr::RNG& rng,
                           const ctr::RNGType& r ) const;
};

} // tk::

#endif // RNGPrint_h
