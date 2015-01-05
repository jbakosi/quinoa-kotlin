//******************************************************************************
/*!
  \file      src/Control/StatControl.h
  \author    J. Bakosi
  \date      Fri 16 Jan 2015 12:35:18 PM MST
  \copyright 2012-2014, Jozsef Bakosi.
  \brief     Types and associated functions to deal with moments and PDFs
  \details   Types and associated functions to deal with statistical moments and
    probability density functions.
*/
//******************************************************************************
#ifndef StatControl_h
#define StatControl_h

#include <Types.h>
#include <Exception.h>

namespace tk {
namespace ctr {

//! \brief Moment specifies which type of moment is computed for a quantity in
//!    a Term
//! \author J. Bakosi
enum class Moment : uint8_t { ORDINARY=0,      //!< Full variable
                              CENTRAL          //!< Fluctuation
};

//! \brief Term is a Moment of a quantity with a field ID to be ensemble
//!    averaged
//! \details Internally the numbering of field IDs starts from 0, but presented
//!    to the user, e.g., in screen-output, as starting from 1.
//! \author J. Bakosi
struct Term {
  int field;         //!< Field ID
  Moment moment;     //!< Moment type: ordinary, central
  char var;          //!< Dependent variable
  bool plot;         //!< Indicates whether the variable will be plotted
  // Conceptually, plot should be in Product, since plot will only be false for
  // a mean that was triggered by a central moment by one of the Terms of a
  // Product requesting the mean or a model. However, that would require
  // Product to be a vector< struct >, which then would need custom comparitors
  // for std::sort() and std::unique(), etc., in, e.g, Parser::unique(). Since
  // this is not a performance issue, plot is here, redundantly, in Term.

  /** @name Pack/Unpack: Serialize Term object for Charm++ */
  ///@{
  //! Pack/Unpack serialize member function
  //! \param[inout] p Charm++'s PUP::er serializer object reference
  //! \author J. Bakosi
  void pup( PUP::er& p ) {
    p | field;
    PUP::pup( p, moment );
    p | var;
    p | plot;
  }
  //! \brief Pack/Unpack serialize operator|
  //! \param[inout] p Charm++'s PUP::er serializer object reference
  //! \param[inout] t Term object reference
  //! \author J. Bakosi
  friend void operator|( PUP::er& p, Term& t ) { t.pup(p); } 
  ///@}

  //! \brief Default (empty) constructor for Charm++
  //! \author J. Bakosi
  explicit Term() : field(0), moment(Moment::ORDINARY), var(0), plot(false) {}

  //! \brief Constructor: initialize all state data
  //! \param[in] f Field ID
  //! \param[in] m Moment type enum: Moment::ORDINARY or Moment::CENTRAL
  //! \param[in] v Dependent variable
  //! \param[in] p Indicates whether the variable will be plotted
  //! \author J. Bakosi
  explicit Term( int f, Moment m, char v, bool p ) :
    field( f ), moment( m ), var( v ), plot( p ) {}

  //! \brief Equal operator for, e.g., finding unique elements, used by, e.g.,
  //!    std::unique().
  //! \details Test on field, moment, and var, but ignore plot.
  //! \param[in] term Term to compare
  //! \return Boolean indicating if term is equal to 'this'
  //! \author J. Bakosi
  bool operator== ( const Term& term ) const {
    if (field == term.field && moment == term.moment && var == term.var)
      return true;
    else
      return false;
  }

  //! \brief Less-than operator for ordering, used by, e.g., std::sort().
  //! \details Test on field, moment, var, and !plot. Using operator >, instead
  //!   of operator <, on plot ensures that if a Term is user-requested, i.e.,
  //!   plotted, and also triggered by, e.g., a (turbulence) model, the
  //!   user-requested Term will take precendence.
  //! \param[in] term Term to compare
  //! \return Boolean indicating if term is equation to 'this'
  //! \author J. Bakosi
  bool operator< ( const Term& term ) const {
    if (field < term.field)
      return true;
    else if (field == term.field && moment < term.moment)
      return true;
    else if (field == term.field && moment == term.moment && var < term.var)
      return true;
    else if (field == term.field && moment == term.moment &&
             var == term.var && plot > term.plot)
      return true;
    else
      return false;
  }
};

//! \brief Pack/Unpack: Namespace-scope serialize Term object for Charm++
//! \param[inout] p Charm++'s PUP::er serializer object reference
//! \param[inout] t Term object reference
//! \author J. Bakosi
inline void pup( PUP::er& p, Term& t ) { t.pup(p); }

//! \brief Operator + for adding Term (var+field ID) to a std::string
//! \param[in] lhs std::string to add to
//! \param[in] term Term to add
//! \return Updated std::string
//! \author J. Bakosi
static std::string operator+ ( const std::string& lhs, const Term& term ) {
  std::stringstream ss;
  ss << lhs << char(term.var) << term.field+1;
  std::string rhs = ss.str();
  return rhs;
}

//! \brief Operator << for writing Term to output streams
//! \param[inout] os Output stream to write to
//! \param[in] term Term to write
//! \return Updated output stream
//! \author J. Bakosi
static std::ostream& operator<< ( std::ostream& os, const Term& term ) {
  os << char(term.var) << term.field+1;
  return os;
}

//! \brief Lighter-weight (lighter than Term) structure for storing only
//!    var+field.
//! \details Used for representing the variable + field ID in, e.g., statistics
//!    or sample space.
//! \author J. Bakosi
struct FieldVar {
  char var;          //!< Dependent variable
  int field;         //!< Field ID

