#include "CommonDefines.h"

#include "bOSODBCResultSetField.h"
using namespace bOS::SQL::ODBC;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

ODBCResultSetField::ODBCResultSetField(const char* acName) :
	ResultSetField(acName, "")
{
	iType = VARCHAR;
}


ODBCResultSetField::ODBCResultSetField(const char* acName, String& sValue) :
	ResultSetField(acName, sValue)
{
	iType = VARCHAR;
}

ODBCResultSetField::ODBCResultSetField(const char* acName, const char* acValue) :
	ResultSetField(acName, acValue)
{
	iType = VARCHAR;
}

ODBCResultSetField::ODBCResultSetField(const char* acName, long lValue) :
	ResultSetField(acName, lValue)
{
	iType = NUMERIC;
}

ODBCResultSetField::ODBCResultSetField(const char* acName, int iValue) :
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

ODBCResultSetField::~ODBCResultSetField()
{
}