#include "CommonDefines.h"

#include "bOS.h"
#include "bOSStringBuffer.h"
#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSFileSystem.h"
using namespace bOS::IO;

#include "CodeItem.h"
#include "CodeTracer.h"
using namespace CodeManager;

CodeItem::CodeItem(const char* acName, const char* acFile, bool _Ticks)
{
	sName = acName;
	sFile = FileSystem::getFileName(acFile);

	sBuffer.append(CodeTracer::CODEITEM_IN);

	bTicks=_Ticks;
	if ( _Ticks ) 
	{
		timer.start();
	}

	CodeTracer::instance()->write(CodeTracer::CODEBLOCK_LEVEL, this, 0, CodeTracer::ADD_ITEM);
}

CodeItem::~CodeItem()
{
	sBuffer.append(CodeTracer::CODEITEM_OUT);

	if (bTicks) 
	{
		timer.stop();
	}

	CodeTracer::instance()->write(CodeTracer::CODEBLOCK_LEVEL, this, 0, CodeTracer::REMOVE_ITEM);
}

String CodeItem::getTicks()
{
	StringBuffer sMs;
	sMs.append(timer.getTicks());
	sMs.append("ms");

	return sMs.getData();
}

void CodeItem::add (unsigned int iLevel, const char *s, int iCodeLineNumber)
{
    sBuffer.append(s);
	CodeTracer::instance()->write (iLevel, this, iCodeLineNumber);
}

void CodeItem::add (unsigned int iLevel, const String &s, int iCodeLineNumber)
{
    sBuffer.append(s);
	CodeTracer::instance()->write (iLevel, this, iCodeLineNumber);
}

void CodeItem::add (unsigned int iLevel, int n, int iCodeLineNumber)
{
	sBuffer.append(n);
	CodeTracer::instance()->write (iLevel, this, iCodeLineNumber  );
}

void CodeItem::add (unsigned int iLevel, long n, int iCodeLineNumber)
{
    sBuffer.append(n);
	CodeTracer::instance()->write (iLevel, this, iCodeLineNumber  );
}

void CodeItem::add (unsigned int iLevel, short n, int iCodeLineNumber)
{
	sBuffer.append(n);
	CodeTracer::instance()->write (iLevel, this, iCodeLineNumber  );
}

void CodeItem::add (unsigned int iLevel, char n, int iCodeLineNumber)
{
	sBuffer.append(n);
	CodeTracer::instance()->write (iLevel, this, iCodeLineNumber  );
}

void CodeItem::add (unsigned int iLevel, double d, int iCodeLineNumber)
{
	sBuffer.append(d);
	CodeTracer::instance()->write (iLevel, this, iCodeLineNumber  );
}

void CodeItem::add (unsigned int iLevel, ostrstream &os, int iCodeLineNumber)
{
   	sBuffer.append(os.str());
	CodeTracer::instance()->write (iLevel, this, iCodeLineNumber  );
}
/*
void STRC_Buffer::addFormatted (const char *format, const char *arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, int arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, long arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, short arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, char arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, unsigned int arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, unsigned long arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, unsigned short arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, unsigned char arg)
{
    char s[500];

    sprintf(s, format, arg);
    mBuff += s;
}

void STRC_Buffer::addFormatted (const char *format, double d)
{
    char s[500];

    sprintf(s, format, d);
    mBuff += s;
}
*/

const char* CodeItem::getBuffer()
{
	return sBuffer.getData();
}

void CodeItem::clear()
{
	sBuffer.clear();
}