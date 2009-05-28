/*
 * Barrel.cpp
 *
 *  Created on: 2009-03-13
 *      Author: zby
 */
#include <cassert>
#include <cstdlib>

#include "Barrel.h"

namespace AALBarrels // name space
{


Barrel::Barrel()
{
	this->color = Barrel::NONE;
	this->_prev = NULL;
	this->_next = NULL;
}

Barrel::Barrel(Color c)
{
	this->color = c;
	this->_prev = NULL;
	this->_next = NULL;
}

Barrel::Barrel(Color c, Barrel *p, Barrel *n)
{
	this->color = c;
	this->setPtr(p, n);
}

Barrel::Barrel(const Barrel& another)
{
	this->color = another.color;
	this->_next = another._next;
	this->_prev = another._prev;
}

Barrel::~Barrel()
{
	// TODO Auto-generated destructor stub
	this->_prev = NULL;
	this->_next = NULL;
}

int Barrel::compareBarrels(const Barrel& it) const
{
	int r = (this->color - it.color);
	if(r<0) r = -1;
	if(r>0) r = 1;
	return r;
}

Barrel::Color Barrel::getColor() const
{
	return this->color;
}

void Barrel::setColor(Color c)
{
	this->color = c;
}

char Barrel::printBarrel() const
{
	char c = '\0';
	switch(this->getColor())
	{
	case Barrel::RED:
		c = 'R';
		break;
	case Barrel::BLUE:
		c = 'B';
		break;
	case Barrel::GREEN:
		c = 'G';
	default:
		break;
	}
	return c;
}

Barrel Barrel::readBarrel(char s)
{
	Color c;
	switch(s)
	{
	case 'R':
		c = Barrel::RED;
		break;
	case 'B':
		c = Barrel::BLUE;
		break;
	case 'G':
		c = Barrel::GREEN;
	default:
		break;
	}
	Barrel b(c);
	return b;
}

Barrel* Barrel::next() const
{
	return this->_next;
}

Barrel* Barrel::prev() const
{
	return this->_prev;
}

void Barrel::setNext(Barrel *a)
{
	this->_next = a;
}

void Barrel::setPrev(Barrel *a)
{
	this->_prev = a;
}

void Barrel::setPtr(Barrel *p, Barrel *n)
{
	this->_prev = p;
	this->_next = n;
}


};
