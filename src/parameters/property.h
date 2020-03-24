/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      property.h                                                  //
//                                                                         //
//  Purpose:   Header file for random generator class                      //
//                                                                         //
//  Author(s): Lebedev I.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __PROPERTY_H__
#define __PROPERTY_H__

/**
\file property.h

\authors ������� �.
\date 2015-2016
\copyright ���� ��. �.�. ������������

\brief ���������� ������ ������� ��� �������

*/

#include <string>
#include "common.h"
using namespace std;

/* ======================================================================== *\
**  ���������� �������                                                      **
\* ======================================================================== */


/**
������� ����� ������� ���������
*/

class IBaseClass
{
protected:

public:

  /// �������� ������ �� ��������� � ���� ������
  virtual void Copy(void* data) = 0;
  /// ������ ������ ������� void* � ���� �������
  virtual void SetValue(void* data) = 0;
  /// ���������� ��������� �� ������ ���������� � �������
  virtual void* GetValue() = 0;
  /// �������� � ������
  virtual string ToString() = 0;
  /// ��������� �������� �� ������
  virtual void FromString(string val) = 0;

  virtual ~IBaseClass() {}

  /// ������ ����������� ��������� �������
  virtual void SetSeparator(string separator) = 0;
  /// ���������� ����������� ��������� �������
  virtual string GetSeparator() = 0;

  /// ������ ������ ������� ���������
  virtual void SetSize(int size) = 0;
  /// ���������� ������ ������� ���������
  virtual int GetSize() = 0;

  /// ��� ��������
  virtual string GetName() = 0;
  /// ����� �������
  virtual string GetHelp() = 0;
  /// �������� ��� ��� ��������� ������
  virtual string GetLink() = 0;

  /// ��� ��������
  virtual void SetName(string name) = 0;
  /// ����� �������
  virtual void SetHelp(string help) = 0;
  /// �������� ��� ��� ��������� ������
  virtual void SetLink(string link) = 0;
  /// ���������� ������� �� ��������
  virtual string GetHelpString() = 0;
  /// ���������� �������� ��������� ���������
  virtual string GetCurrentStringValue() = 0;
  /// ��������� �� ��� ��������� �� ��������� �������
  virtual bool IsNameEqual(string name) = 0;

  /// ���������� ����������� �� �������� ��������� �� ���������� ������� ��� ������ �����
  virtual bool GetIsReadValue() = 0;
  /// ������ ����������� �� �������� ��������� �� ���������� ������� ��� ������ �����
  virtual void SetIsReadValue(bool isReadValue) = 0;

  /// �������� �� �������� ������, � �������� �������� �� ���������.
  virtual bool IsFlag() = 0;
  /// ��������� ������������ ��������
  virtual int CheckValue() = 0;
};


/**
������� ����� ������� ���������
*/
template <class Owner>
class TBaseProperty : public IBaseClass
{
protected:

  /// ��� ������ ������� �������� ������, ��������� ����� �������� ���������� ��� ������
  typedef int (Owner::*tCheckValue)(int);

  /// �������� �������
  Owner* mOwner;
  /// ����������� �� �������� ��������� �� ���������� ������� ��� ������ �����
  bool mIsReadValue;
public:
  /// ���������� ��������� ���������� ���� ��������
  virtual void operator = (TBaseProperty<Owner>& data);
  /// ���������� ��������� ���������� ��� ���������
  virtual void operator = (TBaseProperty<Owner>* data);

  /// ������� ������ data
  virtual void Clone(TBaseProperty<Owner>** data) = 0;

  TBaseProperty(Owner* owner): mOwner(owner), mIsReadValue(false) {}
  virtual ~TBaseProperty() {}

  /** ������������� ��������
  \param[in] owner - ����� �������� ��������
  \param[in] checkMethod - ����� �������� ������������ ��������� ������
  \param[in] index - ����� ��������
  \param[in] separator - ����������� ��������� �������
  \param[in] size - ������ ������� ��������, ��� ����� ������ �� ����������� �������� - ������ ����� 1
  \param[in] name - ��� ��������
  \param[in] help - ��������� �� ������� �������
  \param[in] link - �������� ������ ��� �������
  \param[in] defValue - �������� �� ���������
  */
  virtual void InitializationParameterProperty(Owner * owner,
    tCheckValue checkMethod, int index, string separator, int size, string name,
    string help, string link, string defValue) = 0;

