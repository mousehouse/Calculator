#pragma once
#include <vector>

// pre-delcare
class FormularUnit;

class ParameterList : public std::vector< FormularUnit* >
{
public:
	ParameterList(void);
	virtual ~ParameterList(void);
};

