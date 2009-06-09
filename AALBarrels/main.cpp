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
#include <sys/time.h>
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

void consoleWork(AALBarrels::InclinedPlane &ip);

std::pair<double*, int*> sortFromFile(AALBarrels::InclinedPlane &ip, Flag flags, const char *fileName);

void generateDataToFile(const char *fileName, Flag flags, int iterCount, int baseVal, int chVal);


/**
 * ***********************************************************************************************
 * ******************************************* MAIN PROGRAM **************************************
 * ***********************************************************************************************
 */

int main(int argc, char **argv)
{
	char *n = NULL;
	bool cont = true;
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
	/* ------------------------------------------------------------------------------------ */
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
	/* ------------------------------------------------------------------------------------ */
	if(ifd.getGenTable())
	{
		plikT.open(ifd.getTableFile(), std::ios_base::app | std::ios_base::out);
		if(plikT.fail())
			std::cout << "Nie udalo otworzyc sie pliku do tabelki.\n" << "Tabelka nie zostanie wygenerowana\n";
		flag = (Flag)(flag | TIME);
	}
	/* ------------------------------------------------------------------------------------ */
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
	/* ------------------------------------------------------------------------------------ */
	if(ifd.getSav())
	{
		plikS.open(ifd.getSavToFile(), std::ios_base::app | std::ios_base::out);
		if(plikS.fail())
			std::cout << "Nie udalo sie otworzyc pliku do SAV \n";
	}
	/* ------------------------------------------------------------------------------------ */
	if(ifd.getCheckTimes())
	{
		flag = (Flag)(flag | TIME);
	}
	/* ------------------------------------------------------------------------------------ */
	if(ifd.getConsole())
	{
		consoleWork(ip);
		cont = false;
	} else if(ifd.getSav()) {
		// void generateDataToFile(const char *fileName, Flag flags, int iterCount, int baseVal, int chVal)
		generateDataToFile(ifd.getSavToFile(), flag, ifd.getIterCount(), ifd.getHowMany(), ifd.getChangeVal());
		cont = false;
	} else if(ifd.getLoad())
	{
		result = sortFromFile(ip, flag, ifd.getLoadFromFile());
	}




	while(cont) {


		chV = ifd.getChangeVal();
		bV = ifd.getHowMany();
		i = ifd.getIterCount();

		if(!ifd.getLoad())
			result = sortNtimes(i, &ip, flag, chV, bV);
		double *qn = q(result, i);

		if(plikT.is_open())
			printTable(result, qn, i, plikT);
		else if(result.first != NULL)
		{
			for(int j=0; j<i; ++j)
				std::cout << "N: " << result.second << " t(n): " << result.first << "\n";
		}
		cont = false;
	};
	/* ------------------------------------------------------------------------------------ */
	/**
	 * Czyszczenie pliczkow, tabliczek i roznych takich
	 */
	/* ------------------------------------------------------------------------------------ */
	ip.stopLogs();

	plik.flush();
	plik.close();
	plikT.flush();
	plikT.close();

	plikL.close();
	plikS.flush();
	plikS.close();
	/* ------------------------------------------------------------------------------------ */
	std::cout << "koooooonieeec" << std::endl;


	delete [] n;
	n = NULL;
	/* ------------------------------------------------------------------------------------ */
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

/* ------------------------------------------------------------------------------------ */
/**
 * generuje na podstawie pliku ini dane i wykonuje sekwencje sortowac. Mierzy czasy i zwraca
 * je po bozemu, zeby moznabylo wygenerowac tabelke.
 */
/* ------------------------------------------------------------------------------------ */
std::pair<double*, int*> sortNtimes(int howMany, AALBarrels::InclinedPlane* obj, Flag flags, int chVal, int baseVal)
{
	double *times;
	timeval t1, t2;
	int *n = NULL;
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
//			times[i] = (double)clock();
			gettimeofday(&t1, NULL);
			n[i] = val;
		}
		obj->startSort((AALBarrels::InclinedPlane::SortType)sort_type);
		if(times)
		{
//			times[i] = (double)clock() - times[i];
			gettimeofday(&t2, NULL);
			times[i] = (t2.tv_sec - t1.tv_sec) * 1000.0;
			times[i] += (t2.tv_usec - t1.tv_usec) / 1000.0;
		}
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

/* ------------------------------------------------------------------------------------ */
/**
 * Liczy q(n)
 */
/* ------------------------------------------------------------------------------------ */
double* q(std::pair< double*, int* > data, int s)
{
	double Tnmediana = 0, tnmediana = 0;
	double *Tn = T(data.second, s);
	double *ret = new double [s];
	if(s%2 == 1)
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

/* ------------------------------------------------------------------------------------ */
/**
 * Liczenie dokladniej wartosci T(n)
 */
/* ------------------------------------------------------------------------------------ */
double* T(int *n, int s)
{
	double *ret = new double [s];
	//	Wspolczyniki srednie to:
	double	A = 0.0248586;
	double	B = 0.0745758;
	double	C = 0.000732242;
	for(int i=0; i<s; ++i)
		ret[i] = pow((double)n[i], 2.0)*A + (double)(n[i])*(B+C);
	return ret;
}

/* ------------------------------------------------------------------------------------ */
/**
 * drukuje tabele czasow
 */
/* ------------------------------------------------------------------------------------ */
void printTable(std::pair< double*, int* > data, double *aq, int s, std::ostream &f)
{
	f << "N: \t t(n): \t q(n): \n";
	for(int i=0; i<s; ++i)
	{
		f << data.second[i] << "\t" << data.first[i] << "\t" << aq[i] << "\n" ;
	}
}

/* ------------------------------------------------------------------------------------ */
/**
 * Pozwala na prace w konsoli
 */
/* ------------------------------------------------------------------------------------ */
void consoleWork(AALBarrels::InclinedPlane &ip)
{
	std::cout << "Prosze podawac beczki: R, B, G. Dowolny inny klawisz\n"
			"konczy wprowadzanie. Enter potwierdza dotychczas wprowadzone - mozna\n"
			"dalej wprowadzac.\n";
	char c = '\n';
	int s = 0;
	std::cin >> c;
	while(c == '\n' || c == 'R' || c == 'B' || c == 'G' || c == 'r' || c == 'b' || c == 'g')
	{
		if(c != '\n') {
			ip.addBarrel(AALBarrels::Barrel::readBarrel(c));
			++s;
		}
		std::cin >> c;
	}
	while(s < 3)
	{
		ip.addBarrel(AALBarrels::Barrel::readBarrel('G'));
		++s;
	}
}

/* ------------------------------------------------------------------------------------ */
/**
 * Pobiera dane z pliku - jeden zbior to jedna linia - nastepnie wykonuje sortowanie,
 * tworzy tez tabele czasow i zwraca ja po bozemu, zeby mozna bylo tabelke wygenerowac.
 */
/* ------------------------------------------------------------------------------------ */
std::pair<double*, int*> sortFromFile(AALBarrels::InclinedPlane &ip, Flag flags, const char *fileName)
{
	double *times;
	std::ifstream pliczek;
	std::pair<AALBarrels::Barrel** , int> para;

	timeval t1, t2;
	int *n = NULL;
	int sort_type;
	int nCount = 0, old = 10;
	if(flags & INT_SORT)
		sort_type = AALBarrels::InclinedPlane::IntelligentSort;

	pliczek.open(fileName, std::ios_base::in);
	if(pliczek.fail()) {
		std::cout << "Nie udalo sie otworzyc pliku z danymi. Koniec programu\n";
		return std::make_pair(times, n);
	}
	if(flags & TIME)
		{
			times = new double [10];
			n = new int [10];
		}
		else
			times = NULL;
	do {

		para =  AALBarrels::InclinedPlane::readLineOfBarrels(&pliczek);
		if(para.second == 0)
			continue;
		ip.addBarrel(para.first, para.second);

		if(times)
			++nCount;
		if(nCount > old) // alokuje pamiec na tablice jak potrzeba
		{
			old = old *2;
			double *pomtim = new double [old];
			int *pomn = new int [old];
			memcpy(pomtim, times, sizeof(double)*old/2);
			memcpy(pomn, n, sizeof(int)*old/2);
		}
		// sortowanie wlasciwe
		if(times)
		{
			gettimeofday(&t1, NULL);
			n[nCount-1] = ip.size();
		}
		ip.startSort((AALBarrels::InclinedPlane::SortType)sort_type);
		if(times)
		{
			gettimeofday(&t2, NULL);
			times[nCount-1] = (t2.tv_sec - t1.tv_sec) * 1000.0;
			times[nCount-1] += (t2.tv_usec - t1.tv_usec) / 1000.0;
		}
		ip.clear();
		// koniec petli
	} while(pliczek.good());
	pliczek.close();
	return std::make_pair(times, n);
}

/* ------------------------------------------------------------------------------------ */
/**
 * do podanego pliku na podstawie danych z pliku ini generuje linie beczek
 */
/* ------------------------------------------------------------------------------------ */
void generateDataToFile(const char *fileName, Flag flags, int iterCount, int baseVal, int chVal)
{
	std::ofstream plik;
	int val = baseVal;
	AALBarrels::InclinedPlane ip;
	AALBarrels::Barrel **b =  NULL;
	plik.open(fileName, std::ios_base::app | std::ios_base::out);
	if(plik.fail())	{
		std::cout << "Nie udalo sie otworzyc pliku - dane nie beda wygenerowane\n";
		return;
	}
	for(int i = 0; i < iterCount; ++i)
	{
		b = AALBarrels::InclinedPlane::generateBarrels(val);
		ip.addBarrel(b, val);
		ip.printBarrelsToStream(plik);

		if((flags & MULT) && !(flags & ADD))
			val = val + chVal * baseVal;
		if(flags & ADD)
			val = val + chVal;
		ip.clear();
	}
	plik.flush();
	plik.close();
}



