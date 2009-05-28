/*
 * IniFileData.cpp
 *
 *  Created on: 2009-05-28
 *      Author: zby
 */

#include <cstring>

#include "IniFileData.h"

namespace AALBarrels
{

IniFileData::IniFileData()
{
	this->initVariables();
	this->_iniFileName = NULL;
}

IniFileData::IniFileData(char *fileName)
{
	this->initVariables();
	this->_iniFileName = new char [strlen(fileName)];
	strcpy(this->_iniFileName, fileName);
}

IniFileData::~IniFileData()
{
	delete this->_iniFileName;
	delete [] this->_LoadFromFile;
	delete [] this->_SavToFile;
}




/**
 * -----------------------------------------------------------------------------------------
 * 								CLASS GETTERS AND SETTERS
 * -----------------------------------------------------------------------------------------
 */
char* IniFileData::getIniFileName() const
{
    return _iniFileName;
}

void IniFileData::setIniFileName(char *_iniFileName)
{
    this->_iniFileName = _iniFileName;
}

int IniFileData::getHowMany() const
{
    return _HowMany;
}

char* IniFileData::getChangeWay() const
{
    return (char*)_ChangeWay;
}

int IniFileData::getChangeVal() const
{
    return _ChangeVal;
}

int IniFileData::getIterCount() const
{
    return _IterCount;
}

bool IniFileData::getSav() const
{
    return _Sav;
}

char* IniFileData::getSavToFile() const
{
    return _SavToFile;
}

bool IniFileData::getLoad() const
{
    return _Load;
}

char* IniFileData::getLoadFromFile() const
{
    return _LoadFromFile;
}

bool IniFileData::getConsole() const
{
    return _Console;
}

bool IniFileData::getGenTable() const
{
    return _GenTable;
}

bool IniFileData::getShowWork() const
{
    return _ShowWork;
}

bool IniFileData::getCheckTimes() const
{
    return _CheckTimes;
}

/**
 * -------------------------------------------------------------------------------------
 *  PROTECTED GETTERS AND SETTERS
 *  ------------------------------------------------------------------------------------
 */

void IniFileData::setHowMany(int _HowMany)
{
     this->_HowMany = _HowMany;
}

void IniFileData::setChangeVal(int _ChangeVal)
{
    this->_ChangeVal = _ChangeVal;
}

void IniFileData::setChangeWay(char _ChangeWay[4])
{
    strcpy(this->_ChangeWay, _ChangeWay);
}

void IniFileData::setIterCount(int _IterCount)
{
    this->_IterCount = _IterCount;
}

void IniFileData::setSav(bool _Sav)
{
    this->_Sav = _Sav;
}

void IniFileData::setSavToFile(char *_SavToFile)
{
    this->_SavToFile = _SavToFile;
}

void IniFileData::setLoad(bool _Load)
{
    this->_Load = _Load;
}

void IniFileData::setLoadFromFile(char *_LoadFromFile)
{
    this->_LoadFromFile = _LoadFromFile;
}

void IniFileData::setConsole(bool _Console)
{
    this->_Console = _Console;
}

void IniFileData::setGenTable(bool _GenTable)
{
    this->_GenTable = _GenTable;
}

void IniFileData::setShowWork(bool _ShowWork)
{
    this->_ShowWork = _ShowWork;
}

void IniFileData::setCheckTimes(bool _CheckTimes)
{
    this->_CheckTimes = _CheckTimes;
}



void IniFileData::initVariables()
{
	this->_HowMany = 100;
	this->_ChangeVal = 100;
	strcpy(this->_ChangeWay, "add");
	this->_Console = false;
	this->_GenTable = true;
	this->_IterCount = 10;
	this->_Load = false;
	this->_LoadFromFile = new char [30];
	strcpy(this->_LoadFromFile, "dane.dat");
	this->_Sav = false;
	this->_SavToFile = new char [30];
	strcpy(this->_SavToFile, "dane.dat");
	this->_ShowWork = false;
}


}
