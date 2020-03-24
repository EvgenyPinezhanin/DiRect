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

#ifndef __BASE_PARAMETERS_H__
#define __BASE_PARAMETERS_H__

/**
\file baseParameters.h

\authors ������� �.
\date 2015-2016
\copyright ���� ��. �.�. ������������

\brief ���������� ������ ������� ��� �������

*/


//#include <mpi.h>
#include "types.h"
#include "pugixml.hpp"

/**
������� ����� ����������
��� �������� ���������� ���������� �������������� �������� OWNER_NAME
� � ������������ ������ mOwner
(mOwner = this;)
*/
class TCombinableBaseParameters
{
protected:
  /// ���������� ��������� ��������� ������
  int mArgumentCount;
  /// ���� ��������� ��������� ������
  char** mAargumentValue;
  /// ��� �� ��������������� MPI
  bool mIsMPIInit;
public:

  /// ������ ��������� ���������
  virtual void SetInitParam(int argc = 0, char* argv[] = 0, bool isMPIInit = false)
  {
    mArgumentCount = argc;
    mAargumentValue = argv;
    mIsMPIInit = isMPIInit;
  }

  /// ���������� ��� ��������� ���� ������� � �����
  virtual void CombineOptions(IBaseClass** otherOptions, int count) = 0;
    /// ���������� ��������� ��������
  virtual IBaseClass** GetOptions() = 0;
  /// ���������� ���������� �����
  virtual int GetOptionsCount() = 0;

  virtual void SetVal(string name, string val) = 0;
  /// ������� ��������� � ������ name �������� val
  virtual void SetVal(string name, void* val) = 0;
  /// ���������� ������ � ��������� ��������� � ������ name
  virtual string GetStringVal(string name) = 0;
  /// ���������� �������� ��������� � ������ name
  virtual void* GetVal(string name) = 0;

  TCombinableBaseParameters()
  {
    mArgumentCount = 0;
    mAargumentValue = 0;
    mIsMPIInit = false;
  }
};


/**
������� ����� ����������
��� �������� ���������� ���������� �������������� �������� OWNER_NAME
� � ������������ ������ mOwner
(mOwner = this;)
*/
template <class Owner>
class TBaseParameters : public TCombinableBaseParameters
{
#undef OWNER_NAME
#define OWNER_NAME Owner

protected:
  /// ������ ������� ������������ � ������ �������
  IBaseClass** mOtherOptions;
  /// ������ ������� ������������ � ���� ������
  TBaseProperty<Owner>** mOptions;
  /// ������ ������� ������������ � ���� ������ ����������� � �������� ����
  IBaseClass** mBaseTypeOptions;
  /// ���������� �����
  int mOptionsCount;
  /// ���������� ����� �� ������ �������
  int mOtherOptionsCount;
  /// ������������ ������ ������� ����������
  int mOptionsSize;
  /// ������������ ������ ������� ����������  ������������ � ������ �������
  int mOtherOptionsSize;

  /// �������� �������
  bool mIsPrintHelp;
  /// ������� ��������� ��������� ������
  bool mIsHaveArguments;
  /// �������� ����� ������
  Owner* mOwner;
  /// ������������������� �� ���������
  bool mIsInit;
  /// ���� �� ��������� �� ���������������� �����
  std::string mConfigPath;

  /// �������� ������������ ����� ��������� ������ ����������
  virtual int CheckValue(int index = -1);

