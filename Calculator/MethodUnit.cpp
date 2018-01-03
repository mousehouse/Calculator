#include "MethodUnit.h"
#include <memory.h>
#include "ParseBuffer.h"
#include "NumeralUnit.h"
#include "ParameterList.h"
#include "CalculateManager.h"

#define SYMBOL_SEPERATE		','

MethodUnit::MethodUnit(void)
{
	::memset( this->m_name, 0, sizeof(this->m_name));
	this->m_parameters = new ParameterList();
}

MethodUnit::MethodUnit(ParseBuffer* buffer)
{
	::memset( this->m_name, 0, sizeof(this->m_name));
	this->m_parameters = new ParameterList();
	this->ParseFrom( buffer );
}

MethodUnit::~MethodUnit(void)
{
	delete this->m_parameters;
}


void MethodUnit::ParseFrom(ParseBuffer* buffer)
{
	int i = 0;
	size_t pCnt;
	char c;

	while( MethodUnit::IsNameChar(this->m_name[i] = buffer->Read()) )
		if( ++i >= MAX_METHOD_NAME ) throw UndefineMethodException(buffer); 

	if( this->m_name[i] != SYMBOL_LEFT ) throw WrongFormatException(buffer);
	this->m_name[i] = 0;
	if( !CalculateManager::M.IsRegistered( this->m_name, &pCnt) )throw UndefineMethodException(buffer);
	
	i = 0;
	if( buffer->Peek() == SYMBOL_RIGHT )
	{
		c = buffer->Read();
	}
	else
	{
		do
		{
			this->m_parameters->push_back( FormularUnit::Parse( buffer, 0 ) );
			c = buffer->Read();
			++i;
		}while(SYMBOL_SEPERATE  == c );
	}

	if( i != pCnt ) throw UndefineMethodException(buffer);
	 
	if( c != SYMBOL_RIGHT ) throw WrongFormatException(buffer);
}


bool MethodUnit::IsNameChar(char ch)
{
	return (ch >= 'a' && ch <= 'z') || 
		(ch >= 'A' && ch <= 'Z') || 
		(ch=='_') || 
		NumeralUnit::IsNumeral(ch);
}

double MethodUnit::GetUnitValue(void)const
{
	return CalculateManager::M.GetProc( this->m_name )( this->m_parameters );
}
