/*
 * BarrelsList.cpp
 *
 *  Created on: 2009-05-03
 *      Author: zby
 */

#include <cassert>
#include <cstdlib>

#include "BarrelsList.h"
#include "Barrel.h"

namespace AALBarrels
{

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
BarrelsList::BarrelsList()
{
	_end = new Barrel(Barrel::NONE);
	_start = _end;
	_size = 0;
	_current = _end;

}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
BarrelsList::BarrelsList(const BarrelsList & another)
{
	_end = new Barrel(Barrel::NONE);
	_start = _end;
	_size = 0;
	Barrel *tmp = another._start;
	Barrel *c = NULL;
	while(tmp != another._end)
	{
		c = this->addOnStart(tmp);
		if(tmp == another._current)
			_current = c;
		tmp = tmp->next();
	}
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
BarrelsList::~BarrelsList()
{
	this->_current = this->_start;
	while(this->_current->next() != NULL)
	{
		this->_current = this->_current->next();
		delete this->_current->prev();
		this->_current->setPrev(NULL);//_prev = NULL;
	}
	this->_start = NULL;
	this->_end = NULL;
	this->_size = 0;
	this->_current = NULL;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::addOnEnd(const Barrel *const aNew)
{
	++(this->_size);
	Barrel *t = new Barrel(aNew->getColor(), this->_end->prev(), this->_end);
	if(t->prev())
		t->prev()->setNext(t);//_next = t;
	else
		this->_start = t;
	this->_end->setPrev(t);//_prev = t;
	return t;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::addOnStart(const Barrel *const aNew)
{
	++(this->_size);
	Barrel *t = new Barrel(aNew->getColor(), NULL, this->_start->next());
	if(this->_start->next())
		this->_start->next()->setPrev(t);//_prev = t;
	this->_start = t;
	return t;
}

/* ----------------------------------------------------------------------------------------------------- */
/**
 *	Barrel *BarrelsList::putTrioAtEnd(Barrel *first)
 *
 *	@brief funkcja przenosi trzy beczki (pierwsza wskazana jest przez first) na koniec listy (przed enda)
 *	@param first - wskaznik na pierwsza z 3 beczek do przeniesienia
 *	@return wskaznik do beczki ktora stala bezposrednio za przenoszona trojka beczek
 *
 * Funckja ta nie ma prawa zwrocic enda - nie mozna przenosic 3 ostatnich beczek - to bez sensu i
 * prawdopodobnie spowodowalo by to zapetlenie sie przenoszenia (przenoszenie byloby wykonywane bez
 * zadnych widocznych skutkow).
 *
 * */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::putTrioAtEnd(Barrel *first)
{
	Barrel *f, *s, *t, *r;
	f = first;
	if(f == this->_end)
		{system("sleep 3"); assert(0); }
	s = f->next();
	if(s == this->_end)
		{system("sleep 3"); assert(0); }
	t = s->next();
	if(t == this->_end)
		{system("sleep 3"); assert(0); }
	r = t->next();
	if(r == this->_end)
		{system("sleep 3"); assert(0); }
	if(f == this->_start)
		this->_start = t->next();
	if(f == this->_current || s == this->_current || t == this->_current)
		this->_current = r;
	if(f->prev())
		f->prev()->setNext(t->next());//_next = t->next();
//	if(t->next()) TO nie moze zajsc, bo t->next nie moze byc endem !!!
		t->next()->setPrev(f->prev());//_prev = f->prev();
	this->_end->prev()->setNext(f);//_next = f; // poprzednik enda ma za nastepnika f
	f->setPrev(this->_end->prev());//_prev = _end->prev();
	t->setNext(_end);//_next = _end;
	this->_end->setPrev(t);//_prev = t;
	return r;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::getCurrent() const
{
	return this->_current;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::shiftCurrentForward()
{
	if(this->_current->next())
		this->_current = _current->next();
	else
		{system("sleep 3"); assert(0); }
	return this->_current;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::shiftCurrentBackward()
{
	if(this->_current->prev())
		this->_current = _current->prev();
	else
		{system("sleep 3"); assert(0); }
	return this->_current;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::setCurrentAtStart()
{
	this->_current = this->_start;
	return this->_current;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::setCurrenAtEnd()
{
	this->_current = this->_end;
	return this->_current;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::erase(Barrel *t)
{
	if(t == this->_end)
		{system("sleep 3"); assert(0); }
	--(this->_size); // zmniejszam rozmiar
	Barrel *tmp;
	if(t == this->_start)
	{
		t->next()->setPrev(NULL);//_prev = NULL;
		this->_start = t->next();
		if(this->_current == t)
			this->_current = this->_start;
		delete t;
		return this->_start;
	}
	if(this->_current == t)
		this->_current = t->next();
	t->next()->setPrev(t->prev());//_prev = t->prev();
	t->prev()->setNext(t->next());//_next = t->next();
	tmp = t->next();
	delete t;
	return tmp;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::erase(Barrel *f, Barrel *t)
{
	while(f != t)
	{
		if(f == this->_current)
			this->_current = t;
		f = erase(f);
	}
	return t;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel *BarrelsList::clear()
{
	this->erase(this->_start, this->_end);
	this->_current = this->_end;
	this->_size = 0;
	this->_start = this->_end;
	this->_end->setPtr(NULL, NULL);
	return this->_current;
}


/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel* BarrelsList::end() const
{
	return this->_end;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel* BarrelsList::start() const
{
	return this->_start;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
Barrel* BarrelsList::current() const
{
	return this->_current;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
unsigned int BarrelsList::getSize() const
{
	return this->_size;
}

/* ----------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------------------------------------- */
unsigned int BarrelsList::size() const
{
	return this->_size;
}

};
