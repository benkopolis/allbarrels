/*
 * BarrelException.h
 *
 *  Created on: 2009-03-20
 *      Author: zby
 */

#ifndef BARRELEXCEPTION_H_
#define BARRELEXCEPTION_H_

#include <string>
#include <utility>


namespace AALBarrels
{


class BarrelException
{
public:

	enum BarrelExceptionKind
	{
		None,
		NoColorSet,
		LessThenThreeGreenBarrels,
		NoBarrelExceptionKindSet,
		NoBarrels
	};


	BarrelException();
	BarrelException(BarrelExceptionKind e);
	virtual ~BarrelException();

	void setExceptionKind(BarrelExceptionKind e);
	BarrelExceptionKind getExceptionKind();

	void setMessage(std::string msg);
	std::string getMessage();

	void setAll(BarrelExceptionKind e, std::string msg);
	std::pair<BarrelExceptionKind, std::string> getAll();

private:
	std::string message;
	BarrelExceptionKind exceptionType;
	std::string exceptionName;
};



};
#endif /* BARRELEXCEPTION_H_ */
