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

#ifdef _WIN32

#include <windows.h>

#endif

#include "iniparser.h"
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
double* sortNtimes(int howMany, AALBarrels::InclinedPlane* obj, Flag flags, int chVal, int baseVal);









/**
 * ***********************************************************************************************
 * ******************************************* MAIN PROGRAM **************************************
 * ***********************************************************************************************
 */

int main(int argc, char **argv)
{
	sortNtimes(10, (new AALBarrels::InclinedPlane()), (Flag)(ADD | INT_SORT), 10, 20);
	std::cout << "koooooonieeec" << std::endl;

	system("PAUSE");

	return 0;
}




/**
 * ***********************************************************************************************
 * ********************************** FUNCTIONS DEFINITIONS **************************************
 * ***********************************************************************************************
 */


double* sortNtimes(int howMany, AALBarrels::InclinedPlane* obj, Flag flags, int chVal, int baseVal)
{
	double *times;
	AALBarrels::Barrel **b;
	int sort_type;
	int val = baseVal;
	if(flags & INT_SORT)
		sort_type = AALBarrels::InclinedPlane::IntelligentSort;
	if(flags & TIME)
		times = new double [howMany+1];
	else
		times = NULL;
	for(int i=0; i<howMany; ++i)
	{
		b = AALBarrels::InclinedPlane::generateBarrels(val);
		obj->addBarrel(b, val);
		if(times)
			times[i] = time(NULL);
		obj->startSort((AALBarrels::InclinedPlane::SortType)sort_type);
		if(times)
			times[i] = time(NULL) - times[i];
		obj->clear();
		if((flags & MULT) && !(flags & ADD))
			val = val + chVal * baseVal;
		if(flags & ADD)
			val = val + chVal;
	}
	return times;
}

