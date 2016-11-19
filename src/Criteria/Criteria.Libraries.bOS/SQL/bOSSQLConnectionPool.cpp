#include "CommonDefines.h"

#include "bOSSQLConnectionPool.h"
#include "bOSSQLException.h"
using namespace bOS::SQL;

SQLConnectionPoolEntry::SQLConnectionPoolEntry(SQLConnection* _connection)
{
	assert(_connection != NULL );
	connection = _connection;
	bFree = true;
}

SQLConnectionPoolEntry::~SQLConnectionPoolEntry()
{
	if ( connection != NULL )
	{
		if ( connection->isConnected() )
		{
			connection->close();
		}

		delete connection;
	}
}

bool SQLConnectionPoolEntry::isFree()
{
	return bFree;
}

void SQLConnectionPoolEntry::setBusy()
{
	bFree = false;
}

void SQLConnectionPoolEntry::setFree()
{
	bFree = true;
}