//******************************************************************************
/*!
  \file      src/Main/InciterPrint.C
  \author    J. Bakosi
  \date      Mon 23 Feb 2015 08:59:07 AM MST
  \copyright 2012-2015, Jozsef Bakosi.
  \brief     Inciter-specific pretty printer functionality
  \details   Inciter-specific pretty printer functionality.
*/
//******************************************************************************

#include <InciterPrint.h>

using inciter::InciterPrint;

void
InciterPrint::inthead( const std::string& title,
                       const std::string& name,
                       const std::string& legend,
                       const std::string& head ) const
//******************************************************************************
//  Print time integration header
//! \param[in] title Section title
//! \param[in] name Section name
//! \param[in] legend Legend to print
//! \param[in] head Head to append
//! \author J. Bakosi
//******************************************************************************
{
  section( title, name );
  std::string l( legend );
  boost::replace_all( l, "\n", "\n" + m_item_indent );
  raw( m_item_indent + l + head );
}