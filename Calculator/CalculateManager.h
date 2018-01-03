#pragma once
#include <string>
#include <map>

class ParameterList;

class CalculateManager
{
	typedef double(*CalculateProc)( double a, double b);
	typedef double(*VCalculateProc)(const ParameterList* params);
public:
	struct MethodInfo
	{
		VCalculateProc  method;
		size_t	parameterCount;
		MethodInfo(){ method=0; parameterCount = 0;}
		MethodInfo(VCalculateProc proc, size_t cnt){ method=proc; parameterCount = cnt;}
	};
	typedef std::map< std::string, MethodInfo>	MethodMap;
private:
	CalculateManager(void);
	~CalculateManager(void);
public:
	void	Regester( char op, int priority, CalculateProc proc );
	void	Regester( const std::string& name, VCalculateProc proc, size_t paramCnt = 0 );

	bool	IsRegistered(char op)const;
	bool	IsRegistered(const std::string& name, size_t* pParamCnt )const;

	int		GetPriority(char op)const;

	CalculateProc	GetProc(char op)const;
	VCalculateProc	GetProc(const std::string& name)const;
private:
	CalculateProc	*Procedures;
	mutable MethodMap		Method;
	int				*Priorities;
public:
	static double Cal_add(double a, double b);
	static double Cal_sub(double a, double b);
	static double Cal_mul(double a, double b);
	static double Cal_div(double a, double b);
	static double Cal_mod(double a, double b);
	static double vCal_fact(double a,double b=0);
	
public:
	static double vCal_pow(const ParameterList* params);
	static double vCal_log( const ParameterList* params );
	static double vCal_ln( const ParameterList* params );
	static double vCal_lg( const ParameterList* params );
	static double vCal_sqrt( const ParameterList* params );
	static double vCal_max( const ParameterList* params );
	static double vCal_min( const ParameterList* params );
	static double vCal_abs( const ParameterList* params );
	static double vCal_sin( const ParameterList* params );
	static double vCal_cos( const ParameterList* params );
	static double vCal_tan( const ParameterList* params );
	static double vCal_asin( const ParameterList* params );
	static double vCal_acos( const ParameterList* params );
	static double vCal_atan( const ParameterList* params );
	static double vCal_pi( const ParameterList* params );

	static CalculateManager M;
};

