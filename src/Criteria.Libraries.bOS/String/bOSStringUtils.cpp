#include "CommonDefines.h"

#include "bOSStringUtils.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

#define TO_STRING_TXT_SIZE	50
#define MAX_TRACE_STRING        5000

int StringUtils::compareNoCase( const String& lhs, const String& rhs )
{
	String::const_iterator ilhs = lhs.begin();
	String::const_iterator irhs = rhs.begin();

	while ( ilhs != lhs.end() && irhs != rhs.end() )
	{
		if ( toupper(*ilhs) != toupper(*irhs) )
			return (toupper(*ilhs) < toupper(*irhs)) ? -1 : 1;
		irhs++;
		ilhs++;
	}
	return (rhs.size() ==lhs.size()) ? 0 : (lhs.size() < rhs.size()) ? -1 : 1;
}

String StringUtils::format( String formatText, ... )
{
    String result = "";

    // Initialize variable arguments.
    va_list argList;
    va_start( argList, formatText );
    char* buf = new char[MAX_TRACE_STRING];
    memset( buf, 0, MAX_TRACE_STRING );

    #ifdef _BOS_ON_WIN32_
        _vsnprintf( buf, MAX_TRACE_STRING, formatText.c_str(), argList );
	#else // _PFC_ON_SOLARIS_ _PFC_ON_HP_
        vsnprintf( buf, MAX_TRACE_STRING, formatText.c_str(), argList );
    #endif

    va_end( argList );
    // Reset variable arguments.

    result = buf;
    delete [] buf;
    return result;
}


String StringUtils::toLowerCase( const String text )
{
    String result = "";
	unsigned int iSize=strlen(text.c_str());

    for (unsigned int i = 0; i < iSize; i++)
        result += tolower( text[i] );

    return result;
}

String StringUtils::toUpperCase( const String text )
{
    String result = "";
	unsigned int iSize = strlen(text.c_str());

    for (unsigned int i = 0; i < iSize; i++)
        result += toupper( text[i] );

    return result;
}

String StringUtils::toString( const int& value )
{
    char tmp[TO_STRING_TXT_SIZE];
    memset( tmp, 0, TO_STRING_TXT_SIZE );
    sprintf( tmp, "%d", value );
    return String( tmp );
}

String StringUtils::toString( const long& value )
{
    char tmp[TO_STRING_TXT_SIZE];
    memset( tmp, 0, TO_STRING_TXT_SIZE );
    sprintf( tmp, "%ld", value );
    return String( tmp );
}

String StringUtils::toString( const float& value )
{
    char tmp[TO_STRING_TXT_SIZE];
    memset( tmp, 0, TO_STRING_TXT_SIZE );
    sprintf( tmp, "%.5f", value );
    return String( tmp );
}

String StringUtils::toString( const double& value )
{
    char tmp[TO_STRING_TXT_SIZE];
    memset( tmp, 0, TO_STRING_TXT_SIZE );
    sprintf( tmp, "%.5f", value );
    return String( tmp );
}

String StringUtils::toString( const unsigned long & value )
{
    char tmp[TO_STRING_TXT_SIZE];
    memset( tmp, 0, TO_STRING_TXT_SIZE );
    sprintf( tmp, "%ld", value );
    return String( tmp );
}

String StringUtils::toString( const unsigned int & value )
{
    char tmp[TO_STRING_TXT_SIZE];
    memset( tmp, 0, TO_STRING_TXT_SIZE );
    sprintf( tmp, "%d", value );
    return String( tmp );
}

String StringUtils::toString( const char& value )
{
    char tmp[TO_STRING_TXT_SIZE];
    memset( tmp, 0, TO_STRING_TXT_SIZE );
    sprintf( tmp, "%c", value );
    return String( tmp );
}

String StringUtils::toString( const bool& value )
{
    return ( value == true ) ? "true" : "false";
}

double StringUtils::toDouble( const String& value )
{
    return atof( value.c_str() );
}

long StringUtils::toLong( const String& value )
{
    return atol( value.c_str() );
}

longlong StringUtils::toLongLong( const String& value )
{
#ifdef _BOS_ON_WIN32_
    return atol( value.c_str() );
#elif defined _BOS_ON_SOLARIS_ 
	return atol( value.c_str() );
#elif defined _BOS_ON_HP_
      long long llValue=0;
      int       iSign=1;
	  const char* acValue = value.c_str();

      /*skipping space and tab */
      while (*acValue == ' ' || *acValue == '\t' ) 
          acValue++;

      /*check sign*/
      if ( *acValue == '-' )       
          iSign = -1;

      /* convert String to int */
      while (*acValue != '\0')
          if (*acValue >= '0' && *acValue <= '9')
              llValue = (llValue * 10LL) + (*acValue++ - '0');
          else
              acValue++;

      return (llValue*iSign);
#endif

}

int StringUtils::toInteger( const String& value )
{
    return atoi( value.c_str() );
}

unsigned int StringUtils::toUInteger( const String& value )
{
    return atoi( value.c_str() );
}

String StringUtils::getErrorString( const long& errorCode )
{
    String result = "";

    #ifdef _BOS_ON_WIN32_
        LPVOID lpMessageBuffer = 0;
        FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                       (LPTSTR) &lpMessageBuffer, 0, NULL );
        result = (char*)lpMessageBuffer;
        LocalFree( (HLOCAL)lpMessageBuffer );
        // Strip trailing .crlf if present
        if ( result.size() > 2 && (result[result.size()-3] == '.') )
	        result.erase( result.size() - 3 );
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        result = String( strerror(errorCode) );
    #endif

    return result;
}

String StringUtils::duplicate( const char* source )
{
    char* newString;
    newString = strdup( source );
    String s = newString;
    free( newString );
    return s;
}

void StringUtils::trim( String& source )
{
    if ( source.find_first_not_of("\t\n ") != String::npos )
        source = source.substr( source.find_first_not_of("\t\n ") );

    if ( source.find_last_not_of("\t\n ") != String::npos )
        source = source.substr( 0, source.find_last_not_of("\t\n ") + 1 );
}

char* StringUtils::toChar(const String& s)
{
	unsigned int uiSize = s.size();
	char* c = new char[uiSize + 1];
	strcpy(c, s.c_str());
	return c;
}

char* StringUtils::toChar(char* s)
{
	unsigned int uiSize = strlen(s);
	char* c = new char[uiSize + 1];
	strcpy(c, s);
	return c;
}

void StringUtils::quoteAndTwice( String& source )
{
	char CHAR_APICE = 39;
    String STRING_APICE = "'";

	StringBuffer s;
    s.append( STRING_APICE.c_str() );
	for (unsigned int i = 0; i < source.length(); i++)
	{
		s.append( source.substr(i,1).c_str() );
        if ( source.at(i) == CHAR_APICE )
			s.append( STRING_APICE.c_str() );
	}
	s.append( STRING_APICE.c_str() );

    source = s.getData();
}

String StringUtils::returnQuoteAndTwice( const String& source)
{
    String s=source;

    StringUtils::quoteAndTwice(s);

    return s;
}

String StringUtils::fillWith(const String& sSrc, String sFiller, bool bFillLeft)
{
	String sRet;

	if ( bFillLeft )
	{
		sRet = sFiller.substr( 1, (sFiller.length() - sSrc.length()) );
		sRet += sSrc;
	}
	else
	{
		sRet = sSrc;
		sRet += sFiller.substr( 1, (sFiller.length() - sSrc.length()) );
	}
		
	return sRet;
}
