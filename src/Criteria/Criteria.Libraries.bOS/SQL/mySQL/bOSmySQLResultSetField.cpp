#include "CommonDefines.h"

#include "bOSmySQLResultSetField.h"
using namespace bOS::SQL::mySQL;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

mySQLResultSetField::mySQLResultSetField(const char* acName) :
	ResultSetField(acName, "")
{
	iType = VARCHAR;
}


mySQLResultSetField::mySQLResultSetField(const char* acName, String& sValue) :
	ResultSetField(acName, sValue)
{
	iType = VARCHAR;
}

mySQLResultSetField::mySQLResultSetField(const char* acName, const char* acValue) :
	ResultSetField(acName, acValue)
{
	iType = VARCHAR;
}

mySQLResultSetField::mySQLResultSetField(const char* acName, long lValue) :
	ResultSetField(acName, lValue)
{
	iType = NUMERIC;
}

mySQLResultSetField::mySQLResultSetField(const char* acName, int iValue) :
	ResultSetField(acName, iValue)
{
	iType = INTEGER;
}

/*
ODBCResultSetField::ODBCResultSetField( const ODBCResultSetField& field) :
	ResultSetField(acName, field)
{

}
*/

mySQLResultSetField::~mySQLResultSetField()
{
}