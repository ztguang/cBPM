#include "CommonDefines.h"

#include "bOSmySQLResultSetMetaData.h"
using namespace bOS::SQL::mySQL;

//#include <windows.h>      //ztg delete
#include "mySQL/mysql.h"

mySQLResultSetMetaData::mySQLResultSetMetaData()
{
}

mySQLResultSetMetaData::~mySQLResultSetMetaData()
{
}

void mySQLResultSetMetaData::typeToString(int type,char* ret)
{
	try {
		switch(type)
		{
		case FIELD_TYPE_TINY:
			strcpy(ret,"TINYINT");
			break;
		case FIELD_TYPE_SHORT:
			strcpy(ret,"SMALLINT");
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

void mySQLResultSetMetaData::nullableToString(int nullable,char* ret)
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

