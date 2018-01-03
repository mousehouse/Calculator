#pragma once
#include "formularunit.h"
class ComplexUnit :
	public FormularUnit
{
	friend class FormularUnit;
public:
	FormularUnit*	leftUnit;
	FormularUnit*	rightUnit;
	char			op;
private:
	ComplexUnit(void);
	virtual ~ComplexUnit(void);
/* Override */
public:
	virtual double GetUnitValue()const;
};

