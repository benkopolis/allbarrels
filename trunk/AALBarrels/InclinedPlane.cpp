/*
 * InclinedPlane.cpp
 *
 *  Created on: 2009-03-13
 *      Author: zby
 */

#include <vector>
#include <utility>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>


#include "InclinedPlane.h"
#include "Barrel.h"
#include "BarrelException.h"

namespace AALBarrels
{

/**
 * ********************************************************************************
 * ************************* CLASS PUBLIC CONSTRUCTOR *****************************
 * ********************************************************************************
 * ********************** InclinedPlane::InclinedPlane() **************************
 * ********************************************************************************
 */
InclinedPlane::InclinedPlane()
{
	this->quantityOfBlue = 0;
	this->quantityOfGreen = 0;
	this->quantityOfRed = 0;
}

/**
 * ********************************************************************************
 * ************************* CLASS PUBLIC DESTRUCTOR ******************************
 * ********************************************************************************
 * *********************** InclinedPlane::~InclinedPlane() ************************
 * ********************************************************************************
 */
InclinedPlane::~InclinedPlane()
{
}

/**
 * ********************************************************************************
 * *************************** CLASS PUBLIC METHOD ********************************
 * ********************************************************************************
 * ***************** void InclinedPlane::addBarrel(Barrel *b) *********************
 * ********************************************************************************
 */
Barrel* InclinedPlane::addBarrel(Barrel *b)
{
	Barrel *r;
	r = this->list.addOnEnd(b);
	try
	{
		switch(b->getColor())
		{
		case Barrel::RED:
			++this->quantityOfRed;
			break;
		case Barrel::BLUE:
			++this->quantityOfBlue;
			break;
		case Barrel::GREEN:
			++this->quantityOfGreen;
			break;
		default:
			BarrelException c(BarrelException::NoColorSet);
			std::string s("Threw from void InclinedPlane::addBarrel(Barrel *b)");
			c.setMessage(s);
			throw c;
			break;
		}
	} catch(BarrelException e)
	{
		std::cerr << e.getMessage();
	};
	return r;
}

void InclinedPlane::addBarrel(Barrel** b, int size)
{
	for(int i=0; i<size; ++i)
	{
		this->addBarrel(b[i]);
	}
}


void InclinedPlane::printBarrelsToStream(std::ostream &f) const
{
	Barrel* ii = this->list.start();
	char c = '\0';
	//for(; ii != list.end(); ++ii, ++i)
	while(ii != list.end())
	{
		c = ii->printBarrel();
		f << c;
		ii = ii->next();
	}
	f << "\n";
}


void InclinedPlane::printBarrelsToStream(std::ostream &f, int index) const
{
	Barrel* ii = this->list.start();
	int i = 0;
	char c = '\0';
	//for(; ii != list.end(); ++ii, ++i)
	while(ii != list.end())
	{
		c = ii->printBarrel();
		f << c;
		if(i == index)
			std::cout << "||";
		ii = ii->next();
		++i;
	}
	f << "\n";
}


/**
 * ********************************************************************************
 * ************************** CLASS PUBLIC METHOD *********************************
 * ********************************************************************************
 * ****************** void InclinedPlane::printBarrels() const ********************
 * ********************************************************************************
 */
void InclinedPlane::printBarrels() const
{
	this->printBarrelsToStream(std::cout);
}

/**
 * ********************************************************************************
 * ************************** CLASS PUBLIC METHOD ********************************
 * ********************************************************************************
 * ************** void InclinedPlane::printBarrels(int index) const ***************
 * ********************************************************************************
 */
void InclinedPlane::printBarrels(int index) const
{
	this->printBarrelsToStream(std::cout, index);
}

/**
 * ********************************************************************************
 * ************************** CLASS PUBLIC METHOD *********************************
 * ********************************************************************************
 * ****************** void InclinedPlane::startSort(SortType s) *******************
 * ********************************************************************************
 */
void InclinedPlane::startSort(SortType s)
{
//	Barrel *pom = new Barrel(Barrel::GREEN);
//	Barrel *tmp;
//	bool cheat = false;
	if(this->quantityOfGreen < 3)
		return;
//	if(this->list.size() % 3 == 0) // dla podzielnych przez 3 sie wykrzacza: dodaje 1 beczke
//	{
//		tmp = this->addBarrel(pom);
//		cheat = true;
//	}
	if(s == InclinedPlane::IntelligentSort)
		this->intelligentSort();
//	delete pom;
//	if(cheat == true) // jak dodalem jedna beczke, to ja usuwam
//		this->list.erase(tmp);

}


/**
 * ********************************************************************************
 * ************************** CLASS PUBLIC METHOD *********************************
 * ********************************************************************************
 * ************** Barrel* InclinedPlane::generateBarrels(int size) ****************
 * ********************************************************************************
 */
Barrel** InclinedPlane::generateBarrels(int size)
{
	Barrel **r = new Barrel* [size];
	int i=0, green=0;
	Barrel::Color c=Barrel::NONE;
	srand(time(NULL));
	while(i<size)
	{
		c = (Barrel::Color)(((int)rand())%(int)Barrel::GREEN + 1);
		if(green < 3 && c == Barrel::GREEN)
			++green;
		r[i] = new Barrel(c);
		++i;
	}
	while(i>0 && green < 3)
	{
		--i;
		if(r[i]->getColor() != Barrel::GREEN)
		{
			r[i]->setColor(Barrel::GREEN);
			++green;
		}
	}
	return r;
}

Barrel** InclinedPlane::readLineOfBarrels(std::ifstream *f)
{
	char c;
	int i = 0;
	Barrel **ret;
	char *tab=NULL;
	const char *cp=NULL;
	std::string str;
	std::getline(*f, str);
	cp = str.c_str();
	tab = new char [strlen(cp)+1];
	ret = new Barrel* [strlen(cp)];
	strcpy(tab, cp);
	c = tab[0];
	while(c != '\0' && c != '\n')
	{
		ret[i] = Barrel::readBarrel(c);
		++i;
		c = tab[i];
	}
	return ret;
}

Barrel** InclinedPlane::convertStringToBarrels(const char *str)
{
	int i = strlen(str);
	Barrel **b = new Barrel* [i];
	for(int j = 0; j < i; ++j)
		b[j] = Barrel::readBarrel(str[j]);
	return b;
}


/**
 * ********************************************************************************
 * ************************** CLASS PUBLIC METHOD *********************************
 * ********************************************************************************
 * ************************** void InclinedPlane::clear() *************************
 * ********************************************************************************
 */
void InclinedPlane::clear()
{
	this->list.clear();
	this->quantityOfBlue = 0;
	this->quantityOfGreen = 0;
	this->quantityOfRed = 0;
}

/**
 * przypisuje strumien wyjsciowy do strumienia logowania
 */
void InclinedPlane::makeLogs(std::ostream &a)
{
	this->log=&a;
}

/**
 * nulluje strumien logowania
 */
void InclinedPlane::stopLogs()
{
	this->log = NULL;
}


/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
/* 								PRIVATE METHODS OF CLASS INCLINEDPLANE									 */
/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */


/* ----------------------------------------------------------------------------------------------------- */
/* -------------------------------- CLASS PRIVATE METHOD -------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
/**
 * std::pair<Barrel*, int> InclinedPlane::findRight(Barrel::Color e, Barrel* ii)
 * TODO nie wiem czy to dziala ;/
 */
std::pair<Barrel*, int>
InclinedPlane::findRight(Barrel::Color e, Barrel* ii)
{
	if(this->log)
	{
		*(this->log) << "START: std::pair<Barrel*, int> InclinedPlane::findRight(Barrel::Color e, Barrel* ii)" << "\n";
		this->printBarrelsToStream(*(this->log));
		*(this->log) << "\n";
		if(e == Barrel::BLUE)
			*(this->log) << "Szukany kolor: " << "B" << "\n";
		else if(e == Barrel::GREEN)
			*(this->log) << "Szukany kolor: " << "G" << "\n";
		else if(e == Barrel::RED)
			*(this->log) << "Szukany kolor: " << "R" << "\n";
		this->log->flush();
	}

	std::pair<Barrel*, int> ret;
	ret.second = 0;
	ret.first = NULL;
	Barrel* i = ii;
	int licz = 0;
	i = i->next();//++ii;
	// nie licze pierwszej beczki ktora nie pasuje
	// dlatego jak policze beczke ktora sie zgadza kolorem
	// to ilosc beczek zlego koloru miedzy beczkami dobrego koloru sie zgadza
	while(i != this->list.end())
	{
		++licz;
		if(i->getColor() == e)
		{
			ret.first = i;
			ret.second = licz;
			if(ret.second%3 == 0)
				break;
		}
		i = i->next();//++ii;
	}
	if(ret.first == NULL)
		{system("sleep 1"); {system("sleep 1"); assert(0); } }

	if(this->log)
	{
		*(this->log) << "Odleglosc: " << ret.second << "\n";
		*(this->log) << "Znaleziony kolor: " << ret.first->printBarrel() << "\n";
		*(this->log) << "END: std::pair<Barrel*, int> InclinedPlane::findRight(Barrel::Color e, Barrel* ii)" << "\n";
		this->log->flush();
	}

	return ret;
}



/* ----------------------------------------------------------------------------------------------------- */
/* -------------------------------- CLASS PRIVATE METHOD -------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
/** void InclinedPlane::intelligentSort()
 *
 */
void InclinedPlane::intelligentSort()
{
	if(this->log)
	{
		*(this->log) << "\n";
		*(this->log) << "\n";
		*(this->log) << "START: void InclinedPlane::intelligentSort()" << "\n";
		*(this->log) << "Rozmiar problemu: " << this->list.size() << "\n";
		*(this->log) << "\n";
		this->log->flush();
	}
	int i =0;
	Barrel *tmp;
	int encRed=0, encBlue=0, encGreen=0;
	Barrel* ii;
	std::pair<Barrel*, int> info;

	ii = this->list.setCurrentAtStart(); // USTAWIAM POZYCJE AKTUALNA NA POCZATKOWA!!!

	std::cout << "zaczelo sortowac" << "\n";
///**
	bool notSorted = true;

	while(notSorted==true && this->list.current() != this->list.end())
	{
		switch(ii->getColor())
		{
		case Barrel::RED: // CASE RED - przypadek napotkania czerwonej
			++encRed;
			break;
		case Barrel::BLUE: // CASE BLUE - przypadek napotkania niebieskiej
			if(encRed != this->quantityOfRed)
			{
				info = this->findRight(Barrel::RED, ii);
				tmp = info.first;
				if(ii == this->list.end()) // end nie powinien sie tu pojawic
					{system("sleep 1"); assert(0); }
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::RED) // zwrocona beczka powinna miec
					{system("sleep 1"); assert(0); }							// odpowiedni kolor
				// posortowane - tzn zamiast blue jest red - zwiekszamy licznik
				++encRed;
			} else
				++encBlue;
			break;
		case Barrel::GREEN: // CASE GREEN - przypadek napotkania zielonej
			if(encRed != this->quantityOfRed)
			{
				info = this->findRight(Barrel::RED, ii);
				tmp = info.first;
				if(ii == this->list.end()) // end nie powinien sie tu pojawic
					{system("sleep 1"); assert(0); }
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::RED)// zwrocona beczka powinna miec
					{system("sleep 1"); assert(0); }							// odpowiedni kolor
				// posortowane - tzn zamiast green jest red - zwiekszamy licznik
				++encRed;
			} else if(encBlue != this->quantityOfBlue)
			{
				info = this->findRight(Barrel::BLUE, ii);
				tmp = info.first;
				if(ii == this->list.end()) // end nie powinien sie tu pojawic
					{system("sleep 1"); assert(0); }
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::BLUE) // zwrocona beczka powinna miec
					{system("sleep 1"); assert(0); }							// odpowiedni kolor
				// posortowane - tzn zamiast green jest blue - zwiekszamy licznik
				++encBlue;
			} else
			{
				++encGreen;
				notSorted = false;
			}
			break;
		default: // CASE NONE
			{system("sleep 1"); assert(0); }
		} // KONIEC SWITCHA
		// PRZEMIELILO - znaczy do aktualnej pozycji jest posortowane
		// wiec ide aktualna pozycja do przodu - zatrzymam sie na nastepnej zlej beczce
		ii = this->list.shiftCurrentForward();
		++i;
	} // koniec while
