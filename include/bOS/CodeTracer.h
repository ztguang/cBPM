#ifndef _CODEMANAGER_CODETRACER_H_
#define _CODEMANAGER_CODETRACER_H_

//TO_BE_EXPORTED

#ifdef WIN32
	#include <strstream>
	#include <sstream>
	#include <iostream>
	#include <map>
	using namespace std;
#else
	#include <map>
	#include <strstream.h>
	#include <sys/time.h>        
#endif

#include "bOS.h"
#include "bOSString.h"
#include "bOSStringBuffer.h"

#include "bOSMutex.h"

namespace CodeManager
{
	typedef map<int, int, less<int> > ThreadMap;
	typedef ThreadMap::value_type ThreadType;

	class CodeItem;

	class BOS_API CodeTracer
	{

	private:

		CodeTracer();
		~CodeTracer();

		static CodeTracer* _instance;

		ofstream strTrace;
		bOS::Core::Mutex mtxTrace;

		Mutex mtxThreadMap;
		ThreadMap threadMap;

		short iLevel;
		bool bInitialized;
		bool bTracerEnabled;
		bOS::CoreString::String sApplicationName;
		bOS::CoreString::StringBuffer sFileName;
		String sOldFileName;
		String sVeryOldFileName;

		void createTraceFile();
		String indentbyThread(int iThreadId, int iItemAction);

	public:

		static CodeTracer* instance ();
		static void deinstance();

		void initialize (const char* acApplicationName, int _Level)  ;
		void initialize (int iArgc, char* argv[]);

		void write(short level, CodeItem*, int iCodeLineNumber, int iItemAction = CodeTracer::NO_ACTION )  ;

		void addItem(CodeItem*);
		void removeItem(CodeItem*);

		/*
		static string sprint(const char *format, ...);
		string indent(int tid)   ;
		void   indentIn(int tid);
		void   indentOut(int tid);
		*/

		static String CODEITEM_IN;
		static String CODEITEM_OUT;

		enum 
		{
			NO_ACTION,
			ADD_ITEM,
			REMOVE_ITEM
		};

		enum
		{
			FATAL_LEVEL = 1,
			ERROR_LEVEL = 2,
			WARNING_LEVEL = 3,
			INFO_LEVEL = 4,
			DEBUG_LEVEL = 5,
			CODEPATH_LEVEL = 6,
			CODEBLOCK_LEVEL = 7
		};
	};
}

#endif //_CODEMANAGER_CODETRACER_H_

