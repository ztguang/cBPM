#include "CommonDefines.h"

#include "bOSMutex.h"
using namespace bOS::Core;

#include "bOSFileSystem.h"
using namespace bOS::IO;

#include "bOSDateTime.h"
#include "bOSDate.h"
#include "bOSTime.h"
using namespace bOS::Utils;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSSystem.h"
using namespace bOS::CoreSystem;

#include "bOSThread.h"
using namespace bOS::Core;

#include "bOSProcess.h"
using namespace bOS::System;

#include "CodeTracer.h"
#include "CodeItem.h"
using namespace CodeManager;

const char* CM_ALLPATH	= "${CM_ALLPATH}";
const char* CM_TRACEPATH= "${CM_TRACEPATH}";
const unsigned int CM_TRACEFILE_SIZE = 10000000;

//Application Parameter
const char* TRACE_LEVEL_PARAMETER = "TRACE";
const int TRACE_LEVELS = 8;
const int TRACE_ONLYTIMER=8;
const char* TRACE_LEVEL[] = {
							"FATAL",
							"ERROR",
							"WARNING",
							"INFO",
							"DEBUG",
							"CODEPATH",
							"CODEBLOCK",
							"ONLYTIMER"
							};

String CodeTracer::CODEITEM_IN	="IN";
String CodeTracer::CODEITEM_OUT	="OUT";

CodeTracer* CodeTracer::_instance = (CodeTracer*)NULL;

CodeTracer* CodeTracer::instance()
{
    if (_instance == NULL )
	{
        _instance = new CodeTracer();
	}

    return _instance;
}

void CodeTracer::deinstance()
{
    if ( _instance != NULL )
	{
        delete _instance;
	}
}

CodeTracer::CodeTracer()
{
	iLevel = 0;
	bInitialized=false;
	bTracerEnabled=false;
	sApplicationName="";
}

CodeTracer::~CodeTracer()
{
}

void CodeTracer::initialize(const char* acApplicationName, int _Level)
{
    if ( bInitialized )
		return;

	bInitialized = true;
	sApplicationName = FileSystem::getFileName(acApplicationName);
	iLevel = _Level;

    if (iLevel > 0)
        bTracerEnabled = true;

	this->createTraceFile();
}

void CodeTracer::initialize(int iArgc, char* argv[])
{
    if ( bInitialized )
		return;

	bInitialized = true;

	sApplicationName = FileSystem::getFileName(argv[0], true);
	iLevel = 0;

	for ( int i=1; i<iArgc;i++)
	{
		String sArg=argv[i];

		int iPos;
		if ( (iPos=sArg.find_first_of("=")) != -1 )
		{
			String sLeftValue = sArg.substr(0, iPos);
			String sRightValue = sArg.substr(iPos+1);

			if ( !strcmp(sLeftValue.c_str(), TRACE_LEVEL_PARAMETER) )
			{
				for ( int j=0; j<TRACE_LEVELS;j++)
				{
					if ( !strcmp(sRightValue.c_str(), TRACE_LEVEL[j]) )
					{
						iLevel = j+1;
						break;
					}
				}

				if ( iLevel == 0 )
				{
					iLevel = 4;
				}
			}
		}
	}

    if (iLevel > 0)
        bTracerEnabled = true;

	this->createTraceFile();
}

