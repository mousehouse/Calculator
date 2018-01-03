#include "ParseBuffer.h"
#include <string.h>

ParseBuffer::ParseBuffer( const char* formular )
{
	this->setBuffer( formular );
}

ParseBuffer::ParseBuffer( const ParseBuffer& copy )
{
	this->m_nSize = this->m_nCur = 0;
	this->m_pBuf = 0;
	if( !copy.IsEOF() ) this->setBuffer( &copy.m_pBuf[ copy.m_nCur ] );
}

ParseBuffer::~ParseBuffer(void)
{
	if( this->m_pBuf ){ 
		delete[] this->m_pBuf;
		this->m_pBuf = 0;
	}
}


// read a byte from buffer and update the buffer pointer 
char ParseBuffer::Read(void)
{
	return this->m_pBuf[ this->m_nCur++ ];
}


// peek a byte from buffer without update the pointer of buffer
char ParseBuffer::Peek(void) const
{
	return this->m_pBuf[ this->m_nCur ];
}


// determine if the current pointer is at the end of the buffer
bool ParseBuffer::IsEOF(void) const
{
	return this->m_nCur >= this->m_nSize;
}


// reset the buffer 
char* ParseBuffer::setBuffer(const char* formular)
{
	char* prev = this->m_pBuf;
	
	this->m_nSize	= ::strlen( formular );
	this->m_nCur	= 0;
	this->m_pBuf	= new char[ this->m_nSize+1];
	::strcpy( this->m_pBuf, formular);
	this->m_pBuf[this->m_nSize] = 0;

	return prev;
}


// get current position of the pointer to buffer
int ParseBuffer::GetCurrentPosition(void)const
{
	return this->m_nCur;
}


// retrive the whole stream of buffer
const char* ParseBuffer::GetStream(void)const
{
	return this->m_pBuf;
}
