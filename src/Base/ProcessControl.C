//******************************************************************************
/*!
  \file      src/Base/ProcessControl.h
  \author    J. Bakosi
  \date      Tue 24 Mar 2015 02:13:31 PM MDT
  \copyright 2012-2015, Jozsef Bakosi.
  \brief     POSIX process control wrapper definitions
  \details   POSIX process control wrapper definitions.
*/
//******************************************************************************

#include <string>
#include <vector>

#if defined(__clang__) || defined(__GNUC__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wconversion"
#endif

#include <pstreams/pstream.h>

#if defined(__clang__) || defined(__GNUC__)
  #pragma GCC diagnostic pop
#endif

#include <ProcessControl.h>
#include <Exception.h>

namespace tk {

//******************************************************************************
//  Remove file from file system
//! \param[in] file File name to delete (shell wildcards NOT expanded)
//! \details Since we use pstream's basic_ipstream constructor with signature
//!   ( const std::string & file, const argv_type & argv, pmode mode = pstdout )
//!   and the file argument doesn't contain a slash, the actions of the shell
//!   are duplicated in searching for an executable in PATH. The shell will not
//!   interpret the other arguments, so wildcard expansion will not take place.
//! \author J. Bakosi
//******************************************************************************
void rm( const std::string& file ) {
  std::vector< std::string > argv;
  argv.push_back( "rm" );
  argv.push_back( file );
  redi::ipstream in( "rm", argv, redi::pstreambuf::pstderr );
  std::string e;
  std::string error;
  while ( std::getline( in, e ) ) error += e + '\n';
  if (!error.empty()) Throw( std::move(error) );
}

} // tk::