#include "WrongFormatException.h"
#include "ParseBuffer.h"


WrongFormatException::WrongFormatException(const ParseBuffer* pBuf)
	:runtime_error("Unable to parse the format string since there is an WRONG format")
{
	this->FormatBuffer = pBuf;
}

WrongFormatException::WrongFormatException(const std::string& message ,const ParseBuffer* pBuf)
	:runtime_error( message )
{
	this->FormatBuffer = pBuf;
}

UndefineMethodException::UndefineMethodException(const ParseBuffer* pBuf)
	:WrongFormatException("There is no such a named method",pBuf)
{
}

WrongFormatException::~WrongFormatException() throw()
{
}
