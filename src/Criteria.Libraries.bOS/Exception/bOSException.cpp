#include "CommonDefines.h"

#include "bOS.h"
#include "bOSException.h"
using namespace bOS::Exception;

BaseException::BaseException()
{
    sMessage = "";
}

BaseException::BaseException( const String & message )
{
    sMessage = message;
}

BaseException::BaseException( const String & message, const int lineNumber )
{
    sMessage = message;
    char txt[256];
    sprintf( txt, "\nError at line number %d", lineNumber );
    sMessage += txt;
}

BaseException::~BaseException()
{
}

String BaseException::getMessage()
{   
    return sMessage;
}