void CodeTracer::createTraceFile()
{
	DateTime dt = DateTime::getCurrentDateTime();
	Date date = dt.getDate();
	Time time = dt.getTime();

	StringBuffer sFile2Open;

	String sTracePath = System::getEnvironmentVariable(CM_TRACEPATH);
	if ( strcmp(sTracePath.c_str(), "") )
	{
		sFile2Open.append(sTracePath );
		sFile2Open.append(SLASH);
	}

	sFile2Open.append(sApplicationName);
	sFile2Open.append("-");
	sFile2Open.append((long)Process::getCurrentProcessId());
	sFile2Open.append("-");
	sFile2Open.append(StringUtils::format("%04i%02i%02i",
									date.getYear(),
									date.getMonth(),
									date.getDay()));
	sFile2Open.append("-");

	sFile2Open.append(StringUtils::format("%02i%02i%02i",
									time.getHour(),
									time.getMinutes(),
									time.getSeconds()));

	sFileName.clear();
	sFileName.append(sFile2Open.getData());
	sFileName.append(".trace");

	for (int i=0; (FileSystem::getFileAttributeFlags(sFileName.getData()) & FileAttribute(Exists)); i++)
	{
		sFileName.clear();
		sFileName.append(sFile2Open.getData());
		sFileName.append ("_");
		sFileName.append(i);
		sFileName.append(".trace");
    }

	//FileName found. Close old Stream.
    if (sOldFileName != "" )
    {
        strTrace << endl;
        strTrace << "to -- " << sFileName.getData() << " ------" << endl;
        strTrace.close();

		if ( sVeryOldFileName != "" )
		{
			FileSystem::deleteFile (sVeryOldFileName);
		}
    }
    strTrace.clear();

    strTrace.open( sFileName.getData() );

    if (strTrace.good())
    {
		strTrace << "Tracing[" << sApplicationName << "] at " << time.toString() << " " << date.toString() << endl;
		strTrace << "-----------------------------------------------------------------" << endl;

        if ( sOldFileName.length() > 0 )
        {
            strTrace << endl << " from --" << sOldFileName << " ------" << endl;
        }

		sVeryOldFileName = sOldFileName;
        sOldFileName = sFileName.getData();
    }
}

void CodeTracer::write(short level, CodeItem* item, int iCodeLineNumber, int iItemAction)
{
    if ( ((level < 1) || (level > 7)) || (level > iLevel) )
	{
		item->clear();
        return;
	}

	if ( (iLevel == TRACE_ONLYTIMER) && (iItemAction != CodeTracer::REMOVE_ITEM) )
	{
		item->clear();
        return;
	}

	int iThreadId = (int)Thread::getCurrentThreadId();
	char acThread[10];

	//tracer row
	StringBuffer sTrc;

	//
	sTrc.append(DateTime::getCurrentDateTime().getTime().toString());
	sTrc.append("-");

	//
	sprintf(acThread,"%5d",iThreadId);
	sTrc.append(acThread);

	sTrc.append("-");

	//
	sTrc.append(this->indentbyThread(iThreadId, iItemAction));

	sTrc.append(item->getName());

	sTrc.append("-");
	/*
	String sThreadId = StringUtils::toString((int)Thread::getCurrentThreadId());
	sTrc.append(StringUtils::fillWith (sThreadId, "      ", true) );
	*/
    switch (level)
	{
        case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			sTrc.append(TRACE_LEVEL[level-1]);
			break;

        default:
			sTrc.append(level);
			break;
    }

	sTrc.append("-");
	sTrc.append(item->getFile());
	if ( iCodeLineNumber>0)
	{
		sTrc.append("[");
		sTrc.append(iCodeLineNumber);
		sTrc.append("]");
	}
	sTrc.append("-");
	sTrc.append(item->getBuffer());

	switch ( iItemAction)
	{
	case NO_ACTION:
	case ADD_ITEM:
		break;
	case REMOVE_ITEM:
		sTrc.append("[");
		sTrc.append(item->getTicks());
		sTrc.append("]");
		break;
	}

    if ( strTrace.good())
    {
		Mutex::Lock locker(mtxTrace);

		strTrace << sTrc.getData();
		strTrace << endl;

		if (strTrace.tellp() > CM_TRACEFILE_SIZE)
		{
			this->createTraceFile();
		}
    }
    else
    {
		cerr << sTrc.getData();
		cerr << endl;
	}

	item->clear();
}

String CodeTracer::indentbyThread(int iThreadId, int iItemAction)
{
	Mutex::Lock locker(mtxThreadMap);

	String sRet;

	ThreadMap::iterator tmi = threadMap.find(iThreadId);

    if ( tmi == threadMap.end() )
    {
        threadMap.insert( ThreadType(iThreadId,1) );
    }
	else
	{
		switch ( iItemAction)
		{
		case NO_ACTION:
			sRet.resize(tmi->second,' ');
			break;

		case ADD_ITEM:
			sRet.resize(tmi->second,' ');
			tmi->second++;
			break;

		case REMOVE_ITEM:
			tmi->second--;
			sRet.resize(tmi->second,' ');
			break;
		}


	}

	return sRet;
}

/*
string STracer::sprint(const char *format, ...)
{
    static char buf[50000];

    va_list ap;

    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);

    return buf;
}
*/
