// *****************************************************************************
/*!
  \file      src/NoWarning/HYPRE_krylov.h
  \author    J. Bakosi
  \date      Tue 10 May 2016 10:01:51 AM MDT
  \copyright 2012-2015, Jozsef Bakosi, 2016, Los Alamos National Security, LLC.
  \brief     Include HYPRE_krylov.h with turning off specific compiler
             warnings
*/
// *****************************************************************************
#ifndef nowarning_HYPRE_krylov_h
#define nowarning_HYPRE_krylov_h

#if defined(__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wdocumentation-unknown-command"
#endif

#include <HYPRE_krylov.h>

#if defined(__clang__)
  #pragma clang diagnostic pop
#endif

#endif // nowarning_HYPRE_krylov_h
