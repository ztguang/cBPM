#include "CommonDefines.h"

#include "bOSSQLSmartConnection.h"
#include "bOSSQLConnectionManager.h"
#include "bOSSQLConnection.h"
using namespace bOS::SQL;

SQLSmartConnection::SQLSmartConnection()
{
	manager = NULL;
	connection = NULL;

	bConnectionOwner = false;
}

SQLSmartConnection::SQLSmartConnection(SQLConnectionManager* _manager, SQLConnection* _connection)
{
	assert(_manager != NULL);
	assert(_connection != NULL );

	manager = _manager;
	connection = _connection;

	bConnectionOwner = true;
}

SQLSmartConnection::~SQLSmartConnection()
{
	if ( connection != NULL )
	{
		try
		{
			manager->release(connection);
		}
		catch ( SQLException&)
		{
			//TODO
			//TRC_TRACES(2, "impossible to free connection.Err[" << sqlErr << "]")
		}
	}
}

void SQLSmartConnection::init(SQLConnectionManager* _manager, SQLConnection* _connection)
{
	assert(manager == NULL);
	assert(connection == NULL);
	assert(_manager != NULL);
	assert(_connection != NULL );

	manager = _manager;
	connection = _connection;

	bConnectionOwner = true;
}