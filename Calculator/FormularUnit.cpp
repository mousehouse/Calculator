#include "FormularUnit.h"
#include "ParseBuffer.h"
#include "NumeralUnit.h"
#include "CalculateManager.h"
#include "ComplexUnit.h"
#include "MethodUnit.h"

FormularUnit::FormularUnit(void)
{
}


FormularUnit::~FormularUnit(void)
{
	//puts("FormularUnit release\n");
}


FormularUnit* FormularUnit::Parse(ParseBuffer* buffer, int prev_priority) throw(WrongFormatException)
{
	char ch;
	FormularUnit* pUnit = NULL;

	ch = buffer->Peek();

	if( SYMBOL_LEFT == ch )
	{
		buffer->Read();
		pUnit = FormularUnit::Parse( buffer, 0 );
		if( SYMBOL_RIGHT != buffer->Read() ) throw WrongFormatException(buffer);
	}
	else if( NumeralUnit::IsNumeral(ch) || (NEGATIVE_CHAR == ch))
	{
		pUnit = new NumeralUnit( buffer );
	}
	else if( MethodUnit::IsNameChar( ch ) )
	{
		pUnit = new MethodUnit(buffer);
	}
	else throw WrongFormatException(buffer);

	int priority;
	while( (priority = CalculateManager::M.GetPriority( buffer->Peek() )) > prev_priority )
	{
		ComplexUnit *pComplex = new ComplexUnit();
		pComplex->op = buffer->Read();
		pComplex->leftUnit	= pUnit;
		pComplex->rightUnit	= FormularUnit::Parse( buffer, priority);
		pUnit = pComplex;
	}
	return pUnit;
}

void FormularUnit::Release(  FormularUnit * &pUnit )
{
	if( pUnit ) {
		delete pUnit;
		pUnit = 0;
	}
}
