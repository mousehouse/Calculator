#pragma once
#include "WrongFormatException.h"
#define SYMBOL_LEFT		'('
#define SYMBOL_RIGHT	')'
class FormularUnit
{
public:
	FormularUnit(void);
	virtual ~FormularUnit(void);

/* Override */
public:
	// get value of this unit
	virtual double GetUnitValue()const = 0;

/* Factor */
public:
	/* Parse().
	 *
	 * Comments:This method translate a formular string specfied by 
	 *			a buffer to FormularUnit Object.
	 * 
	 * Remarks: Call Release() to delete the Object created by Parse().
	 * 
	 */ 
	static FormularUnit* Parse(ParseBuffer* buffer, int prev_priority)
		throw(WrongFormatException);

	// release an object created by Parse().
	static void Release( FormularUnit * &pUnit );
};