    /// ���������� ����������� �� �������� ��������� �� ���������� ������� ��� ������ �����
  virtual bool GetIsReadValue()
  {
    return mIsReadValue;
  }
  /// ������ ����������� �� �������� ��������� �� ���������� ������� ��� ������ �����
  virtual void SetIsReadValue(bool isReadValue)
  {
    mIsReadValue = isReadValue;
  }

};

/**
������� ����� ��� �������
*/
template <class Type, class Owner>
class TTypedProperty : public TBaseProperty<Owner>
{
protected:

  /// ��� ������ ������������� ������� ������
  typedef Type (Owner::*tGetter)();
  /// ��� ������ ��������� ������� ������
  typedef void (Owner::*tSetter)(Type);

  /// ����� ��������
  int mIndex;

  /// ����� ������������ ������� ������
  tGetter mGetter;
  /// ����� �������� ������� ������
  tSetter mSetter;
  /// ������� �������� ������
  tCheckValue mCheckValue;
  /// ���������� ������
  Type mValue;
  /// ����� ������ ������������ ���������� ��� �������
  bool mIsHaveValue;
  /// ���� �� �������� �������� ����� �������������
  bool mIsChange;
  /// �������� �� �������� ������, � �������� �������� �� ���������
  bool mIsFlag;

  /// ����������� ���������� ��������
  virtual void CopyValue(Type value);
public:

  /// ������ ������������ �� ���������� ������ ��� �������
  void SetIsHaveValue(bool isHaveValue);
  /// ����� ������ ������������, ���������� ��� �������
  bool GetIsHaveValue();

  /// ������ ������ �������� ��� ��������
  void SetIndex(int index);
  /// ���������� ������ �������� ��� ��������
  int GetIndex();

  /// ������������� �������� ���������� ����, ������
  virtual operator Type();
  /// ������������� �������� ������������, ������
  virtual void operator =(Type data);

  /// ���������� ��������� ���������� ���� ��������
  virtual void operator = (TTypedProperty<Type, Owner>& data);
  /// ���������� ��������� ���������� ��� ���������
  virtual void operator = (TTypedProperty<Type, Owner>* data);

  /// �������� ������ �� ��������� � ���� ������
  virtual void Copy(void* data);
  /// ������ ������ ������� � void* � ���� �������
  virtual void SetValue(void* data);
  /// ���������� ��������� �� ������ ���������� � �������
  virtual void* GetValue();
  /// ������������� �������
  virtual void Init(Owner * owner, tGetter getMethod, tSetter setMethod, tCheckValue checkMethod);

  /// ���������� ������ � ������������ � ���������
  virtual Type GetData();
  /// ���������� ������������� ������� ������
  virtual Type GetAvailableData() const;
  /// ���� �� �������� �������� ����� �������������
  virtual bool GetIsChange();

  TTypedProperty();
  TTypedProperty(Type value);
  TTypedProperty(Owner * owner, tGetter getMethod, tSetter setMethod, tCheckValue checkMethod, Type value);
  virtual ~TTypedProperty();

  /// ������ ������� ������
  virtual void SetSetter(tSetter setter)
  {
    mSetter = setter;
  }
  ///// ���������� ������� ������
  virtual tSetter GetSetter()
  {
    return mSetter;
  }
  /// ������ ������� ������
  virtual void SetGetter(tGetter getter)
  {
    mGetter = getter;
  }
  ///// ���������� ������� ������
  virtual tGetter GetGetter()
  {
    return mGetter;
  }
  /// ������ ������� ����������� ��������
  virtual void SetCheckValue(tCheckValue checkValue)
  {
    mCheckValue = checkValue;
  }
  /// ���������� ������� ����������� ��������
  virtual tCheckValue GetCheckValue()
  {
    return mCheckValue;
  }

  /// �������� �� �������� ������, � �������� �������� �� ���������.
  virtual bool IsFlag()
  {
    return mIsFlag;
  }

  /// ��������� ������������ ��������
  virtual int CheckValue()
  {
    int err = 0;
    if (mCheckValue != 0)
      err = (mOwner->*mCheckValue)(mIndex);
    return err;
  }

};

/**
������� ����� ��� ������� ����������, ����� ������ ����������
*/
template <class Type, class Owner>
class TParameterProperty : public TTypedProperty<Type, Owner>
{
protected:
  /// ����������� �������
  string mSeparator;
  /// ������ �������
  int mSize;
  /// ��� ��������
  string mName;
  /// ����� �������
  string mHelp;
  /// �������� ��� ��� ��������� ������
  string mLink;

