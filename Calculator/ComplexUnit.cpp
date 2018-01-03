#include "ComplexUnit.h"
#include "CalculateManager.h"

ComplexUnit::ComplexUnit(void)
{
	leftUnit = rightUnit = 0;
	op = 0;
}


ComplexUnit::~ComplexUnit(void)
{
	FormularUnit::Release( this->leftUnit );
	FormularUnit::Release( this->rightUnit);
}

double ComplexUnit::GetUnitValue()const
{
	return CalculateManager::M.GetProc( op )( 
		leftUnit->GetUnitValue(), rightUnit->GetUnitValue() );
}