  //! Constructor: Initialize state variables, allowing defaults for both
  //! \param[in] v Dependent variable
  //! \param[in] f Field ID
  //! \author J. Bakosi
  explicit FieldVar( const char v='\0', const int f=0 ) : var(v), field(f) {}

  //! \brief Equal operator for, e.g., testing on equality of containers
  //!   containing FieldVars.
  //! \details  E.g., walker::ctr::InputDeck's tag::pdf field. Test on both var
  //!    and field.
  //! \param[in] f FieldVar to compare
  //! \return Boolean indicating if f is equal to 'this'
  //! \author J. Bakosi
  bool operator== ( const FieldVar& f ) const {
    if (field == f.field && var == f.var)
      return true;
    else
      return false;
  }

  //! \brief Operator += for adding FieldVar to std::string
  //! \param[inout] os std::string to add to
  //! \param[in] f FieldVar to add
  //! \return Updated std::string
  //! \author J. Bakosi
  friend std::string& operator+= ( std::string& os, const FieldVar& f ) {
     std::stringstream ss;
     ss << os << f.var << f.field+1;
     os = ss.str();
     return os;
  }
};

//! \brief Function for writing std::vector< Term > to output streams
//! \param[inout] os Output stream to write to
//! \param[in] vec Vector of Terms to write
//! \return Updated output stream
//! \author J. Bakosi
static
std::ostream& estimated( std::ostream& os, const std::vector< Term >& vec ) {
  if (!vec.empty()) {
    os << "<";
    for (const auto& w : vec) os << w;
    os << "> ";
  }
  return os;
}

//! \brief Function for writing requested statistics terms to output streams
//! \param[inout] os Output stream to write to
//! \param[in] vec Vector of Terms to write
//! \return Updated output stream
//! \author J. Bakosi
static
std::ostream& requested( std::ostream& os, const std::vector< Term >& vec ) {
  if (!vec.empty() && vec[0].plot) {
    os << "<";
    for (const auto& w : vec) os << w;
    os << "> ";
  }
  return os;
}

//! \brief Function for writing triggered statistics terms to output streams
//! \param[inout] os Output stream to write to
//! \param[in] vec Vector of Terms to write
//! \return Updated output stream
//! \author J. Bakosi
static
std::ostream& triggered( std::ostream& os, const std::vector< Term >& vec ) {
  if (!vec.empty() && !vec[0].plot) {
    os << "<";
    for (const auto& w : vec) os << w;
    os << "> ";
  }
  return os;
}

//! \brief Function for writing PDF sample space variables to output streams
//! \param[inout] os Output stream to write to
//! \param[in] var Vector of Terms to write
//! \param[in] bin Vector of PDF bin sizes
//! \param[in] name Name of PDF
//! \param[in] ext Vector of sample space extents
//! \return Updated output stream
//! \author J. Bakosi
static
std::ostream& pdf( std::ostream& os,
                   const std::vector< Term >& var,
                   const std::vector< tk::real >& bin,
                   const std::string& name,
                   const std::vector< tk::real >& ext )
{
  Assert( !var.empty(), "var is empty in sample_space()" );
  Assert( !bin.empty(), "bin is empty in sample_space()" );
  Assert( var.size() == bin.size(),
          "var.size and bin.size() must equal in ctr::pdf()" );

  os << name << '(';
  std::size_t i;
  // sample space variables
  for (i=0; i<var.size()-1; ++i) os << var[i] << ',';
  os << var[i] << ':';
  // sample space bin sizes
  for (i=0; i<bin.size()-1; ++i) os << bin[i] << ',';
  os << bin[i];
  // sample space extents
  if (!ext.empty()) {
    os << ';';
    for (i=0; i<ext.size()-1; ++i) os << ext[i] << ',';
    os << ext[i];
  }
  os << ") ";
  return os;
}

//! \brief Case-insensitive character comparison functor
//! \author J. Bakosi
struct CaseInsensitiveCharLess {
  //! Function call operator
  //! \param[in] lhs Left character of the comparitor operand
  //! \param[in] rhs Right character of the comparitor operand
  //! \return Boolean indicating the result of the comparison
  //! \author J. Bakosi
  bool operator() ( char lhs, char rhs ) const {
    return std::tolower( lhs ) < std::tolower( rhs );
  }
};

//! \brief Products are arbitrary number of Terms to be multiplied and ensemble
//!   averaged.
//! \details An example is the scalar flux in x direction which needs two terms
//! for ensemble averaging: (Y-\<Y\>) and (U-\<U\>), then the central moment is
//! \<yu\> = <(Y-\<Y\>)(U-\<U\>)>, another example is the third mixed central
//! moment of three scalars which needs three terms for ensemble averaging:
//! (Y1-\<Y1\>), (Y2-\<Y2\>), and (Y3-\<Y3\>), then the central moment is
//! \<y1y2y3\> = \<(Y1-\<Y1\>)(Y2-\<Y2\>)(Y3-\<Y3\>)\>.
//! \author J. Bakosi
using Product = std::vector< Term >;

//! \brief Find out if a vector of Terms only contains ordinary moment terms
//! \details If and only if all terms are ordinary, the vector of Terms is
//!    ordinary.
//! \param[in] vec Vector of Terms to check
//! \return Boolean indicating if all terms are ordinary
//! \author J. Bakosi
static inline bool ordinary( const std::vector< ctr::Term >& vec ) {
  bool ord = true;
  for (auto& term : vec) if (term.moment == ctr::Moment::CENTRAL) ord = false;
  return ord;
}

//! \brief Find out if a vector of Terms contains any central moment terms
//! \details If any term is central, the vector of Terms is central.
//! \param[in] vec Vector of Terms to check
//! \return Boolean indicating of any term is central
//! \author J. Bakosi
static inline bool central( const std::vector< ctr::Term >& vec )
{ return !ordinary( vec ); }

//! \brief Probability density function (vector of sample space variables)
//! \author J. Bakosi
using Probability = std::vector< Term >;

//! \brief PDF information bundle
//! \author J. Bakosi
struct PDFInfo {
  const std::string& name;                  //!< PDF identifier, i.e., name
  const std::vector< tk::real >& exts;      //!< Sample space extents
  std::vector< std::string > vars;          //!< List of sample space ariables
};

//! \brief Find sample space variables for a PDF
//! \details The template argument specifies the number of dimensions of the
//!   PDF sample space: 1, 2, or 3.
//! \param[in] pdfs Vector of PDFs to operate on
//! \param[in] idx Index of the PDF with given sample space dimension 'd' given
//!    by the template argument
//! \return Vector of sample variables
//! \author J. Bakosi
template< std::size_t d >
std::vector< std::string >
vars( const std::vector< Probability >& pdfs, long int idx ) {
  static_assert( d >= 1 && d <= 3 ,
                 "Only 1, 2, or 3-dimensional PDFs are supported" );
  long int n = -1;
  std::vector< std::string > v;
  for (const auto& probability : pdfs) {
    if (probability.size() == d) ++n;
    if (n == idx) {
      for (const auto& term : probability)
        v.push_back( term.var + std::to_string(term.field+1) );
      return v;
    }
  }
  Throw( "Cannot find PDF." );
}

//! Find PDF information given the sample space dimension and its index
//! \param[in] binsizes Vector of sample space bin sizes for multiple PDFs
//! \param[in] names Vector of PDF names
//! \param[in] exts Vector of sample space extents
//! \param[in] pdfs Vector of PDFs
//! \param[in] idx Index of the PDF with given sample space dimension
//! \see walker::Distributor
//! \author J. Bakosi
template< std::size_t d >
PDFInfo pdfInfo( const std::vector< std::vector< tk::real > >& binsizes,
                 const std::vector< std::string >& names,
                 const std::vector< std::vector< tk::real > >& exts,
                 const std::vector< Probability >& pdfs,
                 long int idx )
{
  Assert( binsizes.size() == names.size(),
          "Number of binsizes vector and the number of PDF names must equal." );
  long int n = -1;
  long int i = 0;
  for (const auto& bs : binsizes) {
    if (bs.size() == d) ++n;
    if (n == idx) return { names[i], exts[i], vars<d>(pdfs,idx) };
    ++i;
  }
  Throw( "Cannot find PDF name." );
}

//! \brief Make requested statistics unique
//! \param[in,out] statistics Vector of statistics
//! \author  J. Bakosi
static inline void
unique( std::vector< tk::ctr::Product >& statistics ) {
  std::sort( begin(statistics), end(statistics) );
  auto it = std::unique( begin(statistics), end(statistics) );
  statistics.resize( std::distance( begin(statistics), it ) );
}

} // ctr::
} // tk::

#endif // StatControl_h
