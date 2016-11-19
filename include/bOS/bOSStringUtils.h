#ifndef __BOS_STRINGUTILS_H__
#define __BOS_STRINGUTILS_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

namespace bOS
{
    namespace CoreString
    {
        class BOS_API StringUtils
        {
            public:

                static int compareNoCase( const String& lhs, const String& rhs );

                static String format( String formatText, ... );

                static String toLowerCase( const String text );

                static String toUpperCase( const String text );

                static String toString( const int& value );

                static String toString( const long& value );

                static String toString( const float& value );

                static String toString( const double& value );

                static String toString( const unsigned long& value );

                static String toString( const unsigned int& value );

                static String toString( const char& value );

                static String toString( const bool& value );

                static double toDouble( const String& value );

                static long toLong( const String& value );

                static longlong toLongLong( const String& value );

                static int toInteger( const String& value );

				static unsigned int toUInteger( const String& sValue);

                static String getErrorString( const long& errorCode );

                static String duplicate( const char* source );

                static void trim( String& source );

				static String fillWith(const String& sSrc, String sFiller, bool bFillLeft);

				static char* toChar(const String& s);
				static char* toChar(char* s);

				static void quoteAndTwice( String& source );
				static String returnQuoteAndTwice( const String& source);
        };
    }
};

#endif



