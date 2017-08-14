
#ifndef __BOS_SYSTEM_H__
#define __BOS_SYSTEM_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSString.h"

//ztg add
//#include <string>
std::string expand_environment_variables( const std::string& s ) ;

using namespace bOS::CoreString;

namespace bOS
{
    namespace CoreSystem
    {
        enum EnvironmentStrategy
        {
            esCreate = 1,
            esOverwrite,
            esAppendBegin,
            esAppendAtEnd
        };

        class BOS_API System
        {
            public:

                static unsigned long getCurrentTimeMillis();

                //the following two functions are same
				static String expandEnvironmentStrings( const String& sString );
                static String getEnvironmentVariable( const String& Name );

                static void setEnvironmentVariable( String Name, String Value, EnvironmentStrategy es = esCreate );
                static String getHostName();
                static String createUUID();

				static String getErrorString( const long lErrorCode);
        };
    }
};

#endif