  /**
  ������������� ���������
  \param[in] option - �������� ������� ��������������
  \param[in] sizeVal - ������ ������� ��������, ��� ����� ������ �� ����������� �������� - ������ ����� 1
  \param[in] name - ��� ��������
  \param[in] help - ��������� �� ������� �������
  \param[in] com - �������� ������ ��� �������
  \param[in] defVal - �������� �� ���������
  */
  virtual void InitializationOption(TBaseProperty<Owner>* option, string name, string defVal,
    string com, string help, int sizeVal);
  /// ��������� ����� � ����� ������
  virtual void AddOption(TBaseProperty<Owner>* option);
  /// ������� �������� �� ��������� ������� ����������
  virtual void SetBaseDefaultParameters();
  /**
  ������� �������� �� ��������� ��� ���� ����������
  ������:
  InitOption(��� ���������, �������� �� ���������, "�������� �������", "������� �� ���������", ���-�� ���������);
  *���-�� ��������� ��� �� �������� ������ ����� 1.
  InitOption(Separator,_, "-Separator", "eparator", 1);
  */
  virtual void SetDefaultParameters() = 0;
  /// ������ ���������� �� ����� ConfigPath
  virtual void ReadConfigFile();
  /// ������ ���������� ��������� ������
  virtual void ReadParameters(int argc, char* argv[]);
  /// ������ ����������� ������� ��� ���� �����
  void SetSeparator();


public:
  ///�������� ��� ��� ������� ��� ������ ��������� ������
  TBool<TBaseParameters<Owner>> IsPrintHelpWithoutArguments;
  /// ��������� �� ��� ������ ��������� ������
  TBool<TBaseParameters<Owner>> IsStartWithoutArguments;
  /// ����������� ��������� �������
  TString<TBaseParameters<Owner>> Separator;
  /// ���� �� ������ ����� ���������
  TString<TBaseParameters<Owner>> ConfigPath;
  /// ������ ������� �� ����������
  void PrintHelp();
  /// ������ ������� �������� ����������
  void PrintParameters();
  /// ��������� �� ������ ���������
  bool IsStart();

  /**
  �������� ������������ ��� ��������� ����������
  ��� ��������������� ���������� ������� ������� ����� �������� ������!
  */
  virtual int CheckValueParameters(int index = 0);

  /// ������ �������� ��������� � ������ name
  void PrintParameter(string name);
  /// ������� ��������� � ������ name �������� val
  void SetVal(string name, string val);
  /// ������� ��������� � ������ name �������� val
  void SetVal(string name, void* val);
  /// ���������� ������ � ��������� ��������� � ������ name
  string GetStringVal(string name);
  /// ���������� �������� ��������� � ������ name
  void* GetVal(string name);

  /**
  ������������� ���������
  \param[in] pt - ��� ���������
  \param[in] sizeVal - ������ ������� ��������, ��� ����� ������ �� ����������� �������� - ������ ����� 1
  \param[in] name - ��� ��������
  \param[in] help - ��������� �� ������� �������
  \param[in] com - �������� ������ ��� �������
  \param[in] defVal - �������� �� ���������
  */
  virtual void AddOption(EParameterType pt, string name, string defVal,
    string com, string help, int sizeVal);

  /// ���������� ��� ��������� ���� ������� � �����
  virtual void CombineOptions(IBaseClass** otherOptions, int count);
  /// ���������� ��������� ��������
  virtual IBaseClass** GetOptions();
  /// ���������� ���������� �����
  virtual int GetOptionsCount();

  /// ������������� ����������
  virtual void Init(int argc, char* argv[], bool isMPIInit = false);
  TBaseParameters();
  TBaseParameters(TBaseParameters& parameters);
  virtual ~TBaseParameters();
};

/// �������� ������������
template <class Owner>
int TBaseParameters<Owner>::CheckValue(int index = -1)
{

  if (Separator.ToString().length() < 1)
  {
    Separator = "_";
  }

  return 0;
}

/// ������������� ���������
template <class Owner>
void TBaseParameters<Owner>::InitializationOption(TBaseProperty<Owner>* option, string name, string defVal,
  string com, string help, int sizeVal)
{
  option->InitializationParameterProperty(mOwner, &Owner::CheckValueParameters, mOptionsCount, Separator, sizeVal, name, help, com, defVal);
  AddOption(option);
}

/// ��������� ����� � ����� ������
template <class Owner>
void TBaseParameters<Owner>::AddOption(TBaseProperty<Owner>* option)
{
  for (int i = 0; i < mOptionsCount; i++)
    if (mOptions[i]->IsNameEqual(option->GetName()))
      return;

  mOptions[mOptionsCount] = option;
  mBaseTypeOptions[mOptionsCount] = (IBaseClass*)option;
  mOptionsCount++;


  if (mOptionsCount >= mOptionsSize )
  {
    TBaseProperty<Owner>** bufOptions = new TBaseProperty<Owner>* [mOptionsSize];
    for (int i = 0; i < mOptionsSize; i++)
    {
      bufOptions[i] = mOptions[i];
    }

    delete [] mOptions;
    delete [] mBaseTypeOptions;

    mOptions = new TBaseProperty<Owner>* [mOptionsSize * 2];
    mBaseTypeOptions = new IBaseClass* [mOptionsSize * 2];

    for (int i = 0; i < mOptionsSize * 2; i++)
    {
      mOptions[i] = 0;
      mBaseTypeOptions[i] = 0;
    }

    for (int i = 0; i < mOptionsSize; i++)
    {
      mOptions[i] = bufOptions[i];
      mBaseTypeOptions[i] = (IBaseClass*)mOptions[i];
    }
    mOptionsSize = mOptionsSize * 2;

    delete [] bufOptions;
  }
}

