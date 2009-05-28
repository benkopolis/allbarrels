/*
 * BarrelException.cpp
 *
 *  Created on: 2009-03-20
 *      Author: zby
 */

#include <iostream>


#include "BarrelException.h"


namespace AALBarrels
{



BarrelException::BarrelException()
{
	// TODO Auto-generated constructor stub
	this->exceptionName = "BarrelException::NoBarrelExceptionKindSet";
	this->exceptionType = BarrelException::NoBarrelExceptionKindSet;
}

BarrelException::BarrelException(BarrelExceptionKind e)
{
	this->setExceptionKind(e);
}

BarrelException::~BarrelException()
{
	// TODO Auto-generated destructor stub
}


BarrelException::BarrelExceptionKind BarrelException::getExceptionKind()
{
	return this->exceptionType;
}

void BarrelException::setExceptionKind(BarrelExceptionKind e)
{
	this->exceptionType = e;
	switch(e)
	{
	case BarrelException::LessThenThreeGreenBarrels:
		this->exceptionName = "BarrelException::LessThenThreeGreenBarrels";
		break;
	case BarrelException::NoBarrelExceptionKindSet:
		this->exceptionName = "BarrelException::NoBarrelExceptionKindSet";
		break;
	case BarrelException::NoBarrels:
		this->exceptionName = "BarrelException::NoBarrels";
		break;
	case BarrelException::NoColorSet:
		this->exceptionName = "BarrelException::NoColorSet";
		break;
	default:
		this->exceptionName = "BarrelException::None";
		break;

	}
}

std::string BarrelException::getMessage()
{
	try
		{
			if(this->exceptionType == BarrelException::None)
			{
				BarrelException e(BarrelException::NoBarrelExceptionKindSet);
				std::string lol("Threw by std::string BarrelException::getMessage()"
						"\n You must set BarrelExceptionKind before setting a message\n");
				e.setMessage(lol);
				throw e;
			} else
			{
				return this->message;
			}
		} catch(BarrelException e)
		{
			std::cerr << e.getMessage();
		}
		return this->message;
}

void BarrelException::setMessage(std::string msg)
{
	try
	{
		if(this->exceptionType == BarrelException::None)
		{
			BarrelException e(BarrelException::NoBarrelExceptionKindSet);
			std::string lol("Threw by void BarrelException::setMessage(std::string)"
					"\n You must set BarrelExceptionKind before setting a message\n");
			e.setMessage(lol);
			throw e;
		} else
		{
			this->message = this->exceptionName + "::: " + msg;
		}
	} catch(BarrelException e)
	{
		std::cerr << e.getMessage();
	}
}

std::pair<BarrelException::BarrelExceptionKind, std::string> BarrelException::getAll()
{
	return std::make_pair(this->exceptionType, this->message);
}

void BarrelException::setAll(BarrelExceptionKind e, std::string msg)
{
	this->setExceptionKind(e);
	this->setMessage(msg);
}






};
