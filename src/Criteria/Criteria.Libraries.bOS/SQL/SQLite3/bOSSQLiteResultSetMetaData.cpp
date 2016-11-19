#ifdef _USE_SQLITE3_

#include "CommonDefines.h"

#include "bOSSQLiteResultSetMetaData.h"
using namespace bOS::SQL::SQLite3;

SQLiteResultSetMetaData::SQLiteResultSetMetaData()
{
}

SQLiteResultSetMetaData::~SQLiteResultSetMetaData()
{
}

void SQLiteResultSetMetaData::typeToString(int type,char* ret)
{
	strcpy(ret,"UNKNOWN");
}

void SQLiteResultSetMetaData::nullableToString(int nullable,char* ret)
{
	try
	{
		switch(nullable)
		{
		case 1:
			strcpy(ret,"NULL");
			break;
		case 0:
			strcpy(ret,"NOT NULL");
			break;
		default:
			strcpy(ret,"UNKNOWN");
		}
	}
	catch(...)
	{
		strcpy(ret,"-1");
	}
}

#endif