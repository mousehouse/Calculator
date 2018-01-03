#pragma once
#include "formularunit.h"

#define MAX_METHOD_NAME		20

// pre-declare
class ParameterList;

class MethodUnit : public FormularUnit
{
	// 方法名
	char						m_name[MAX_METHOD_NAME];
	// 参数列表
	ParameterList*				m_parameters;
public:
	MethodUnit(void);
	MethodUnit(ParseBuffer* buffer);
	virtual ~MethodUnit(void);
public:
	void ParseFrom(ParseBuffer* buffer);
	static bool IsNameChar(char ch);
	virtual double GetUnitValue(void)const;
};

