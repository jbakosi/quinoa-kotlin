//******************************************************************************
/*!
  \file      src/Model/MixModel/MixModel.h
  \author    J. Bakosi
  \date      Mon 12 Nov 2012 01:34:02 PM MST
  \copyright Copyright 2005-2012, Jozsef Bakosi, All rights reserved.
  \brief     MixModel base
  \details   MixModel base
*/
//******************************************************************************
#ifndef MixModel_h
#define MixModel_h

#include <iostream>

namespace Quinoa {

using namespace std;

class Model;

//! MixModel base
class MixModel {

  public:
    //! Constructor
    MixModel(Model* model, const string& name, const int& nscalar);

    //! Destructor
    virtual ~MixModel() {}

    //! Interface for echo information on mix model
    virtual void echo() = 0;

    //! Interface for mix model initialize
    virtual void init() = 0;

    //! Constant accessor to mix model name
    const string& name() const { return m_name; }

  protected:
    Model* m_model;               //!< Model object pointer
    const string m_name;          //!< Name of mix model
    const int m_nscalar;          //!< Number of mixing scalars

  private:
    //! Don't permit copy constructor
    MixModel(const MixModel&) = delete;
    //! Don't permit copy assigment
    MixModel& operator=(const MixModel&) = delete;
    //! Don't permit move constructor
    MixModel(MixModel&&) = delete;
    //! Don't permit move assigment
    MixModel& operator=(MixModel&&) = delete;
};

} // namespace Quinoa

#endif // MixModel_h