/// ������� �������� �� ��������� ������� ����������
template <class Owner>
void TBaseParameters<Owner>::SetBaseDefaultParameters()
{
  int sizeVal = 1;

  Separator.InitializationParameterProperty(this, &TBaseParameters::CheckValue, mOptionsCount, Separator, sizeVal,
    "Separator", "eparator", "-Separator", "_");
  AddOption((TBaseProperty<Owner>*)(&Separator));

  IsPrintHelpWithoutArguments.InitializationParameterProperty(this, &TBaseParameters::CheckValue, mOptionsCount, Separator, sizeVal,
    "IsPrintHelpWithoutArguments", "Is print help without console arguments", "-PHWA", "false");
  AddOption((TBaseProperty<Owner>*)(&IsPrintHelpWithoutArguments));

  IsStartWithoutArguments.InitializationParameterProperty(this, &TBaseParameters::CheckValue, mOptionsCount, Separator, sizeVal,
    "IsStartWithoutArguments", "Is start without console arguments", "-SWA", "true");
  AddOption((TBaseProperty<Owner>*)(&IsStartWithoutArguments));

  ConfigPath.InitializationParameterProperty(this, &TBaseParameters::CheckValue, mOptionsCount, Separator, sizeVal,
    "ConfigPath", "The path to the configuration file of the program", "-CP", mConfigPath);
  AddOption((TBaseProperty<Owner>*)(&ConfigPath));

}

/// ������ ���������� �� ����� ConfigPath
template <class Owner>
void TBaseParameters<Owner>::ReadConfigFile()
{
  if (mConfigPath != "")
    ConfigPath = mConfigPath;
  if (ConfigPath.operator std::string() != "")
  {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(ConfigPath.ToString().c_str());
    if (result.status != pugi::status_ok)
      return ;
    pugi::xml_node config = doc.child("config");
    for (pugi::xml_node iter = config.first_child(); iter != 0; iter = iter.next_sibling())
    {
      string name = iter.name();
      for (int i = 0; i < mOptionsCount; i++)
      {
        if (mOptions[i]->IsNameEqual(name))
        {
          if (!mOptions[i]->IsFlag())
          {
            string value = iter.child_value();
            mOptions[i]->FromString(value);
            mOptions[i]->SetIsReadValue(true);
            break;
          }
          else
          {
            mOptions[i]->FromString("1");
            mOptions[i]->SetIsReadValue(true);
            break;
          }
        }
      }
    }
  }
}

/// ������ ���������� ��������� ������
template <class Owner>
void TBaseParameters<Owner>::ReadParameters(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++)
  {
    string argument = argv[i];
    for (int j = 0; j < mOptionsCount; j++)
    {
      if (mOptions[j]->IsNameEqual(argument))
      {
        if (!mOptions[j]->IsFlag())
        {
          i++;
          if (i < argc)
          {
            string value = argv[i];
            mOptions[j]->FromString(value);
            mOptions[j]->SetIsReadValue(true);
            break;
          }
        }
        else
        {
          mOptions[j]->FromString("1");
          mOptions[j]->SetIsReadValue(true);
          break;
        }
      }
    }
  }
}

/// ������ ����������� ������� ��� ���� �����
template <class Owner>
void TBaseParameters<Owner>::SetSeparator()
{
  for (int i = 0; i < mOptionsCount; i++)
  {
    mOptions[i]->SetSeparator(Separator);
  }
}


/// ������ ������� �� ����������
template <class Owner>
void TBaseParameters<Owner>::PrintHelp()
{
  printf("\n\nHelp:\n");
  for (int i = 0; i < mOptionsCount; i++)
  {
    printf("%s\n", mOptions[i]->GetHelpString().c_str());
  }
  for (int i = 0; i < mOtherOptionsCount; i++)
  {
    printf("%s\n", mOtherOptions[i]->GetHelpString().c_str());
  }
}

