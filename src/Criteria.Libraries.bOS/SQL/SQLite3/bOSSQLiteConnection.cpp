#ifdef _USE_SQLITE3_

#include "CommonDefines.h"

#include "bOSSQLException.h"
using namespace bOS::SQL;

#include "bOSSQLiteConnection.h"
#include "bOSSQLiteResultSet.h"
using namespace bOS::SQL::SQLite3;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

SQLiteConnection::SQLiteConnection(SQLiteConnectionData* data) : SQLConnection()
{
	sDB = data->sPath;
	sDB += SLASH;
	sDB +=data->sDB;

	this->iTimeout = 10;
	this->bConnected = false;
}

SQLiteConnection::~SQLiteConnection()
{
    this->close();
}

bool SQLiteConnection::isConnected()
{
	return bConnected;
}

long SQLiteConnection::execute( const char* acSql)
{
	if(!this->bConnected)
	{
		throw SQLException("Call Open() before Execute()");
	}

	long lRows=0;

	try
	{
		lRows = sqlliteDB.execDML(acSql);
	}
	catch (CppSQLite3Exception& e)
	{
		cout << e.errorCode() << ":" << e.errorMessage() << endl;
		throw SQLException( e.errorMessage());
	}


	return lRows;
}

ResultSet* SQLiteConnection::executeQuery( const char* acSql )
{
	if(!this->bConnected)
	{
		throw SQLException("Call Open() before Execute()");
	}

	CppSQLite3Query query;
	try
	{
		query = sqlliteDB.execQuery(acSql);
	}
	catch (CppSQLite3Exception& e)
	{
		cout << e.errorCode() << ":" << e.errorMessage() << endl;
		throw SQLException( e.errorMessage());
	}


	//?necessario per eseguire altre query
	SQLiteResultSet* rslt = new SQLiteResultSet(query);
	return rslt;
}

ResultSet* SQLiteConnection::executeQuery(const char* acSql,int iCursorType,bool bScrollable)
{
	//TODO: Scrollable cursor to manage.
	return this->executeQuery(acSql);
}

void SQLiteConnection::beginTrans()
{
	try
	{
		sqlliteDB.execDML("begin transaction;");
	}
	catch (CppSQLite3Exception& e)
	{
		cout << e.errorCode() << ":" << e.errorMessage() << endl;
		throw SQLException( e.errorMessage());
	}
}

void SQLiteConnection::commit()
{
	try
	{
		sqlliteDB.execDML("commit transaction;");
	}
	catch (CppSQLite3Exception& e)
	{
		cout << e.errorCode() << ":" << e.errorMessage() << endl;
		throw SQLException( e.errorMessage());
	}
}

void SQLiteConnection::rollback()
{
	try
	{
		sqlliteDB.execDML("rollback transaction;");
	}
	catch (CppSQLite3Exception& e)
	{
		cout << e.errorCode() << ":" << e.errorMessage() << endl;
		throw SQLException( e.errorMessage());
	}
}

bool SQLiteConnection::supportTransaction()
{
	return true;
}

void SQLiteConnection::open()
{
	try
	{
		sqlliteDB.open(sDB.c_str());
	}
	catch (CppSQLite3Exception& e)
	{
		cout << e.errorCode() << ":" << e.errorMessage() << endl;
		throw SQLException( e.errorMessage());
	}

	bConnected = true;
}

void SQLiteConnection::close()
{
	if (bConnected) 
	{
		try
		{
			sqlliteDB.close();
		}
		catch (CppSQLite3Exception& e)
		{
			cout << e.errorCode() << ":" << e.errorMessage() << endl;
		}
	}

	bConnected  = false;
}

#endif