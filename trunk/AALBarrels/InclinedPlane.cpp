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
	// TODO Auto-generated constructor stub
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
	// TODO Auto-generated destructor stub

}

/**
 * ********************************************************************************
 * *************************** CLASS PUBLIC METHOD ********************************
 * ********************************************************************************
 * ***************** void InclinedPlane::addBarrel(Barrel *b) *********************
 * ********************************************************************************
 */
void InclinedPlane::addBarrel(Barrel *b)
{
	this->list.addOnEnd(b);
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
}

void InclinedPlane::addBarrel(Barrel** b, int size)
{
	for(int i=0; i<size; ++i)
	{
		this->addBarrel(b[i]);
	}
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
	Barrel* ii = this->list.start();
	char c = '\0';
	//for(; ii != list.end(); ++ii, ++i)
	while(ii != list.end())
	{
		c = ii->printBarrel();
		std::cout << c;
		ii = ii->next();
	}
	std::cout << std::endl;
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
	Barrel* ii = this->list.start();
	char c = '\0';
	int i = 0;
	//for(; ii!=list.end(); ++ii, ++i)
	while(ii != list.end())
	{
		c = ii->printBarrel();
		if(i == index)
			std::cout << "||";
		std::cout << c;
		if(i%25 == 0)
			std::cout << std::endl;
		++i;
		ii = ii->next();
	}
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
	if(this->quantityOfGreen < 3)
		return;
	if(s == InclinedPlane::IntelligentSort)
		this->intelligentSort();
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
 *
 */
std::pair<Barrel*, int>
InclinedPlane::findRight(Barrel::Color e, Barrel* ii)
{
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
		assert(0);
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
	int i =0;
	Barrel *tmp;
	int encRed=0, encBlue=0, encGreen=0;
	Barrel* ii;
	std::pair<Barrel*, int> info;

	ii = this->list.setCurrentAtStart(); // USTAWIAM POZYCJE AKTUALNA NA POCZATKOWA!!!

	std::cout << "zaczelo sortowac" << std::endl;
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
					assert(0);
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::RED) // zwrocona beczka powinna miec
					assert(0);							// odpowiedni kolor
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
					assert(0);
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::RED)// zwrocona beczka powinna miec
					assert(0);							// odpowiedni kolor
				// posortowane - tzn zamiast green jest red - zwiekszamy licznik
				++encRed;
			} else if(encBlue != this->quantityOfBlue)
			{
				info = this->findRight(Barrel::BLUE, ii);
				tmp = info.first;
				if(ii == this->list.end()) // end nie powinien sie tu pojawic
					assert(0);
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::BLUE) // zwrocona beczka powinna miec
					assert(0);							// odpowiedni kolor
				// posortowane - tzn zamiast green jest blue - zwiekszamy licznik
				++encBlue;
			} else
			{
				++encGreen;
				notSorted = false;
			}
			break;
		default: // CASE NONE
			assert(0);
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
					assert(0);
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
					assert(0);
				ii = ii->next();
				// posortowane - tzn zamiast green jest red - zwiekszamy licznik
				++encRed;
			} else if(encBlue != this->quantityOfBlue)
			{
				info = this->findRight(Barrel::BLUE, ii);
				tmp = info.first;
				ii = this->moveTrios(ii, info.first, info.second, i);
				if(ii->getColor() != Barrel::BLUE)
					assert(0);
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

	std::cout << std::endl << " SPRAWDZENIE SORTOWANIA " << std::endl << std::endl;
	//this->printBarrels();
	std::cout << std::endl << " KONIEC SORTOWANIA " << std::endl << std::endl;

}// KONIEC INTELLIGENT SORTA





/* ----------------------------------------------------------------------------------------------------- */
/* -------------------------------- CLASS PRIVATE METHOD -------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
/** Barrel* InclinedPlane::moveTrios(Barrel *from, Barrel *to, int k, int i)
 *
 */
Barrel* InclinedPlane::moveTrios(Barrel *from, Barrel *to, int k, int i)
{
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
	if(k % 3 == 1)
	{
		if(l % 3 == 0)
		{
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
			t = t->prev();
			this->swapTrioBehind(t);
			//this->printBarrels();
		}
	} else if(k % 3 == 2)
	{
		if(l % 3 == 0)
		{
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
			this->swapTrioBefore(t);
			//this->printBarrels();
		} else if(l % 3 == 2)
		{ // jak ilosc beczek miedzy dobra, a kocem listy wynosi 3*c + 2, to cofam wsk o 1 i przenosze 3 beczki
			// nie ma prawa przeniesc enda!!!
			t = t->prev();
			this->swapTrioBehind(t);
			//this->printBarrels();
		}
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
		std::cout << lol << std::endl;
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
