#ifndef _CODEMAANGER_MACROS_H_
#define _CODEMAANGER_MACROS_H_

//TO_BE_EXPORTED

#include "CodeTracer.h"
#include "CodeItem.h"
using namespace CodeManager;

#ifdef _CODEMANAGER_TRACE_ON_

	#define CM_SETTING_BY_MAINARGS  CodeManager::CodeTracer::instance()->initialize(argc, argv);
	#define CM_SETTING_TO(programName, traceLevel) CodeManager::CodeTracer::instance()->initialize(programName, traceLevel);

#ifdef _NO_TICKS_
	#define CM_CODEBLOCK(fname)		CodeManager::CodeItem myCodeItem(#fname, __FILE__, false);
#else
	#define CM_CODEBLOCK(fname)		CodeManager::CodeItem myCodeItem(#fname, __FILE__);
#endif

	#define CM_TRACE(level, msg)  {\
							ostringstream TRC__os;\
							TRC__os << msg << ends;\
							myCodeItem.add(level, TRC__os.str(), __LINE__);\
							}


	//TRACE By Level
	#define CM_TRACE_FATAL(msg)			CM_TRACE(CodeManager::CodeTracer::FATAL_LEVEL, msg)
	#define CM_TRACE_ERROR(msg)			CM_TRACE(CodeManager::CodeTracer::ERROR_LEVEL, msg)
	#define CM_TRACE_WARNING(msg)		CM_TRACE(CodeManager::CodeTracer::WARNING_LEVEL, msg)
	#define CM_TRACE_INFO(msg)			CM_TRACE(CodeManager::CodeTracer::INFO_LEVEL, msg)
	#define CM_TRACE_DEBUG(msg)			CM_TRACE(CodeManager::CodeTracer::DEBUG_LEVEL, msg)
	#define CM_TRACE_CODEPATH(msg)		CM_TRACE(CodeManager::CodeTracer::CODEPATH_LEVEL, msg)
	#define CM_TRACE_CODEBLOCK(msg)		CM_TRACE(CodeManager::CodeTracer::CODEBLOCK_LEVEL, msg)

	//C++ Constructs
	#define CM_TRACE_IF(cond)			if (cond) {
	#define CM_TRACE_ELSEIF(cond)		} else if (cond) {
	#define CM_TRACE_ELSE				} else {
	#define CM_TRACE_ENDIF				}
	#define CM_TRACE_SWITCH(var)		switch(var) {
	#define CM_TRACE_CASE(val)			case val:
	#define CM_TRACE_DEFAULT			default:
	#define CM_TRACE_ENDSWITCH			}
	#define CM_TRACE_FOR(cond1, cond2, cond3)	for (cond1; cond2; cond3) {
	#define CM_TRACE_NEXT				}
	#define CM_TRACE_WHILE(cond)		while(cond) {
	#define CM_TRACE_DONE				}
	#define CM_TRACE_CONTINUE			continue;
	#define CM_TRACE_BREAK				break;

#else

	#define CM_SETTING_BY_MAINARGS
	#define CM_SETTING_TO(programName, traceLevel)
	#define CM_CODEBLOCK(fname)
	#define CM_TRACE(level, msg)

	//TRACE By Level
	#define CM_TRACE_FATAL(msg)
	#define CM_TRACE_ERROR(msg)
	#define CM_TRACE_WARNING(msg)
	#define CM_TRACE_INFO(msg)
	#define CM_TRACE_DEBUG(msg)
	#define CM_TRACE_CODEPATH(msg)
	#define CM_TRACE_CODEBLOCK(msg)

	//C++ Constructs
	#define CM_TRACE_IF(cond)
	#define CM_TRACE_ELSEIF(cond)
	#define CM_TRACE_ELSE
	#define CM_TRACE_ENDIF
	#define CM_TRACE_SWITCH(var)
	#define CM_TRACE_CASE(val)
	#define CM_TRACE_DEFAULT
	#define CM_TRACE_ENDSWITCH
	#define CM_TRACE_FOR(cond1, cond2, cond3)
	#define CM_TRACE_NEXT
	#define CM_TRACE_WHILE(cond)
	#define CM_TRACE_DONE
	#define CM_TRACE_CONTINUE
	#define CM_TRACE_BREAK

#endif
    
    
#endif //_CODEMAANGER_MACROS_H_
