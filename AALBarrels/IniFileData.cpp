/*
 * IniFileData.cpp
 *
 *  Created on: 2009-05-28
 *      Author: zby
 */

#include "IniFileData.h"


using namespace std;


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
	this->_iniFileName = new char [strlen(fileName)+1];
	strcpy(this->_iniFileName, fileName);
}

IniFileData::~IniFileData()
{
	delete this->_iniFileName;
	delete [] this->_LoadFromFile;
	delete [] this->_SavToFile;
}

bool IniFileData::loadData()
{
	ifstream *ini = new ifstream();
	char t[100];
	char *temp = NULL;
	ini->open(this->_iniFileName, ios_base::in);
	if(ini->is_open() == false)
		return false;
	while(ini->good())
	{
		*ini >> t;
		if(!strcmp(t, "HowMany"))
			this->_HowMany = getint(ini, this->_HowMany);
		else if(!strcmp(t, "ChangeVal"))
			this->_ChangeVal = getint(ini, this->_ChangeVal);
		else if(!strcmp(t, "ChangeWay"))
			strncpy(this->_ChangeWay, getstring(ini, this->_ChangeWay), 3);
		else if(!strcmp(t, "CheckTimes"))
			this->_CheckTimes = getboolean(ini, this->_CheckTimes);
		else if(!strcmp(t, "Console"))
			this->_Console = getboolean(ini, this->_Console);
		else if(!strcmp(t, "GenTable"))
			this->_GenTable = getboolean(ini, this->_GenTable);
		else if(!strcmp(t, "Load"))
			this->_Load = getboolean(ini, this->_Load);
		else if(!strcmp(t, "IterCount"))
			this->_IterCount = getint(ini, this->_IterCount);
		else if(!strcmp(t, "LoadFromFile"))
		{
			temp = getstring(ini, this->_LoadFromFile);
			if(strcmp(this->_LoadFromFile, temp) < 0 || strcmp(this->_LoadFromFile, temp) > 0 )
			{
				delete [] this->_LoadFromFile;
				this->_LoadFromFile = new char [strlen(temp)+1];
				strcpy(this->_LoadFromFile, temp);
			}
		} else if(!strcmp(t, "Sav"))
			this->_Sav = getboolean(ini, this->_Sav);
		else if(!strcmp(t, "SavToFile"))
		{
			temp = getstring(ini, this->_SavToFile);
			if(strcmp(this->_SavToFile, temp) < 0 || strcmp(this->_SavToFile, temp) > 0 )
			{
				delete [] this->_SavToFile;
				this->_SavToFile = new char [strlen(temp)+1];
				strcpy(this->_SavToFile, temp);
			}
		} else if(!strcmp(t, "ShowWork"))
			this->_ShowWork = getboolean(ini, this->_ShowWork);
	}
	return true;
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
    return (char*)(((_ChangeWay)));
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

    char *IniFileData::getSavToFile() const
    {
        return _SavToFile;
    }

    bool IniFileData::getLoad() const
    {
        return _Load;
    }

    char *IniFileData::getLoadFromFile() const
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
     * Metoda wczytuje inta z podanego strumienia, jezeli wczytani go niepoprawnie to czysci flagi
     * bledow i ustawia wskaznik pozycji w strumieniu na zachowany wczesniej wskaznik pozycji przed
     * przeczytaniem i zwraca wartosc podana w parametrze def. W razie sukcesu zwraca wartosc wczytana ze strumienia.
     */
    int AALBarrels::IniFileData::getint(ifstream *f, int def)
    {
        int k, l;
        l = f->tellg();
        if(f->good())
            *f >> k;

        if(!f->good()){
            k = def;
            f->clear();
            f->seekg(l);
        }
        return k;
    }

    /**
     * Metoda z podanego strumienia wczytuje stringa. Po pierwszym wczytanym znaku okresla czy string
     * reprezentuje wartosc true (y, Y, T, t) czy false (n, f, N, F) i przypisuja ja do zwracanej zmiennej.
     * Jak string ten nie da sie jednoznacznie zinterpretowac, to pozycja w strumieniu jest cofana do poprzedniej
     * i zwracana jest wartosc podana w parametrze def.
     */
    bool AALBarrels::IniFileData::getboolean(ifstream *f, bool def)
    {
        int l = f->tellg();
        bool r;
        char t[100];
        if(f->good())
            *f >> t;
        if(f->good())
        {
			if(t[0] == 't' || t[0] == 'y' || t[0] == 'Y' || t[0] == 'T')
				r = true;

			else if(t[0] == 'n' || t[0] == 'f' || t[0] == 'F' || t[0] == 'N')
					r = false;
			else
			{
				r = def;
				f->seekg(l);
			}
        }
        return r;
    }

    char *AALBarrels::IniFileData::getstring(ifstream *f, const char *def)
    {
    	char *t = new char [100];
    	if(f->good())
    		*f >> t;
    	if(!f->good())
    	{
    		delete [] t;
    		t = new char [strlen(def)+1];
    		strcpy(t, def);
    	}
    	return t;
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