  /// ������ ���������� ��� �� �����
  string GetFullLink();

public:
  /// ���������� ��������� ���������� ���� ��������
  virtual void operator = (TParameterProperty<Type, Owner>&  data);
  /// ���������� ��������� ���������� ��� ���������
  virtual void operator = (TParameterProperty<Type, Owner>* data);

  /// ������� ������ data
  virtual void Clone(TBaseProperty<Owner>** data);

  /// ������ ����������� ��������� �������
  virtual void SetSeparator(string separator);
  /// ���������� ����������� ��������� �������
  virtual string GetSeparator();

  /// ������ ������ ������� ���������
  virtual void SetSize(int size);
  /// ���������� ������ ������� ���������
  virtual int GetSize();

  /// ��� ��������
  virtual string GetName();
  /// ����� �������
  virtual string GetHelp();
  /// �������� ��� ��� ��������� ������
  virtual string GetLink();

  /// ��� ��������
  virtual void SetName(string name);
  /// ����� �������
  virtual void SetHelp(string help);
  /// �������� ��� ��� ��������� ������
  virtual void SetLink(string link);
  /// ���������� ������� �� ��������
  virtual string GetHelpString();
  /// ���������� �������� ��������� ���������
  virtual string GetCurrentStringValue();

  /// �������� � ������
  virtual string ToString();
  /// ��������� �������� �� ������
  virtual void FromString(string val);

  /// ��������� �� ��� ��������� �� ��������� �������
  virtual bool IsNameEqual(string name);

  /** ������������� ��������
  \param[in] owner - ����� �������� ��������
  \param[in] checkMethod - ����� �������� ������������ ��������� ������
  \param[in] index - ����� ��������
  \param[in] separator - ����������� ��������� �������
  \param[in] size - ������ ������� ��������, ��� ����� ������ �� ����������� �������� - ������ ����� 1
  \param[in] name - ��� ��������
  \param[in] help - ��������� �� ������� �������
  \param[in] link - �������� ������ ��� �������
  \param[in] defValue - �������� �� ���������
  */
  virtual void InitializationParameterProperty(Owner * owner,
    tCheckValue checkMethod, int index, string separator, int size, string name,
    string help, string link, string defValue);

  /** ������������� ��������
  \param[in] owner - ����� �������� ��������
  \param[in] getMethod - ������
  \param[in] setMethod - ������
  \param[in] checkMethod - ����� �������� ������������ ��������� ������
  \param[in] index - ����� ��������
  \param[in] separator - ����������� ��������� �������
  \param[in] size - ������ ������� ��������, ��� ����� ������ �� ����������� �������� - ������ ����� 1
  \param[in] name - ��� ��������
  \param[in] help - ��������� �� ������� �������
  \param[in] link - �������� ������ ��� �������
  \param[in] defValue - �������� �� ���������
  */
  virtual void InitializationParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
    tCheckValue checkMethod, int index, string separator, int size, string name,
    string help, string link, string defValue);

  TParameterProperty();
  TParameterProperty(Type value);
  TParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
    tCheckValue checkMethod, Type value);

};


/* ======================================================================== *\
**  ���������� ������� ������     TBaseProperty                                 **
\* ======================================================================== */

//���������� ��������� ���������� ���� ��������
template <class Owner>
void TBaseProperty<Owner>::operator = (TBaseProperty<Owner>& data)
{
  mOwner = data.mOwner;
}

///// ���������� ��������� ���������� ��� ���������
template <class Owner>
void TBaseProperty<Owner>::operator = (TBaseProperty<Owner>* data)
{
  mOwner = data->mOwner;
}


/* ======================================================================== *\
**  ���������� ������� ������     TTypedProperty                                 **
\* ======================================================================== */

/// ����������� ���������� ��������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::CopyValue(Type value)
{
  mValue = value;
}

/// ������ ������������ �� ���������� ������ ��� �������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::SetIsHaveValue(bool isHaveValue)
{
  mIsHaveValue = isHaveValue;
}
/// ����� ������ ������������, ���������� ��� �������
template <class Type, class Owner>
bool TTypedProperty<Type, Owner>::GetIsHaveValue()
{
  return mIsHaveValue;
}

/// ������ ������ �������� ��� ��������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::SetIndex(int index)
{
  mIndex = index;
}
/// ���������� ������ �������� ��� ��������
template <class Type, class Owner>
int TTypedProperty<Type, Owner>::GetIndex()
{
  return mIndex;
}

