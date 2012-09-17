//******************************************************************************
/*!
  \file      src/Base/SymCompRowMatrix.h
  \author    J. Bakosi
  \date      Sun 16 Sep 2012 06:01:53 PM MDT
  \copyright Copyright 2005-2012, Jozsef Bakosi, All rights reserved.
  \brief     Symmetric compressed row sparse matrix
  \details   Derived sparse matrix class for symmetric compressed sparse row
             (CSR) storage format, with only the upper triangle stored,
             including the main diagonal.
*/
//******************************************************************************
#ifndef SymCompRowMatrix_h
#define SymCompRowMatrix_h

#include <Memory.h>

namespace Quinoa {

//! Symmetric compressed row sparse matrix
class SymCompRowMatrix : SparseMatrix {

  public:
    //! Constructor
    SymCompRowMatrix(Memory* memory,
                     string name,
                     Int size,
                     Int dof,
                     Int *psup1,
                     Int* psup2);
    //! Destructor
    ~SymCompRowMatrix();

    //! Add value to matrix in specified position using relative indexing
    void add(Int row, Int column, Int i, Real value);
    //! Add value to matrix in specified position using absolute indexing
    void add(Int row, Int column, Real value);

    //! Insert value to matrix in specified position using relative indexing
    void ins(Int row, Int column, Int i, Real value);
    //! Insert value to matrix in specified position using absolute indexing
    void ins(Int row, Int column, Real value);

    //! Get value from matrix from specified position using relative indexing
    Real get(Int row, Int column, Int i);
    //! Get value from matrix from specified position using absolute indexing
    Real get(Int row, Int column);

    //! Print out matrix entries as stored
    void echoAsStored(ostream& ofs);

    //! Print out nonzero structure of matrix
    void echoNonzeroStructure(ostream& ofs);

    //! Print out matrix as a real matrix
    void echoAsMatrix(ostream& ofs);

    //! Print out matrix as a matlab matrix
    void echoAsMatlab(ostream& ofs);

  private:
    //! Don't permit copy constructor
    SymCompRowMatrix(const SymCompRowMatrix&) = delete;
    //! Don't permit copy assigment
    SymCompRowMatrix& operator=(const SymCompRowMatrix&) = delete;
    //! Don't permit move constructor
    SymCompRowMatrix(SymCompRowMatrix&&) = delete;
    //! Don't permit move assigment
    SymCompRowMatrix& operator=(SymCompRowMatrix&&) = delete;

    MemoryEntry* m_ia;   //!< Row pointers, vector size: size*dof+1
    MemoryEntry* m_ja;   //!< Column indices, vector size: nnz
    MemoryEntry* m_a;    //!< Nonzero values, vector size: nnz

    Int* m_pia;  //!< Data pointer to row indices
    Int* m_pja;  //!< Data pointer to column indices
    Real* m_pa;  //!< Data pointer to matrix values
};

} // namespace Quinoa

#endif // SymCompRowMatrix_h
