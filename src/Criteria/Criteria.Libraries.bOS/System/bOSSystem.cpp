#include "CommonDefines.h"

#include "bOSRuntimeException.h"
using namespace bOS::Exception;

#include "bOSSystem.h"
using namespace bOS::CoreSystem;

#define MAX_VAR 8192

unsigned long System::getCurrentTimeMillis()
{
    #ifdef _BOS_ON_WIN32_
        return ((unsigned long)::GetTickCount());
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        timeb aTime;
        ftime(&aTime);
        return (unsigned long)(aTime.time*1000 + aTime.millitm);
    #endif
}

void System::setEnvironmentVariable(String Name, String Value, EnvironmentStrategy es)
{
    #ifdef _BOS_ON_WIN32_
        HKEY _userEnv;
        Char newVar[MAX_VAR];
        //Open the HKEY_CURRENT_USER\Environment key
        LONG lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Environment\\", 0, KEY_ALL_ACCESS, &_userEnv);
        if ( lRet != ERROR_SUCCESS )
        {
            LPVOID lpMsgBuffer;
            FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpMsgBuffer, 0, NULL );
            throw RuntimeException( ENV_DEFAULT_ERROR + String((LPTSTR)lpMsgBuffer) );
        }
        unsigned long lType = 0;
        unsigned long lSize = MAX_VAR;
        if ( (es != esCreate) && (es != esOverwrite) )
        {
            //Query if the variable name exist
            lRet = RegQueryValueEx(_userEnv, Name.c_str(), NULL, &lType, (Byte*)newVar, &lSize);
            if ( lRet != ERROR_SUCCESS )
            {
                LPVOID lpMsgBuffer;
                FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                            (LPTSTR) &lpMsgBuffer, 0, NULL );
                throw RuntimeException( ENV_DEFAULT_ERROR + String((LPTSTR)lpMsgBuffer) );
            }
        }
        switch (es)
        {
        case esCreate:
        case esOverwrite:
            {
                strcpy(newVar, Value.c_str());
                lSize = Value.length();
            }
            break;
        case esAppendBegin:
            {
                String tmp = newVar;
                Value += ";" + tmp;
                strcpy( newVar, Value.c_str() );
                lSize = Value.length();
            }
            break;
        case esAppendAtEnd:
            {
                strcat( newVar, ";" );
                strcat( newVar, Value.c_str() );
                lSize = strlen( newVar ) + 1;
            }
            break;
        }
        //Set the new variable
        lRet = RegSetValueEx(_userEnv, Name.c_str(), NULL, REG_SZ, (Byte*)newVar, lSize);
        if ( lRet != ERROR_SUCCESS )
        {
            LPVOID lpMsgBuffer;
            FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpMsgBuffer, 0, NULL );
            throw RuntimeException( ENV_DEFAULT_ERROR + String((LPTSTR)lpMsgBuffer) );
        }
        lRet = RegCloseKey(_userEnv);
        if ( lRet != ERROR_SUCCESS )
        {
            LPVOID lpMsgBuffer;
            FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpMsgBuffer, 0, NULL );
            throw RuntimeException( ENV_DEFAULT_ERROR + String((LPTSTR)lpMsgBuffer) );
        }
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        /*
        #ifdef HAVE_SETENV
            setenv(name, value, (int)overwrite);
        #else
            char strbuf[256];
            _snprintf(strbuf, sizeof(strbuf), "%s=%s", Name, Value);
            if(!Overwrite)
                if(getenv(strbuf))
                    return;
            putenv(strbuf);
        #endif
        */
    #endif
}

String System::getErrorString( const long lErrorCode)
{
    String result = "";

    #ifdef _BOS_ON_WIN32_
        LPVOID lpMessageBuffer = 0;
        FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, lErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       (LPTSTR) &lpMessageBuffer, 0, NULL );
        result = (char*)lpMessageBuffer;
        LocalFree( (HLOCAL)lpMessageBuffer );
        // Strip trailing .crlf if present
        if ( result.size() > 2 && (result[result.size()-3] == '.') )
	        result.erase( result.size() - 3 );
	#else
        result = String( strerror(lErrorCode) );
    #endif

    return result;
}



String System::expandEnvironmentStrings( const String& Name )
{
	//String sResult = "";

    #ifdef _BOS_ON_WIN32_
        char acBuffer[2048];
        if ( ExpandEnvironmentStrings( sString.c_str(), acBuffer, sizeof(acBuffer) ) )
            sResult = acBuffer;
        else
            sResult = sString;
	#else

        String sResult = expand_environment_variables( Name );
        //String sResult = "/etc/nginx/html";

	#endif

	return sResult;
}

String System::getEnvironmentVariable( const String& Name )
{
    #ifdef _BOS_ON_WIN32_
        String oldValue = "";
        Char newVar[MAX_VAR];
        DWORD dwSuccess;
        // lpszOldValue gets current value of "varname", or NULL if "varname"
        // environment variable does not exist.
        dwSuccess = GetEnvironmentVariable( Name.c_str(), newVar, MAX_VAR );
        if ( dwSuccess > 0 )
            oldValue = newVar;
        return oldValue;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_

        String var = expand_environment_variables( Name );

        return var;

    #endif
}


std::string expand_environment_variables( const std::string& s ) {
    if( s.find( "${" ) == std::string::npos ) return s;

    std::string pre  = s.substr( 0, s.find( "${" ) );
    std::string post = s.substr( s.find( "${" ) + 2 );

    if( post.find( '}' ) == std::string::npos ) return s;

    std::string variable = post.substr( 0, post.find( '}' ) );
    std::string value    = "";

    post = post.substr( post.find( '}' ) + 1 );

    //if( getenv( variable.c_str() ) != NULL ) value = std::string( getenv( variable.c_str() ) );
    char *temp = getenv( variable.c_str() ) ;
    if( temp != NULL )
       value = std::string( temp );

    //cout << temp << endl ;

    return expand_environment_variables( pre + value + post );
    //return expand_environment_variables( pre + "/etc/nginx/html" + post );

}