/// ������������� �������� ���������� ����, ������
template <class Type, class Owner>
TTypedProperty<Type, Owner>::operator Type()
{
  if ((mIsHaveValue) || (mGetter == 0))
    return mValue;
  else
    return (mOwner->*mGetter)();
}

/// ������������� �������� ������������, ������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::operator =(Type data)
{
  Type oldVal = mValue;
  mIsChange = true;
  if ((mIsHaveValue) || (mSetter == 0))
    CopyValue(data);
  else
    (mOwner->*mSetter)(data);
  int err = 0;
  if (mCheckValue != 0)
    err = (mOwner->*mCheckValue)(mIndex);
  if (err != 0)
  {
    CopyValue(oldVal);
  }
}

/// ���������� ��������� ���������� ���� ��������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::operator = (TTypedProperty<Type, Owner>& data)
{
  CopyValue(data.mValue);
  mIsHaveValue = data.mIsHaveValue;
  mGetter = data.mGetter;
  mSetter = data.mSetter;
  mCheckValue = data.mCheckValue;
  mOwner = data.mOwner;
  mIndex = data.mIndex;
  mIsChange = data.mIsChange;
}

/// ���������� ��������� ���������� ��� ���������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::operator = (TTypedProperty<Type, Owner>* data)
{
  CopyValue(data->mValue);
  mIsHaveValue = data->mIsHaveValue;
  mGetter = data->mGetter;
  mSetter = data->mSetter;
  mCheckValue = data->mCheckValue;
  mOwner = data->mOwner;
  mIndex = data->mIndex;
  mIsChange = data->mIsChange;
}

/// �������� ������ �� ��������� � ���� ������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::Copy(void* data)
{
  operator = ((TTypedProperty<Type, Owner>*)data);
}
/// ������ ������ ������� � void* � ���� �������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::SetValue(void* data)
{
  *this = *((Type*)(data));
}
/// ���������� ��������� �� ������ ���������� � �������
template <class Type, class Owner>
void* TTypedProperty<Type, Owner>::GetValue()
{
  if ((mIsHaveValue) || (mGetter == 0))
    return (void*)&mValue;
  else
  {
    Type* val = new Type ((mOwner->*mGetter)());
    return (void*)val;
  }
}

/// ������������� �������
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::Init(Owner * owner, tGetter getMethod, tSetter setMethod, tCheckValue checkMethod)
{
  mOwner = owner;
  mGetter = getMethod;
  mSetter = setMethod;
  mCheckValue = checkMethod;
  if ((getMethod != 0) || (setMethod != 0))
    mIsHaveValue = false;
  else
    mIsHaveValue = true;
  mIsChange = false;
};

/// ���������� ������ � ������������ � ���������
template <class Type, class Owner>
Type TTypedProperty<Type, Owner>::GetData()
{
  return operator Type();
}
/// ���������� ������������� ������� ������
template <class Type, class Owner>
Type TTypedProperty<Type, Owner>::GetAvailableData() const
{
  return mValue;
}

/// ���� �� �������� �������� ����� �������������
template <class Type, class Owner>
bool TTypedProperty<Type, Owner>::GetIsChange()
{
  return mIsChange;
}

template <class Type, class Owner>
TTypedProperty<Type, Owner>::TTypedProperty() : TBaseProperty(0), mGetter(0), mSetter(0), mCheckValue(0)
{
  mIsHaveValue = true;
  mIndex = 0;
  mIsChange = false;
  mIsFlag = false;
}

template <class Type, class Owner>
TTypedProperty<Type, Owner>::TTypedProperty(Type value) : TBaseProperty(0), mGetter(0), mSetter(0), mCheckValue(0)
{
  CopyValue(value);
  mIsHaveValue = true;
  mIndex = 0;
  mIsChange = false;
  mIsFlag = false;
}

template <class Type, class Owner>
TTypedProperty<Type, Owner>::TTypedProperty(Owner * owner, tGetter getMethod, tSetter setMethod, tCheckValue checkMethod, Type value) :
TBaseProperty(owner), mGetter(getMethod), mSetter(setMethod), mCheckValue(checkMethod)
{
  CopyValue(value);
  if ((getMethod != 0) || (setMethod != 0))
    mIsHaveValue = false;
  else
    mIsHaveValue = true;
  mIsChange = false;
  mIndex = 0;
  mIsFlag = false;
}

template <class Type, class Owner>
TTypedProperty<Type, Owner>::~TTypedProperty()
{}

/* ======================================================================== *\
**  ���������� ������� ������     TParameterProperty                                 **
\* ======================================================================== */

