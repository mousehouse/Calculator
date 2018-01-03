#include "NumeralUnit.h"
#include "ParseBuffer.h"
#include "CalculateManager.h"

#define MIN_NUMERAL		'0'
#define MAX_NUMERAL		'9'
#define	FLOAT_POINT		'.'
#define FACT_SYMBOL		'!'

NumeralUnit::NumeralUnit(void)
{
	m_data = 0;
	m_bNegative = false;
}

NumeralUnit::NumeralUnit( ParseBuffer* buffer ) throw(WrongFormatException)
{
	ParseFrom( buffer );
}


NumeralUnit::~NumeralUnit(void)
{
}

double NumeralUnit::GetUnitValue()const
{
	return m_bNegative ? (-m_data) : m_data;
}

void NumeralUnit::ParseFrom(ParseBuffer* buffer) throw(WrongFormatException)
{
	double tmp = 0,ex = 1;
	char first = buffer->Peek();
	this->m_data = 0;
	this->m_bNegative = false;

	// 负号处理
	if( first == NEGATIVE_CHAR )
	{
		this->m_bNegative = true;
		buffer->Read();
		first = buffer->Peek();
	}

	// 整数处理
	if( !NumeralUnit::IsNumeral(first) )
		throw WrongFormatException( buffer );

	do
	{
		tmp *= 10;
		tmp += NumeralUnit::ToNumeral( buffer->Read() );
	}while( NumeralUnit::IsNumeral( buffer->Peek() ) );

	this->m_data = tmp;
	//处理阶乘
	if (buffer->Peek() == FACT_SYMBOL)
	{
		tmp = CalculateManager::vCal_fact(tmp);
		buffer->Read();
	}
	this->m_data = tmp;

	// 小数点检验
	if( buffer->Peek() != FLOAT_POINT ) return;
	buffer->Read();

	// 小数处理
	first = buffer->Peek();

	if( !NumeralUnit::IsNumeral(first) )
		throw WrongFormatException( buffer );
	tmp = 0;
	do
	{
		ex *= 10;
		tmp *= 10;
		tmp += NumeralUnit::ToNumeral( buffer->Read() );
	}while( NumeralUnit::IsNumeral( buffer->Peek() ) );

	this->m_data += ( tmp / ex );
}


bool NumeralUnit::IsNumeral(char ch)
{
	return ch >= MIN_NUMERAL && ch <= MAX_NUMERAL;
}


int NumeralUnit::ToNumeral(char ch)
{
	return ch - MIN_NUMERAL;
}
