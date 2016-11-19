#ifndef _CODEMANAGER_CODEITEM_H_
#define _CODEMANAGER_CODEITEM_H_

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSString.h"
#include "bOSStringBuffer.h"

#include "bOSTimer.h"

namespace CodeManager
{
	class BOS_API CodeItem
	{
	public:

		CodeItem(const char* acName, const char* acFile, bool bTicks = true); 
		~CodeItem();

	private:

		bOS::CoreString::String sName;
		bOS::CoreString::String sFile;
		bOS::CoreString::StringBuffer sBuffer;

		bool bTicks;
		bOS::Utils::Timer timer;

	public:

		String& getName() { return sName;}
		String& getFile() { return sFile;}

		bool bIsTicked() { return bTicks;}
		String getTicks();

		const char* getBuffer();
		void clear();

		void add (unsigned int iLevel, const char *s, int iCodeLineNumber);
		void add (unsigned int iLevel, const bOS::CoreString::String& s, int iCodeLineNumber);
		void add (unsigned int iLevel, int n, int iCodeLineNumber);
		void add (unsigned int iLevel, long n, int iCodeLineNumber);
		void add (unsigned int iLevel, short n, int iCodeLineNumber);
		void add (unsigned int iLevel, char n, int iCodeLineNumber);
		void add (unsigned int iLevel, double, int iCodeLineNumber);
		void add (unsigned int iLevel, ostrstream &os, int iCodeLineNumber);

		/*
		void addFormatted (const char *format, const char *s);
		void addFormatted (const char *format, int n);
		void addFormatted (const char *format, long n);
		void addFormatted (const char *format, short n);
		void addFormatted (const char *format, char n);
		void addFormatted (const char *format, unsigned int n);
		void addFormatted (const char *format, unsigned long n);
		void addFormatted (const char *format, unsigned short n);
		void addFormatted (const char *format, unsigned char n);
		void addFormatted (const char *format, double);
		*/
	};
}

#endif //_CODEMANAGER_CODEITEM_H_