template <class Owner>
void TBaseParameters<Owner>::PrintParameters()
{
  for (int i = 0; i < mOptionsCount; i++)
  {
    printf("%s\n", mOptions[i]->GetCurrentStringValue().c_str());
  }
  for (int i = 0; i < mOtherOptionsCount; i++)
  {
    printf("%s\n", mOtherOptions[i]->GetCurrentStringValue().c_str());
  }
}

/// ��������� �� ������ ���������
template <class Owner>
bool TBaseParameters<Owner>::IsStart()
{
  if ((mIsHaveArguments == false) && (IsStartWithoutArguments == false))
    return false;
  return true;
}

/**
�������� ������������ ��� ��������� ����������
��� ��������������� ���������� ������� ������� ����� �������� ������!
*/
template <class Owner>
int TBaseParameters<Owner>::CheckValueParameters(int index = 0)
{
  if (mIsInit)
  {
    CheckValue(index);
    mIsInit = false;
    for (int i = 0; i < mOtherOptionsCount; i++)
    {
      for (int j = 0; j < mOptionsCount; j++)
      {
        if (mOtherOptions[i]->IsNameEqual(mOptions[j]->GetName()))
        {
          string oldBaseParameterValue = mOptions[j]->ToString();
          string oldOtherParameterValue = mOtherOptions[i]->ToString();

          if (oldBaseParameterValue != oldOtherParameterValue)
          {
            mOtherOptions[i]->FromString(oldBaseParameterValue);

            string newOtherParameterValue = mOtherOptions[i]->ToString();

            if (newOtherParameterValue == oldOtherParameterValue)
            {
              mOptions[j]->FromString(oldOtherParameterValue);
            }
          }
          break;
        }
      }
    }
    mIsInit = true;
  }
  return 0;
}

/// ������ �������� ��������� � ������ name
template <class Owner>
void TBaseParameters<Owner>::PrintParameter(string name)
{
  for (int i = 0; i < mOptionsCount; i++)
  {
    if (mOptions[i]->IsNameEqual(name))
    {
      printf("%s\n", mOptions[i]->GetCurrentStringValue().c_str());
      break;
    }
  }
  for (int i = 0; i < mOtherOptionsCount; i++)
  {
    if (mOtherOptions[i]->IsNameEqual(name))
    {
      printf("%s\n", mOtherOptions[i]->GetCurrentStringValue().c_str());
      break;
    }
  }
}

/// ������� ��������� � ������ name �������� val
template <class Owner>
void TBaseParameters<Owner>::SetVal(string name, string val)
{
  for (int i = 0; i < mOptionsCount; i++)
  {
    if (mOptions[i]->IsNameEqual(name))
    {
      mOptions[i]->FromString(val);
      break;
    }
  }

  for (int i = 0; i < mOtherOptionsCount; i++)
  {
    if (mOtherOptions[i]->IsNameEqual(name))
    {
      mOtherOptions[i]->FromString(val);
      break;
    }
  }
}
/// ������� ��������� � ������ name �������� val
template <class Owner>
void TBaseParameters<Owner>::SetVal(string name, void* val)
{
  for (int i = 0; i < mOptionsCount; i++)
  {
    if (mOptions[i]->IsNameEqual(name))
    {
      mOptions[i]->SetValue(val);
      break;
    }
  }
  for (int i = 0; i < mOtherOptionsCount; i++)
  {
    if (mOtherOptions[i]->IsNameEqual(name))
    {
      mOtherOptions[i]->SetValue(val);
      break;
    }
  }
}
/// ���������� ������ � ��������� ��������� � ������ name
template <class Owner>
string TBaseParameters<Owner>::GetStringVal(string name)
{
  for (int i = 0; i < mOptionsCount; i++)
  {
    if (mOptions[i]->IsNameEqual(name))
    {
      return mOptions[i]->ToString();
    }
  }

  for (int i = 0; i < mOtherOptionsCount; i++)
  {
    if (mOtherOptions[i]->IsNameEqual(name))
    {
      return mOtherOptions[i]->ToString();
    }
  }
}
/// ���������� �������� ��������� � ������ name
template <class Owner>
void* TBaseParameters<Owner>::GetVal(string name)
{
  for (int i = 0; i < mOptionsCount; i++)
  {
    if (mOptions[i]->IsNameEqual(name))
    {
      return mOptions[i]->GetValue();
    }
  }

  for (int i = 0; i < mOtherOptionsCount; i++)
  {
    if (mOtherOptions[i]->IsNameEqual(name))
    {
      return mOtherOptions[i]->GetValue();
    }
  }
}

