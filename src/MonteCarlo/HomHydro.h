//******************************************************************************
/*!
  \file      src/MonteCarlo/HomHydro.h
  \author    J. Bakosi
  \date      Sat 25 Jan 2014 05:45:24 PM MST
  \copyright Copyright 2005-2012, Jozsef Bakosi, All rights reserved.
  \brief     Homogeneous hydrodynamics
  \details   Homogeneous hydrodynamics
*/
//******************************************************************************
#ifndef HomHydro_h
#define HomHydro_h

#include <Physics.h>

namespace quinoa {

//! HomHydro : Physics
class HomHydro : public Physics {

  public:
    //! Constructor
    explicit HomHydro(const Base& base);

    //! Destructor
    ~HomHydro() override = default;

    //! Run
    void run() override;

  private:
    //! Don't permit copy constructor
    HomHydro(const HomHydro&) = delete;
    //! Don't permit copy assigment
    HomHydro& operator=(const HomHydro&) = delete;
    //! Don't permit move constructor
    HomHydro(HomHydro&&) = delete;
    //! Don't permit move assigment
    HomHydro& operator=(HomHydro&&) = delete;
    
    //! One-liner report
    void reportHeader();
    void report(const uint64_t it,
                const uint64_t nstep,
                const tk::real t,
                const tk::real dt,
                const bool wroteJpdf,
                const bool wroteGlob,
                const bool wroteStat);

    //! Advance
    void advance(tk::real dt);

    //! Output joint PDF
    void outJpdf(const tk::real t);
};

} // quinoa::

#endif // HomHydro_h