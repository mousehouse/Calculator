#pragma once
class ParseBuffer
{
private:
	char*	m_pBuf;
	int		m_nSize;
	int		m_nCur;
public:
	ParseBuffer( const char* formular );
	ParseBuffer( const ParseBuffer& copy );
	virtual ~ParseBuffer(void);
	// read a byte from buffer and update the buffer pointer 
	char Read(void);
	// peek a byte from buffer without update the pointer of buffer
	char Peek(void) const;
	// determine if the current pointer is at the end of the buffer
	bool IsEOF(void) const;
private:
	// reset the buffer 
	char* setBuffer(const char* formular);
public:
	// get current position of the pointer to buffer
	int GetCurrentPosition(void)const;
	// retrive the whole stream of buffer
	const char* GetStream(void) const;
};

