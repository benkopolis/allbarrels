/*
 * IniFileData.h
 *
 *  Created on: 2009-05-28
 *      Author: zby
 */

#ifndef INIFILEDATA_H_
#define INIFILEDATA_H_

#include <iostream>
#include <fstream>


using namespace std;

namespace AALBarrels
{

class IniFileData
{
public:
	IniFileData();
	IniFileData(char *fileName);
	virtual ~IniFileData();

	/**
	 * Metoda pobiera dane z pliku i zapisuje w zmiennych prywatnych klasy.
	 */
	bool loadData();

	/**
	 * -------------------------------------------------------------------------------------
	 *  PUBLIC GETTERS AND SETTERS
	 *  ------------------------------------------------------------------------------------
	 */

    char *getIniFileName() const;

    void setIniFileName(char *_iniFileName);

    int getHowMany() const;

    char* getChangeWay() const;

    int getChangeVal() const;

    int getIterCount() const;

    bool getSav() const;

    char *getSavToFile() const;

    bool getLoad() const;

    char *getLoadFromFile() const;

    bool getConsole() const;

    bool getGenTable() const;

    bool getShowWork() const;

    bool getCheckTimes() const;

    char *getWorkLogFile() const;

    char *getTableFile() const;


    /**
	 * -------------------------------------------------------------------------------------
	 *  PROTECTED GETTERS AND SETTERS
	 *  ------------------------------------------------------------------------------------
	 */

protected:

    void setHowMany(int _HowMany);

    void setChangeVal(int _ChangeVal);

    void setChangeWay(char _ChangeWay[4]);
    void setIterCount(int _IterCount);

    void setSav(bool _Sav);

    void setSavToFile(char *_SavToFile);

    void setLoad(bool _Load);

    void setLoadFromFile(char *_LoadFromFile);

    void setConsole(bool _Console);

    void setGenTable(bool _GenTable);

    void setShowWork(bool _ShowWork);

    void setCheckTimes(bool _CheckTimes);

    int getint(ifstream *f, int def);

    bool getboolean(ifstream *f, bool def);

    char* getstring(ifstream *f, const char* def);

    void setTableFile(char *_TableFile);

    void setWorkLogFile(char *_WorkLogFile);

private:

	void initVariables();


	/**
	 * CLASS VARIABLES
	 */

	char *_iniFileName;

	/**
	 * jak duzo beczek za pierwszym razem wygenerowac - domyslnie 100
	 */
	int _HowMany;

	/**
	 * Sposób zwiększania ilości danych - może być mult lub add lub non
	 * domyślnie add
	 */
	char _ChangeWay[4];

	/**
	 * Wartość o jaką dokonywana jest zmiana
	 * domyślnie 100
	 */
	int _ChangeVal;

	/**
	 * Ilość powtórzeń przebiegów algorytmu - domyślnie jest 10
	 */
	int _IterCount;

	/**
	 * Mówi czy zapisywać dane do pliku. Domyślnie nie, ale jak tak, to nazwę pliku
	 * bierze ze zmiennej _SavToFile
	 */
	bool _Sav;

	/**
	 * Nazwa pliku do którego trzeba wygenerować dane. Domyślnie dane.dat
	 */
	char *_SavToFile;

	/**
	 * Mówi czy wczytywać dane. Jak tak to nazwe pliku
	 * z danymi pobieraz ze zmiennej LoadFromFile.
	 * Domyślnie jest false.
	 */
	bool _Load;

	/**
	 * Nazwa pliku z danymi do załadowania. Domyślnie dane.dat
	 */
	char *_LoadFromFile;

	/**
	 * Mówi czy pobierać dane z konsoli. Domyślnie false.
	 */
	bool _Console;

	/**
	 * mówi czy generować tabelke.
	 */
	bool _GenTable;

	/**
	 * nazwa pliku do ktorego generowana bedzie tabelka
	 */
	char *_TableFile;

	/**
	 * Mówi czy pokazywać przebiegi sortowania.
	 */
	bool _ShowWork;

	/**
	 * nazwa pliku w ktorym pokazana jest praca
	 */
	char *_WorkLogFile;

	/**
	 * Mówi czy mierzyć czasy.
	 */
	bool _CheckTimes;
};

}

#endif /* INIFILEDATA_H_ */