/// ���������� ��������� ���������� ���� ��������
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::operator = (TParameterProperty<Type, Owner>&  data)
{
  mSeparator = data.mSeparator;
  mSize = data.mSize;
  mName = data.mName;
  mHelp = data.mHelp;
  mLink = data.mLink;
  mIsFlag = data.mIsFlag;
  TTypedProperty::operator=(data);
}

/// ���������� ��������� ���������� ��� ���������
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::operator = (TParameterProperty<Type, Owner>* data)
{
  mSeparator = data->mSeparator;
  mSize = data->mSize;
  mName = data->mName;
  mHelp = data->mHelp;
  mLink = data->mLink;
  mIsFlag = data->mIsFlag;
  TTypedProperty::operator=(data);
}

/// ������� ������ data
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::Clone(TBaseProperty<Owner>** data)
{
  *data = new TParameterProperty<Type, Owner>();
  **data = *this;
}

/// ������ ����������� ��������� �������
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetSeparator(string separator)
{
  mSeparator = separator;
}
/// ���������� ����������� ��������� �������
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetSeparator()
{
  return mSeparator;
}
/// ������ ������ ������� ���������
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetSize(int size)
{
  //if (size > 0)
  //  mSize = size;
}
/// ���������� ������ ������� ���������
template <class Type, class Owner>
int TParameterProperty<Type, Owner>::GetSize()
{
  return mSize;
}

/// ��� ��������
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetName()
{
  return mName;
}
/// ����� �������
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetHelp()
{
  return mHelp;
}
/// �������� ��� ��� ��������� ������
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetLink()
{
  return mLink;
}

/// ��� ��������
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetName(string name)
{
  mName = name;
}
/// ����� �������
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetHelp(string help)
{
  mHelp = help;
}
/// �������� ��� ��� ��������� ������
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetLink(string link)
{
  mLink = link;
}
/// ���������� ������� �� ��������
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetHelpString()
{
  string result = "";
  result = result + GetName() + " (" + GetLink() + ") - \'" + GetHelp() + "\' default:\t" + ToString();
  return result;
}

/// ���������� �������� ��������� ���������
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetCurrentStringValue()
{
  string result = "";
  result = result + GetName() + " = " + ToString();
  return result;
}

/// �������� � ������
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::ToString()
{
  return "";
}
/// ��������� �������� �� ������
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::FromString(string val)
{}

/// ������ ���������� ��� �� �����
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetFullLink()
{
  return "-" + GetName();
}

/// ��������� �� ��� ��������� �� ��������� �������
template <class Type, class Owner>
bool TParameterProperty<Type, Owner>::IsNameEqual(string name)
{
  if ((name == GetFullLink()) || (name == GetLink()) || (name == GetName()))
    return true;
  else
    return false;
}

template <class Type, class Owner>
void TParameterProperty<Type, Owner>::InitializationParameterProperty(Owner * owner,
  tCheckValue checkMethod, int index, string separator, int size, string name,
  string help, string link, string defValue)
{
  TTypedProperty<Type, Owner>::Init(owner, 0, 0, checkMethod);

  SetIndex(index);
  SetSeparator(separator);
  SetSize(size);
  SetName(name);
  SetHelp(help);
  SetLink(link);

  FromString(defValue);
  mIsChange = false;
}

template <class Type, class Owner>
void TParameterProperty<Type, Owner>::InitializationParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
  tCheckValue checkMethod, int index, string separator, int size, string name,
  string help, string link, string defValue)
{
  TTypedProperty<Type, Owner>::Init(owner, getMethod, setMethod, checkMethod);

  SetIndex(index);
  SetSeparator(separator);
  SetSize(size);
  SetName(name);
  SetHelp(help);
  SetLink(link);

  FromString(defValue);
  mIsChange = false;
}

template <class Type, class Owner>
TParameterProperty<Type, Owner>::TParameterProperty(): mSize(1), TTypedProperty()
{
  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

template <class Type, class Owner>
TParameterProperty<Type, Owner>::TParameterProperty(Type value) : mSize(1), TTypedProperty(value)
{
  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

template <class Type, class Owner>
TParameterProperty<Type, Owner>::TParameterProperty(Owner * owner, tGetter getMethod,
  tSetter setMethod, tCheckValue checkMethod, Type value) :
mSize(1), TTypedProperty(mOwner, mGetter, mSetter, mCheckValue, value)
{
  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

#endif //__TYPES_H__
// - end of file ----------------------------------------------------------------------------------