/**
������������� ���������
\param[in] pt - ��� ���������
\param[in] sizeVal - ������ ������� ��������, ��� ����� ������ �� ����������� �������� - ������ ����� 1
\param[in] name - ��� ��������
\param[in] help - ��������� �� ������� �������
\param[in] com - �������� ������ ��� �������
\param[in] defVal - �������� �� ���������
*/
template <class Owner>
void TBaseParameters<Owner>::AddOption(EParameterType pt, string name, string defVal,
  string com, string help, int sizeVal)
{
  TBaseProperty<Owner>* option = 0;

  if (pt == Pint)
    option = new TInt<Owner> ();
  else if (pt == Pdouble)
    option = new TDouble<Owner> ();
  else if (pt == Pstring)
    option = new TString<Owner> ();
  else if (pt == PETypeMethod)
    option = new TETypeMethod<Owner> ();
  else if (pt == PETypeProcess)
    option = new TETypeProcess<Owner> ();
  else if (pt == PETypeCalculation)
    option = new TETypeCalculation<Owner> ();
  else if (pt == PELocalMethodScheme)
    option = new TELocalMethodScheme<Owner> ();
  else if (pt == PESeparableMethodType)
    option = new TESeparableMethodType<Owner> ();
  else if (pt == PEStopCondition)
    option = new TEStopCondition<Owner> ();
  else if (pt == Pbool)
    option = new TBool<Owner> ();
  else if (pt == Pints)
    option = new TInts<Owner> ();
  else if (pt == Pdoubles)
    option = new TDoubles<Owner> ();
  else if (pt == PEMapType)
    option = new TEMapType<Owner> ();

  option->InitializationParameterProperty(mOwner, 0, mOptionsCount, Separator, sizeVal,
    name, help, com, defVal);
  AddOption(option);
}

/// ���������� ��� ��������� ���� ������� � �����
template <class Owner>
void TBaseParameters<Owner>::CombineOptions(IBaseClass** otherOptions, int count)
{
  int newOtherOptionsCount = mOtherOptionsCount + count;
  if (newOtherOptionsCount >= mOtherOptionsSize)
  {
    IBaseClass** bufOptions = new IBaseClass* [mOtherOptionsSize];
    for (int i = 0; i < mOtherOptionsSize; i++)
    {
      bufOptions[i] = mOtherOptions[i];
    }

    delete [] mOtherOptions;

    mOtherOptions = new IBaseClass* [mOtherOptionsSize * 2];

    for (int i = 0; i < mOtherOptionsSize * 2; i++)
    {
      mOtherOptions[i] = 0;
    }

    for (int i = 0; i < mOtherOptionsSize; i++)
    {
      mOtherOptions[i] = bufOptions[i];
    }
    mOtherOptionsSize = mOtherOptionsSize * 2;

    delete [] bufOptions;
  }

  for (int i = 0; i < count; i++)
  {
    mOtherOptions[mOtherOptionsCount] = otherOptions[i];

    for (int j = 0; j < mOptionsCount; j++)
    {
      if (mOtherOptions[mOtherOptionsCount]->IsNameEqual(mOptions[j]->GetName()))
      {
        string oldBaseParameterValue = mOptions[j]->ToString();
        string oldOtherParameterValue = mOtherOptions[mOtherOptionsCount]->ToString();

        if (oldBaseParameterValue != oldOtherParameterValue)
        {

          mOptions[j]->FromString(oldOtherParameterValue);
          string newBaseParameterValue = mOptions[j]->ToString();

          if (newBaseParameterValue == oldBaseParameterValue)
          {
            mOtherOptions[mOtherOptionsCount]->FromString(oldBaseParameterValue);
          }
        }
        break;
      }
    }

    mOtherOptionsCount++;
  }
}

