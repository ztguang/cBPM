#ifdef _USE_SQLITE3_

#include "CommonDefines.h"

#include "bOSSQLiteResultSetField.h"
using namespace bOS::SQL::SQLite3;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

SQLiteResultSetField::SQLiteResultSetField(const char* acName) :
	ResultSetField(acName, "")
{
	iType = VARCHAR;
}


SQLiteResultSetField::SQLiteResultSetField(const char* acName, String& sValue) :
	ResultSetField(acName, sValue)
{
	iType = VARCHAR;
}

SQLiteResultSetField::SQLiteResultSetField(const char* acName, const char* acValue) :
	ResultSetField(acName, acValue)
{
	iType = VARCHAR;
}

SQLiteResultSetField::SQLiteResultSetField(const char* acName, long lValue) :
	ResultSetField(acName, lValue)
{
	iType = NUMERIC;
}

SQLiteResultSetField::SQLiteResultSetField(const char* acName, int iValue) :
	ResultSetField(acName, iValue)
{
	iType = INTEGER;
}

/*
SQLiteResultSetField::SQLiteResultSetField( const ODBCResultSetField& field) :
	ResultSetField(acName, field)
{

}
*/

SQLiteResultSetField::~SQLiteResultSetField()
{
}

#endif