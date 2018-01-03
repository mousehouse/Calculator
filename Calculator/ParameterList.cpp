#include "ParameterList.h"
#include "FormularUnit.h"

ParameterList::ParameterList(void)
{
}


ParameterList::~ParameterList(void)
{
	for( ParameterList::iterator i = begin(), end= this->end(); i != end ;++i)
		FormularUnit::Release( *i );
}
