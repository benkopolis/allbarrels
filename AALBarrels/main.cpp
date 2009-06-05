/*
 *
 * main.cpp
 *
 *  Created on: 2009-03-13
 *      Author: zby
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <utility>
#include <cmath>

#ifdef _WIN32

#include <windows.h>

#endif

#include "IniFileData.h"
#include "InclinedPlane.h"



enum Flag {
	NONE = 0,
	MULT = 1 << 0,
	ADD = 1 << 1,
	TIME = 1 << 2,
	INT_SORT = 1 << 3
};






/**
 * ***********************************************************************************************
 * ********************************** FUNCTIONS DECLARATIONS *************************************
 * ***********************************************************************************************
 */

/**
 * @brief Funkcja ta wykonuje glowna funkcjonalnosc programu, poza generowaniem tabelki
 *
 * @param howMany - mowi ile razy robic przebieg petli
 * @param obj - obiekt na ktorym dokonywane bedzie sortowanie
 * @param flags - flagi mowiace o tym jak zmienia sie ilosc beczej i czy mierzyc czas
 * @param chVal - wartosc o jako ma sie zmieniac baseVal co obieg petli (ablo +chVal, albo *chVal)
 * @param baseVal - wartosc poczatkowa ilosci beczek
 * @return jezeli ma mierzyc czasy to zwraza tablice czasow zmierzonych z wartoscia -1 w ostatniej
 * 			komorce, a jak nie to zwraca NULL
 */
std::pair<double*, int*> sortNtimes(int howMany, AALBarrels::InclinedPlane* obj, Flag flags, int chVal, int baseVal);

double* q(std::pair< double*, int* > data, int s);

double* T(int *n, int s);

void printTable(std::pair< double*, int* > data, double *aq, int s, std::ostream &f);





/**
 * ***********************************************************************************************
 * ******************************************* MAIN PROGRAM **************************************
 * ***********************************************************************************************
 */

int main(int argc, char **argv)
{
	char *n = NULL;
	Flag flag = INT_SORT;
	int chV = 0, bV = 0, i=0;
	std::pair<double*, int*> result;
	if(argc == 1)
	{
		n = new char [strlen("./example.ini\0")];
		strcpy(n, "./example.ini");
	} else
	{
		n = new char [strlen(argv[1])+1];
		strcpy(n, argv[1]);
	}
	AALBarrels::IniFileData ifd(n); // tworze parsera pliku ini
	ifd.loadData(); // laduje dane
	delete [] n;
	n = NULL;
	AALBarrels::InclinedPlane ip;
	std::ofstream plik, plikT, plikS;
	std::ifstream plikL;
	if(ifd.getShowWork())
	{
		plik.open(ifd.getWorkLogFile(), std::ios_base::app | std::ios_base::out);
		if(plik.fail())
		{
			std::cout << "Nie udalo otworzyc sie pliku z logami\n";
			ip.makeLogs(std::cout);
		} else
			ip.makeLogs(plik);
	}
	if(ifd.getGenTable())
	{
		plikT.open(ifd.getTableFile(), std::ios_base::app | std::ios_base::out);
		if(plikT.fail())
			std::cout << "Nie udalo otworzyc sie pliku do tabelki.\n" << "Tabelka nie zostanie wygenerowana\n";
		flag = (Flag)(flag | TIME);
	}
	if(!strcmp(ifd.getChangeWay(), "add"))
		flag = (Flag)(flag | ADD);
	else
		flag = (Flag)(flag | MULT);
	if(ifd.getLoad())
	{
		plikL.open(ifd.getLoadFromFile(), std::ios::in);
		if(plikL.fail())
			std::cout << "Nie udalo sie otworzyc pliku do LOAD\n";
	}
	if(ifd.getSav())
	{
		plikS.open(ifd.getSavToFile(), std::ios_base::app | std::ios_base::out);
		if(plikS.fail())
			std::cout << "Nie udalo sie otworzyc pliku do SAV \n";
	}
	chV = ifd.getChangeVal();
	bV = ifd.getHowMany();
	i = ifd.getIterCount();


	result = sortNtimes(i, &ip, flag, chV, bV);
	double *qn = q(result, i);
	if(plikT.is_open())
		printTable(result, qn, i, plikT);

	ip.stopLogs();

	plik.flush();
	plik.close();
	plikT.flush();
	plikT.close();
//	plikL.flush();
	plikL.close();
	plikS.flush();
	plikS.close();

	std::cout << "koooooonieeec" << std::endl;


	delete [] n;
	n = NULL;

#ifdef WIN32
	system("PAUSE");
#endif

	return 0;
}




/**
 * ***********************************************************************************************
 * ********************************** FUNCTIONS DEFINITIONS **************************************
 * ***********************************************************************************************
 */


std::pair<double*, int*> sortNtimes(int howMany, AALBarrels::InclinedPlane* obj, Flag flags, int chVal, int baseVal)
{
	double *times;
	int *n;
	AALBarrels::Barrel **b;
	int sort_type;
	int val = baseVal;
	if(flags & INT_SORT)
		sort_type = AALBarrels::InclinedPlane::IntelligentSort;
	if(flags & TIME)
	{
		times = new double [howMany+1];
		n = new int [howMany+1];
	}
	else
		times = NULL;
	for(int i=0; i<howMany; ++i)
	{
		b = AALBarrels::InclinedPlane::generateBarrels(val);
		obj->addBarrel(b, val);
		if(times)
		{
			times[i] = clock();
			n[i] = val;
		}
		obj->startSort((AALBarrels::InclinedPlane::SortType)sort_type);
		if(times)
			times[i] = clock() - times[i];
		obj->clear();
		if((flags & MULT) && !(flags & ADD))
			val = val + chVal * baseVal;
		if(flags & ADD)
			val = val + chVal;
	}
	times[howMany] = 0;
	n[howMany] = 0;
	return std::make_pair(times, n);
}


double* q(std::pair< double*, int* > data, int s)
{
	double Tnmediana = 0, tnmediana = 0;
	double *Tn = T(data.second, s);
	double *ret = new double [s];
	if(s%2 == 0)
	{
		Tnmediana = Tn[s/2];
		tnmediana = data.first[s/2];
	} else
	{
		Tnmediana = (Tn[s/2] + Tn[s/2 +1])/2.0;
		tnmediana = (data.first[s/2] + data.first[s/2 + 1])/2.0;
	}
	for(int i=0; i<s; ++i)
		ret[i] = (data.first[i] * Tnmediana)/(Tn[i] * tnmediana);
	return ret;
}

double* T(int *n, int s)
{
	double *ret = new double [s];
	for(int i=0; i<s; ++i)
		ret[i] = pow((double)n[i], 2.0)/6.0 + (double)5*(n[i])/6;
	return ret;
}

void printTable(std::pair< double*, int* > data, double *aq, int s, std::ostream &f)
{
	f << "N: \t t(n): \t q(n): \n";
	for(int i=0; i<s; ++i)
	{
		f << data.second[i] << "\t" << data.first[i] << "\t" << aq[i] << "\n" ;
	}
}