/// ���������� ��������� ��������
template <class Owner>
IBaseClass** TBaseParameters<Owner>::GetOptions()
{
  return mBaseTypeOptions;
}

/// ���������� ���������� �����
template <class Owner>
int TBaseParameters<Owner>::GetOptionsCount()
{
  return mOptionsCount;
}

template <class Owner>
void TBaseParameters<Owner>::Init(int argc, char* argv[], bool isMPIInit)
{
  mIsMPIInit = isMPIInit;
  mIsInit = false;
  mOptionsCount = 0;
  mOtherOptionsCount = 0;
  mOptions = 0;

  mOptionsSize = 100;
  mOtherOptionsSize = 100;

  mOptions = new TBaseProperty<Owner>* [mOptionsSize];
  mOtherOptions = new IBaseClass* [mOtherOptionsSize];
  mBaseTypeOptions = new IBaseClass* [mOptionsSize];
  for (int i = 0; i < mOptionsSize; i++)
  {
    mOptions[i] = 0;
    mBaseTypeOptions[i] = 0;
  }

  for (int i = 0; i < mOtherOptionsSize; i++)
  {
    mOtherOptions[i] = 0;
  }

  // ���������� ���� �� ��������� �������

  if (argc > 0)
  {
    mArgumentCount = argc;
    mAargumentValue = argv;
  }

  if (mArgumentCount <= 1)
    mIsHaveArguments = false;
  else
    mIsHaveArguments = true;

  // ������������� ������� ���������� �� ���������
  SetBaseDefaultParameters();
  // ������������� ������� ����������
  SetDefaultParameters();
  // ������ ����������� ��� ��������
  SetSeparator();
  // ���������� ��������� �� �������
  ReadParameters(mArgumentCount, mAargumentValue);
  // ���������� ��������� �� ������
  ReadConfigFile();
  // �������� ����������
  CheckValue();

  if ((mIsHaveArguments == false) && (IsPrintHelpWithoutArguments == false))
    mIsPrintHelp = false;
  else if (mIsHaveArguments == true)
    mIsPrintHelp = false;
  else
    mIsPrintHelp = true;
  mIsInit = true;

  CheckValueParameters();
}

template <class Owner>
TBaseParameters<Owner>::TBaseParameters()
{
  mConfigPath = "";
  mOwner = 0;
  mIsInit = false;
}

template <class Owner>
TBaseParameters<Owner>::TBaseParameters(TBaseParameters& parameters) : TCombinableBaseParameters()
{
  mIsInit = false;
  mOptionsCount = 0;
  mOtherOptionsCount = 0;
  mIsMPIInit = parameters.mIsMPIInit;
  mOptionsSize = parameters.mOptionsSize;
  mOtherOptionsSize = parameters.mOtherOptionsSize;
  mOwner = 0;
  mIsHaveArguments = parameters.mIsHaveArguments;
  IsPrintHelpWithoutArguments = parameters.IsPrintHelpWithoutArguments;
  IsStartWithoutArguments = parameters.IsStartWithoutArguments;
  mIsPrintHelp = parameters.mIsPrintHelp;
  mOtherOptionsCount = parameters.mOtherOptionsCount;

  mOptions = new TBaseProperty<Owner>* [mOptionsSize];
  mOtherOptions = new IBaseClass* [mOtherOptionsSize];
  mBaseTypeOptions = new IBaseClass* [mOptionsSize];
  for (int i = 0; i < mOptionsSize; i++)
  {
    mOptions[i] = 0;

    mBaseTypeOptions[i] = 0;
  }

  for (int i = 0; i < mOtherOptionsSize; i++)
  {
    mOtherOptions[i] = 0;
  }

  // ������������� ������� ���������� �� ���������
  SetBaseDefaultParameters();

  for (int i = 0; i < mOptionsCount; i++)
  {
    *mOptions[i] = *parameters.mOptions[i];
  }

  for (int i = 0; i < mOtherOptionsCount; i++)
  {
    mOtherOptions[i] = parameters.mOtherOptions[i];
  }

}

template <class Owner>
TBaseParameters<Owner>::~TBaseParameters()
{
  delete [] mOptions;
  mOptions = 0;
}


#endif //__BASE_PARAMETERS_H__
// - end of file ----------------------------------------------------------------------------------
