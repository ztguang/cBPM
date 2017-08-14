#include "CommonDefines.h"

#include "bOSODBCResultSetMetaData.h"
using namespace bOS::SQL::ODBC;

#include <windows.h>
#include <SQL.h>
#include <sqlext.h>

ODBCResultSetMetaData::ODBCResultSetMetaData()
{
}

ODBCResultSetMetaData::~ODBCResultSetMetaData()
{
}

void ODBCResultSetMetaData::typeToString(int type,char* ret)
{
	try {
		switch(type)
		{
		case SQL_CHAR:
			strcpy(ret,"CHAR");
			break;
		case SQL_VARCHAR:
			strcpy(ret,"VARCHAR");
			break;
		case SQL_LONGVARCHAR:
			strcpy(ret,"LONG VARCHAR");
			break;
		case SQL_WCHAR:
			strcpy(ret,"UNICODE CHAR");
			break;
		case SQL_WVARCHAR:
			strcpy(ret,"UNICODE VARCHAR");
			break;
		case SQL_WLONGVARCHAR:
			strcpy(ret,"UNICODE LONG VARCHAR");
			break;
		case SQL_DECIMAL:
			strcpy(ret,"DECIMAL");
			break;
		case SQL_NUMERIC:
			strcpy(ret,"NUMERIC");
			break;
		case SQL_SMALLINT:
			strcpy(ret,"SMALLINT");
			break;
		case SQL_INTEGER:
			strcpy(ret,"INTEGER");
			break;
		case SQL_REAL:
			strcpy(ret,"REAL");
			break;
		case SQL_FLOAT:
			strcpy(ret,"FLOAT");
			break;
		case SQL_DOUBLE:
			strcpy(ret,"DOUBLE");
			break;
		case SQL_BIT:
			strcpy(ret,"BIT");
			break;
		case SQL_TINYINT:
			strcpy(ret,"TINYINT");
			break;
		case SQL_BIGINT:
			strcpy(ret,"BIGINT");
			break;
		case SQL_BINARY:
			strcpy(ret,"BINARY");
			break;
		case SQL_VARBINARY:
			strcpy(ret,"VARBINARY");
			break;
		case SQL_LONGVARBINARY:
			strcpy(ret,"LONG VARBINARY");
			break;
		case SQL_TYPE_DATE:
		case SQL_DATE:
			strcpy(ret,"DATE");
			break;
		case SQL_TYPE_TIME:
		case SQL_TIME:
			strcpy(ret,"TIME");
			break;
		case SQL_TYPE_TIMESTAMP:
		case SQL_TIMESTAMP:
			strcpy(ret,"TIMESTAMP");
			break;
		case SQL_INTERVAL_MONTH:
			strcpy(ret,"INTERVAL MONTH");
			break;
		case SQL_INTERVAL_YEAR:
			strcpy(ret,"INTERVAL YEAR");
			break;
		case SQL_INTERVAL_YEAR_TO_MONTH:
			strcpy(ret,"INTERVAL YEAR TO MONTH");
			break;
		case SQL_INTERVAL_DAY:
			strcpy(ret,"INTERVAL DAY");
			break;
		case SQL_INTERVAL_HOUR:
			strcpy(ret,"INTERVAL HOUR");
			break;
		case SQL_INTERVAL_MINUTE:
			strcpy(ret,"INTERVAL MINUTE");
			break;
		case SQL_INTERVAL_SECOND:
			strcpy(ret,"INTERVAL SECOND");
			break;
		case SQL_INTERVAL_DAY_TO_HOUR:
			strcpy(ret,"INTERVAL DAY TO HOUR");
			break;
		case SQL_INTERVAL_DAY_TO_MINUTE:
			strcpy(ret,"INTERVAL DAY TO MINUTE");
			break;
		case SQL_INTERVAL_DAY_TO_SECOND:
			strcpy(ret,"INTERVAL DAY TO SECOND");
			break;
		case SQL_INTERVAL_HOUR_TO_MINUTE:
			strcpy(ret,"INTERVAL HOUR TO MINUTE");
			break;
		case SQL_INTERVAL_HOUR_TO_SECOND:
			strcpy(ret,"INTERVAL HOUR TO SECOND");
			break;
		case SQL_INTERVAL_MINUTE_TO_SECOND:
			strcpy(ret,"INTERVAL MINUTE TO SECOND");
			break;
		case SQL_GUID:
			strcpy(ret,"GUID");
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

void ODBCResultSetMetaData::nullableToString(int nullable,char* ret)
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

