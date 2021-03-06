// *****************************************************************************
/*!
  \file      src/NoWarning/optional.h
  \author    J. Bakosi
  \date      Fri 30 Sep 2016 12:43:50 PM MDT
  \copyright 2012-2015, Jozsef Bakosi, 2016, Los Alamos National Security, LLC.
  \brief     Include boost/optional.hpp with turning off specific
             compiler warnings
*/
// *****************************************************************************
#ifndef nowarning_optional_h
#define nowarning_optional_h

#if defined(__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wundef"
#elif defined(__GNUC__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#elif defined(__INTEL_COMPILER)
  #pragma warning( push )
  #pragma warning( disable: 367 )
#endif

#include <boost/optional.hpp>

#if defined(__clang__)
  #pragma clang diagnostic pop
#elif defined(__GNUC__)
  #pragma GCC diagnostic pop
#elif defined(__INTEL_COMPILER)
  #pragma warning( pop )
#endif

#endif // nowarning_optional_h
