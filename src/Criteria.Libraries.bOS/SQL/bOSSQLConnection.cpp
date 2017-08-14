#include "CommonDefines.h"

#include "bOSSQLConnection.h"
using namespace bOS::SQL;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

SQLConnection::SQLConnection()
{
	bAutoCommit = true;
	iTimeout=0;
}

SQLConnection::~SQLConnection()
{
	;
}

void SQLConnection::setAutoCommit(bool bCommit)
{
	bAutoCommit=bCommit;
}

bool SQLConnection::isAutoCommit()
{
	return bAutoCommit;
}

void SQLConnection::setTimeout(int _timeout)
{
	iTimeout = _timeout;
}

int SQLConnection::getTimeout()
{
	return iTimeout;
}