//**/
	/**
//	 * V 1.0

	// poczatek petli sortujacej
	for(; ii != this->list.end(); ++i)
	{
		switch(ii->getColor())
		{
		case Barrel::RED:
			ii = ii->next();//++ii;
			++encRed;
			break;
		case Barrel::BLUE:
			if(encRed != this->quantityOfRed)
			{
				info = this->findRight(Barrel::RED, ii);
				tmp = info.first;
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::RED)
					{system("sleep 1"); assert(0); }
				ii = ii->next();
				// posortowane - tzn zamiast blue jest red - zwiekszamy licznik
				++encRed;
			} else
			{
				++encBlue;
				ii = ii->next();//++ii;
			}
			break;
		case Barrel::GREEN:
			if(encRed != this->quantityOfRed)
			{
				info = this->findRight(Barrel::RED, ii);
				tmp = info.first;
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::RED)
					{system("sleep 1"); assert(0); }
				ii = ii->next();
				// posortowane - tzn zamiast green jest red - zwiekszamy licznik
				++encRed;
			} else if(encBlue != this->quantityOfBlue)
			{
				info = this->findRight(Barrel::BLUE, ii);
				tmp = info.first;
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::BLUE)
					{system("sleep 1"); assert(0); }
				ii = ii->next();
				// posortowane - tzn zamiast green jest blue - zwiekszamy licznik
				++encBlue;
			} else
			{
				ii = ii->next();//++ii;
				++encGreen;
			}
			break;
		default:
			break;
		}
	} // KONIEC PETLI FOR

//	 *
//	*	END V 1.0
//	*
	* */

	std::cout << "\n" << " SPRAWDZENIE SORTOWANIA " << "\n" << "\n";
	//this->printBarrels();
	std::cout << "\n" << " KONIEC SORTOWANIA " << "\n" << "\n";

	if(this->log)
	{
		*(this->log) << "Koniec sortowania" << "\n";
		this->printBarrelsToStream(*(this->log));
		*(this->log) << "END: void InclinedPlane::intelligentSort()" << "\n";
		*(this->log) << "\n";
		*(this->log) << "\n";
		this->log->flush();
	}

}// KONIEC INTELLIGENT SORTA





