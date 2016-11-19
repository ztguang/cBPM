#include "CommonDefines.h"

#include "bOSStringBuffer.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

StringBuffer::StringBuffer() 
{
	str = allocator(1000);
}

StringBuffer::StringBuffer( unsigned int value )
{
	str = allocator(value);
}

StringBuffer::~StringBuffer()
{
	if ( str) 
		delete str;
}

void StringBuffer::append(const char* s)
{
	unsigned int iAppend=strlen(s);

	if ( iBufferEmpty <  iAppend) 
	{
		int iOld = iStr;
		char* c = allocator( (iBuffer + iBuffer) + iAppend);
		memcpy(c, str, iOld);
		delete[] str;
		str=c;
		iBufferEmpty-=iOld;
		iStr=iOld;
	}

	memcpy(&str[iStr], s, iAppend);
	iBufferEmpty-=iAppend;
	iStr+=iAppend;
}

void StringBuffer::append(const char* s, unsigned int uiSize)
{
	if ( iBufferEmpty <  uiSize) 
	{
		int iOld = iStr;
		char* c = allocator( (iBuffer + iBuffer) + uiSize);
		memcpy(c, str, iOld);
		delete[] str;
		str=c;
		iBufferEmpty-=iOld;
		iStr=iOld;
	}

	memcpy(&str[iStr], s, uiSize);
	iBufferEmpty-=uiSize;
	iStr+=uiSize;
}

void StringBuffer::append(const String& sValue)
{
	this->append (sValue.c_str());
}

void StringBuffer::append( const long lValue)
{
	this->append ( StringUtils::toString(lValue));
}

void StringBuffer::append( const int iValue)
{
	this->append ( StringUtils::toString (iValue));
}

void StringBuffer::append( const double dValue)
{
	this->append ( StringUtils::toString (dValue));
}

void StringBuffer::append( const char ch)
{
	this->append ( StringUtils::toString (ch));
}

const char* StringBuffer::getData()
{
	return str;
}

char* StringBuffer::allocator(unsigned int _len)
{
	iBuffer=_len;
	char* c = new char[_len + 1];
	memset(c, 0 , _len + 1);
	iBufferEmpty=_len;
	iStr=0;
	return c;
}

void StringBuffer::clear()
{
	if ( str) 
		delete str;

	str = allocator(1000);
}

int StringBuffer::size()
{
	return iBuffer - iBufferEmpty;

}
