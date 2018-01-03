#pragma once

#include <stdexcept>
#include <string>

// pre-declaration
class ParseBuffer;

class WrongFormatException : public std::runtime_error
{
public:
	const ParseBuffer*	FormatBuffer;
public:
	WrongFormatException(const ParseBuffer*);
	WrongFormatException(const std::string& message ,const ParseBuffer*);
	~WrongFormatException() throw();
};

class UndefineMethodException : public WrongFormatException
{
public:
	UndefineMethodException(const ParseBuffer*);
};

