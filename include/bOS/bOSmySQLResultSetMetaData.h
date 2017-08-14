#ifndef _BOS_MYSQL_RESULTSET_METADATA_H_
#define _BOS_MYSQL_RESULTSET_METADATA_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetMetaData.h"

namespace bOS
{
	namespace SQL
	{
		namespace mySQL
		{
			class BOS_API mySQLResultSetMetaData : public bOS::SQL::ResultSetMetaData
			{
			public:
				mySQLResultSetMetaData();
				~mySQLResultSetMetaData();

				void typeToString(int type,char* ret);
				void nullableToString(int nullable,char* ret);
			};
		}
	}
}

#endif //_BOS_MYSQL_RESULTSET_METADATA_H_