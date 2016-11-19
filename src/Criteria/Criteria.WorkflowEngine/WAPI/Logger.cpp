#include "CommonDefines.h"

#include "WAPI.h"
#include "WAPIError.h"

#include "Tracer.h"

extern "C" ENGINE_API void LoggerLevel(const char* acLog, int iTraceLevel)
{
	CM_CODEBLOCK(Logger)

	CM_TRACE(iTraceLevel, acLog);
}

extern "C" ENGINE_API void Logger(const char* acLog)
{
	LoggerLevel( acLog, CodeTracer::CODEBLOCK_LEVEL);
}

