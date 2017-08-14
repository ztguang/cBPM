#include "CommonDefines.h"

#include "bOSSQLConnectionManager.h"
#include "bOSSQLException.h"
using namespace bOS::SQL;

#include "bOSmySQLConnection.h"
#include "bOSmySQLConnectionData.h"
using namespace bOS::SQL::mySQL;

#ifdef _USE_SQLITE3_
#include "bOSSQLiteConnection.h"
#include "bOSSQLiteConnectionData.h"
using namespace bOS::SQL::SQLite3;
#endif

#include "bOSThread.h"
using namespace bOS::Core;

SQLConnectionManager::SQLConnectionManager()
{
    iMin=1;
    iMax=1;

	connectionData= NULL;
}

SQLConnectionManager::~SQLConnectionManager()
{
	unsigned int uiSize = vPool.size();
	for ( unsigned int i = 0; i < uiSize; i++ )
	{
		delete vPool.at(i);
	}

	if ( connectionData != NULL )
		delete connectionData;
}

void SQLConnectionManager::init(DataBaseType dbt)
{
    iDBType = dbt;
}

SQLConnection* SQLConnectionManager::getNewConnection()
{
	assert(connectionData != NULL);

	SQLConnection* connection = NULL;

	switch ( iDBType )
	{
	case MYSQL:
		connection  = new mySQLConnection((mySQLConnectionData*)connectionData);
		break;
#ifdef _USE_SQLITE3_
	case SQLITE3:
		connection  = new SQLiteConnection((SQLiteConnectionData*)connectionData);
		break;
#endif

	}

	return connection;
}

void SQLConnectionManager::createPool( SQLConnectionData* data, unsigned int _Min, unsigned int _Max)
{
	iMin = _Min;
	iMax = _Max;

	switch ( iDBType )
	{
	case MYSQL:
		connectionData = new mySQLConnectionData();
		break;
#ifdef _USE_SQLITE3_
	case SQLITE3:
		connectionData = new SQLiteConnectionData();
		break;
#endif
	}

	connectionData->init (data);

    vPool.clear();
    for ( unsigned int i = 0; i < iMin; i++ )
    {
		SQLConnection* connection = this->getNewConnection();

		try
		{
			connection->open();
		}
		catch (SQLException& )
		{
			throw;
		}

		SQLConnectionPoolEntry*	entry = new SQLConnectionPoolEntry (connection);
        vPool.push_back( entry );
    }
}

SQLConnection* SQLConnectionManager::get()
{
    SQLConnection* connection = NULL;

    Mutex::Lock lock(mutex);
    
    unsigned int uiPoolSize = vPool.size();
    if ( uiPoolSize == 0 )
    {
		throw SQLException( SQL_NOT_CONNECTED );
	}

    for ( unsigned int i=0; i <uiPoolSize; i++)
    {
        SQLConnectionPoolEntry* entry = vPool.at(i);
        if ( entry->isFree() )
        {
            entry->setBusy();
            connection = entry->getConnection();
            break;
        }
    }
        
    if ( connection == NULL )
    {
        if ( uiPoolSize < iMax )
        {
			connection = this->getNewConnection();
			connection->open();

			SQLConnectionPoolEntry*	entry = new SQLConnectionPoolEntry (connection);
			entry->setBusy();
			vPool.push_back( entry );
		}
    }

	if ( connection != NULL )
		connection->setAutoCommit (true);
	return connection;
}

SQLConnection* SQLConnectionManager::get(unsigned int uiTimes, unsigned int uiMilliSeconds)
{
    SQLConnection* connection = NULL;

	if ( uiTimes == 0  )
	{
		do {
			connection = this->get();
			Thread::sleep( uiMilliSeconds );

		} while ( connection == NULL);

	} else {

		for ( unsigned int i = 1; i <= uiTimes; i++ )
		{
			connection = this->get();
			if ( connection != NULL )
			{
				break;
			}

			Thread::sleep( uiMilliSeconds );
		}
	}

    return connection;
}

void SQLConnectionManager::release( SQLConnection* connection )
{
    Mutex::Lock lock(mutex);
    
    unsigned int uiPoolSize = vPool.size();

    if ( uiPoolSize == 0 )
    {
		throw SQLException( SQL_NOT_CONNECTED );
	}

	SQLConnectionPool::iterator i = vPool.begin();
	for ( ; i!=vPool.end();i++)
    {
        SQLConnectionPoolEntry* entry = (*i);
        if ( connection == entry->getConnection() )
        {
			if ( entry->isFree() ) 
			{
				throw SQLException( SQL_NOT_CONNECTED );
			}

            entry->setFree();

            if ( uiPoolSize > iMin )
            {
                delete entry;
				vPool.erase( i );
                break;
            }
        }
    }
}
