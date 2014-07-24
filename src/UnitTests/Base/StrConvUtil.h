//******************************************************************************
/*!
  \file      src/UnitTests/Base/StrConvUtil.h
  \author    J. Bakosi
  \date      Thu 24 Jul 2014 09:05:28 AM MDT
  \copyright 2005-2014, Jozsef Bakosi.
  \brief     Unit tests for Base/StrConvUtil.h
  \details   Unit tests for Base/StrConvUtil.h
*/
//******************************************************************************
#ifndef test_StrConvUtil_h
#define test_StrConvUtil_h

#include <tut/tut.hpp>
#include <StrConvUtil.h>

namespace tut {

//! All tests in group inherited from this base
struct StrConvUtil_common {};

//! Test group shortcuts
using StrConvUtil_group = test_group< StrConvUtil_common >;
using StrConvUtil_object = StrConvUtil_group::object;

//! Define test group
StrConvUtil_group StrConvUtil( "Base/StrConvUtil" );

//! Test definitions for group

//! Test tk::operator<< used for writing enum class value to output stream
template<> template<>
void StrConvUtil_object::test< 1 >() {
  set_test_name( "tk::operator<<( enum class ) casting to unsigned int" );

  enum class Enum { FIRST=3, SECOND, THIRD };
  using tk::operator<<;
  std::stringstream ss;
  ss << Enum::FIRST;
  ensure_equals( "enum class first item output to stream", ss.str(), "3" );
  ss.str("");
  ss << Enum::SECOND;
  ensure_equals( "enum class second item output to stream", ss.str(), "4" );
  ss.str("");
  ss << Enum::THIRD;
  ensure_equals( "enum class third item output to stream", ss.str(), "5" );
}

//! Test tk::operator<< used for writing non-enum-class to output stream
template<> template<>
void StrConvUtil_object::test< 2 >() {
  set_test_name( "tk::operator<<( non-enum-class )" );

  using tk::operator<<;
  std::stringstream ss;
  ss << "blah";
  ensure_equals( "non-enum-class item output to stream", ss.str(), "blah" );
}

//! Test tk::operator<< used for concatenating to std::basic_string
template<> template<>
void StrConvUtil_object::test< 3 >() {
  set_test_name( "tk::operator<<( std::basic_string )" );

  using tk::operator<<;
  std::string s;
  s << 123;
  ensure_equals( "concatenating integer to std::string", s, "123" );
  s << 3.14;
  ensure_equals( "concatenating double to std::string", s, "1233.14" );
  s << " blah";
  ensure_equals( "concatenating const char* to std::string",
                 s, "1233.14 blah" );
  s << std::string("string");
  ensure_equals( "concatenating const char* to std::string",
                 s, "1233.14 blahstring" );
  s = "";
  ensure_equals( "std::string empty after concatenations", s.size(), 0UL );
}

//! Test tk::operator+ used for concatenating to std::basic_string
template<> template<>
void StrConvUtil_object::test< 4 >() {
  set_test_name( "tk::operator+( std::basic_string )" );

  using tk::operator+;
  std::string s;
  s + 123;
  ensure_equals( "concatenating integer to std::string", s, "123" );
  s + 3.14;
  ensure_equals( "concatenating double to std::string", s, "1233.14" );
  s + " blah";
  ensure_equals( "concatenating const char* to std::string",
                 s, "1233.14 blah" );
  s = "";
  ensure_equals( "std::string empty after concatenations", s.size(), 0UL );
}

} // tut::

#endif // test_StrConvUtil_h
