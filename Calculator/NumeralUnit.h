#pragma once
#include "formularunit.h"
#define NEGATIVE_CHAR	'-'

class NumeralUnit :
	public FormularUnit
{
	friend class FormularUnit;
private:
	double m_data;
	bool   m_bNegative;
private:
	NumeralUnit(void);
	NumeralUnit( ParseBuffer* buffer )throw(WrongFormatException);
	~NumeralUnit(void);
/* Override */
public:
	virtual double GetUnitValue()const;
	void ParseFrom(ParseBuffer* buffer)throw(WrongFormatException);
public:
	static bool IsNumeral(char ch);
	static int ToNumeral(char ch);
};

