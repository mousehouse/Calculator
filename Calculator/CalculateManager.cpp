#include "CalculateManager.h"
#include <math.h>
#include "FormularUnit.h"
#include "ParameterList.h"
#include <memory.h>
#include <algorithm>

#define MAX_OPERATOR 128

CalculateManager CalculateManager::M;

CalculateManager::CalculateManager(void)
{
	this->Priorities = new int[ MAX_OPERATOR ];
	this->Procedures = new CalculateProc[MAX_OPERATOR];
	::memset(this->Priorities, 0, sizeof(int)*MAX_OPERATOR);
	::memset(this->Procedures, 0, sizeof(CalculateProc)*MAX_OPERATOR);

	// Initialize
	this->Regester('+', 1, CalculateManager::Cal_add);
	this->Regester('-', 1, CalculateManager::Cal_sub);
	this->Regester('*', 2, CalculateManager::Cal_mul);
	this->Regester('/', 2, CalculateManager::Cal_div);
	this->Regester('%', 2, CalculateManager::Cal_mod);
	this->Regester('^', 3, ::pow);
	this->Regester('!', 3, CalculateManager::vCal_fact);

	#define REG( X, t ) this->Regester( #X, CalculateManager::vCal_##X , t )
	REG( log,2 );
	REG( lg,1 );
	REG( ln,1 );
	REG( sqrt,1 );
	REG( max,2 );
	REG( min,2 );
	REG( sin,1 );
	REG( cos,1 );
	REG( tan,1 );
	REG( asin,1 );
	REG( acos,1 );
	REG( atan,1 );
	REG( pi,0 );
}


CalculateManager::~CalculateManager(void)
{
	delete [] this->Priorities;
	delete [] this->Procedures;
}

void CalculateManager::Regester( char op, int priority, CalculateProc proc )
{
	this->Priorities[op] = priority;
	this->Procedures[op] = proc;
}

double CalculateManager::Cal_add(double a, double b){return a+b;}
double CalculateManager::Cal_sub(double a, double b){return a-b;}
double CalculateManager::Cal_mul(double a, double b){return a*b;}
double CalculateManager::Cal_div(double a, double b){return a/b;}
double CalculateManager::Cal_mod(double a, double b){return int(a)%int(b);}
double CalculateManager::vCal_fact(double a,double b) {
	double result = 1;
	for (int i = 1; i <= a; i++)
		result *= i;
	return result;
}

double CalculateManager::vCal_pow( const ParameterList* params ){
	const ParameterList& p = *params;
	return ::pow(p[0]->GetUnitValue(), p[1]->GetUnitValue());
}

double CalculateManager::vCal_log( const ParameterList* params )
{
	const ParameterList& p = *params;
	return ::log(p[1]->GetUnitValue()) / ::log(p[0]->GetUnitValue());
}

double CalculateManager::vCal_ln( const ParameterList* params )
{
	const ParameterList& p = *params;
	return ::log(p[0]->GetUnitValue());
}

double CalculateManager::vCal_lg( const ParameterList* params )
{
	const ParameterList& p = *params;
	return ::log10(p[0]->GetUnitValue());
}
double CalculateManager::vCal_sqrt( const ParameterList* params )
{
	const ParameterList& p = *params;
	return ::sqrt( p[0]->GetUnitValue() );
}

bool CalculateManager::IsRegistered(char op)const
{
	return GetProc(op)!=0;
}


int CalculateManager::GetPriority(char op)const
{
	return this->Priorities[op];
}

CalculateManager::CalculateProc CalculateManager::GetProc(char op)const
{
	return this->Procedures[op];
}

void CalculateManager::Regester( const std::string& name, VCalculateProc proc,size_t paramCnt )
{
	this->Method[name] = CalculateManager::MethodInfo(proc, paramCnt);
}

bool CalculateManager::IsRegistered(const std::string& name, size_t* pParamCnt )const
{
	MethodMap::iterator it = this->Method.find( name );
	if( it != Method.end())
	{
		*pParamCnt = it->second.parameterCount;
		return true;
	}
	return false;
}

CalculateManager::VCalculateProc CalculateManager::GetProc(const std::string& name)const
{
	MethodMap::iterator it = this->Method.find( name );
	return it->second.method;
}

 double CalculateManager::vCal_max( const ParameterList* params )
 {
	 const ParameterList& p = *params;
	 return std::max( p[0]->GetUnitValue(), p[1]->GetUnitValue());
 }
 double CalculateManager::vCal_min( const ParameterList* params ){
	 const ParameterList& p = *params;
	 return std::min( p[0]->GetUnitValue(), p[1]->GetUnitValue());
 }
 double CalculateManager::vCal_abs( const ParameterList* params ){
	 const ParameterList& p = *params;
	 return ::abs( p[0]->GetUnitValue() );
 }
 double CalculateManager::vCal_sin( const ParameterList* params ){
	 const ParameterList& p = *params;
	// return ::sin( p[0]->GetUnitValue() );
	 return ::sin( atan(1.0) * 4 * (p[0]->GetUnitValue()) / 180 );
 }
 double CalculateManager::vCal_cos( const ParameterList* params ){
	 const ParameterList& p = *params;
	 return ::cos( atan(1.0) * 4 * (p[0]->GetUnitValue()) / 180 );
 }
 double CalculateManager::vCal_tan( const ParameterList* params ){
	 const ParameterList& p = *params;
	 return ::tan( atan(1.0) * 4 * (p[0]->GetUnitValue()) / 180 );
 }
 double CalculateManager::vCal_asin( const ParameterList* params ){
	 const ParameterList& p = *params;
	 return ::asin( atan(1.0) * 4 * (p[0]->GetUnitValue()) / 180);
 }
 double CalculateManager::vCal_acos( const ParameterList* params ){
	 const ParameterList& p = *params;
	 return ::acos( atan(1.0) * 4 * (p[0]->GetUnitValue()) / 180 );
 }
 double CalculateManager::vCal_atan( const ParameterList* params ){
	 const ParameterList& p = *params;
	 return ::atan( atan(1.0)*4 *( p[0]->GetUnitValue())/180 );
 }
 double CalculateManager::vCal_pi( const ParameterList* params ){
	 return ::atan(1.0)*4;
 }
