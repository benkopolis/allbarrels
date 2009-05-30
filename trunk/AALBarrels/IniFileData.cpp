/*
 * IniFileData.cpp
 *
 *  Created on: 2009-05-28
 *      Author: zby
 */

#include "iniparser.h"

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

void IniFileData::loadData(FILE *f)
{
	dictionary *dict;
	dict = iniparser_load(f);
	char *temp = NULL;
	this->_HowMany = iniparser_getint(dict, "data:HowMany", this->_HowMany);
	this->_ChangeVal = iniparser_getint(dict, "data:ChangeVal", this->_ChangeVal);
	strncpy(this->_ChangeWay, iniparser_getstring(dict, "data:ChangeWay", this->_ChangeWay), 3);
	this->_CheckTimes = iniparser_getboolean(dict, "other:CheckTimes", this->_CheckTimes);
	this->_Console = iniparser_getboolean(dict, "io:Console", this->_Console);
	this->_GenTable = iniparser_getboolean(dict, "other:GenTable", this->_GenTable);
	this->_Load = iniparser_getboolean(dict, "io:Load", this->_Load);
	this->_IterCount = iniparser_getint(dict, "data:IterCount", this->_IterCount);
	temp = iniparser_getstring(dict, "io:LoadFromFile", this->_LoadFromFile);
	if(strcmp(this->_LoadFromFile, temp) < 0 || strcmp(this->_LoadFromFile, temp) > 0 )
	{
		delete [] this->_LoadFromFile;
		this->_LoadFromFile = new char [strlen(temp)+1];
		strcpy(this->_LoadFromFile, temp);
	}
	this->_Sav = iniparser_getboolean(dict, "io:Sav", this->_Sav);
	temp = iniparser_getstring(dict, "io:SavToFile", this->_SavToFile);
	if(strcmp(this->_SavToFile, temp) < 0 || strcmp(this->_SavToFile, temp) > 0 )
	{
		delete [] this->_SavToFile;
		this->_SavToFile = new char [strlen(temp)+1];
		strcpy(this->_SavToFile, temp);
	}
	this->_ShowWork = iniparser_getboolean(dict, "other:ShowWork", this->_ShowWork);

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


/**
 * Metoda inicjująca pola klasy wartościami domyślnymi opisanymi w dokumentacji
 */
void IniFileData::initVariables()
{
	this->_HowMany = 100;
	this->_ChangeVal = 100;
	this->_CheckTimes = true;
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