/* ----------------------------------------------------------------------------------------------------- */
/* -------------------------------- CLASS PRIVATE METHOD -------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
/** Barrel* InclinedPlane::moveTrios(Barrel *from, Barrel *to, int k, int i)
 *
 */
Barrel* InclinedPlane::moveTrios(Barrel *from, Barrel *to, int k, int i)
{

	if(this->log)
	{
		*(this->log) << "\n";
		*(this->log) << "START: Barrel* InclinedPlane::moveTrios(Barrel *from, Barrel *to, int k, int i)" << "\n";
		*(this->log) << "Przed przestawieniem: " << "\n";
		this->printBarrelsToStream(*(this->log));
		*(this->log) << "Krok ity: " << i << "\n";
		*(this->log) << "Odleglosc od szukanej beczki: " << k << "\n";
		*(this->log) << "Odleglosc szukanej beczki od konca: " << this->list.size()-i-k-1 << "\n";
		this->log->flush();
	}

	Barrel* pom = this->list.end();
	Barrel* p = to;
	pom = pom->prev(); // --pom;
	Barrel::Color c = to->getColor();
	int l = this->list.size()-i-k-1; // z -1 jest dobrze ALE wchodzi i tak do zlych przypadkow - momentami zle zlicza!
							// TODO: poprawic - tylko co?
	int ll = 0;
	while(p->next() != this->list.end())
	{
		++ll;
		p = p->next();
	}
	Barrel *t, *f;
	t = to;
	f = from;
//	this->printBarrels();
/**
 * k - odleglosc beczki od odp pozycji
 * l - odleglosc beczki od konca listy
 */
	//this->printBarrels();
	if(k % 3 != 0)
	{
		if(this->log)
		{
			*(this->log) << "\n";
			*(this->log) << "Przestawienie korekcyjne: " << k << " i ";
			this->log->flush();
		}
	}
	if(k % 3 == 1)
	{
		if(l % 3 == 0)
		{
			if(this->log)
			{
				*(this->log) << l << " czyli 1 i 0" << "\n";
				this->log->flush();
			}
			if(l == 0)
			{
				t = t->prev();
				t = this->swapTrioBefore(t);
				//this->printBarrels();
			}
			t = t->prev();
			this->swapTrioBehind(t);
			//this->printBarrels();
		} else if(l % 3 == 1)
		{
			if(this->log)
			{
				*(this->log) << l << " czyli 1 i 1" << "\n";
				this->log->flush();
			}
			if(l == 1)
			{
				t = t->prev();
				t = this->swapTrioBefore(t);
				//this->printBarrels();
			}
			this->swapTrioBehind(t);
			//this->printBarrels();
		} else if(l % 3 == 2)
		{
			if(this->log)
			{
				*(this->log) << l << " czyli 1 i 2" << "\n";
				this->log->flush();
			}
			t = t->prev();
			this->swapTrioBehind(t);
			//this->printBarrels();
		}
	} else if(k % 3 == 2)
	{
		if(l % 3 == 0)
		{
			if(this->log)
			{
				*(this->log) << l << " czyli 2 i 0" << "\n";
				this->log->flush();
			}
			if(l == 0)
			{
				t = t->prev();
				t = this->swapTrioBefore(t);
				//this->printBarrels();
			}
			this->swapTrioBehind(t);
			//this->printBarrels();
		} else if(l % 3 == 1)
		{
			if(this->log)
			{
				*(this->log) << l << " czyli 2 i 1" << "\n";
				this->log->flush();
			}
			this->swapTrioBefore(t);
			//this->printBarrels();
		} else if(l % 3 == 2)
		{
			if(this->log)
			{
				*(this->log) << l << " czyli 2 i 2" << "\n";
				this->log->flush();
			}
			t = t->prev();
			this->swapTrioBehind(t);
			//this->printBarrels();
		}
	}
	if(this->log)
		{
			*(this->log) << "\n";
			*(this->log) << "Po przestawieniu korekcyjnym:" << "\n";
			this->printBarrelsToStream(*log);
			this->log->flush();
		}

	int lol=0;
	while(from->getColor() != c)
	{
	//	this->printBarrels();
	//	if(from->prev()->getColor() != c)
	//	{
	//		while(from->prev()->getColor() == c)
//				from = from->prev();
	//	}
		from = this->swapTrioBehind(from);
		lol++;
		//this->printBarrels();
		//std::cout << lol << "\n";
	}

	if(this->log)
	{
		*(this->log) << "Po przestawieniu: " << "\n";
		this->printBarrelsToStream(*(this->log));
		*(this->log) << "\n";
		*(this->log) << "END: Barrel* InclinedPlane::moveTrios(Barrel *from, Barrel *to, int k, int i)" << "\n";
		*(this->log) << "\n";
		this->log->flush();
	}

	return from;
}





/* ----------------------------------------------------------------------------------------------------- */
/* -------------------------------- CLASS PRIVATE METHOD -------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
/** Barrel* InclinedPlane::swapTrioBefore(Barrel* last)
 *
 */
Barrel* InclinedPlane::swapTrioBefore(Barrel* last)
{
	Barrel *l;
	l = last->prev()->prev();//--last; --last;
	l = this->list.putTrioAtEnd(l);
	return l;
}


/* ----------------------------------------------------------------------------------------------------- */
/* -------------------------------- CLASS PRIVATE METHOD -------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
/** Barrel* InclinedPlane::swapTrioBehind(Barrel* first)
 *
 */
Barrel* InclinedPlane::swapTrioBehind(Barrel* first)
{
	Barrel *f = first;
	f = this->list.putTrioAtEnd(f);
	return f;
}

} // namespace
