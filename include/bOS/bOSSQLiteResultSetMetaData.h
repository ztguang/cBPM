#ifndef _BOS_SQLITE3_RESULTSET_METADATA_H_
#define _BOS_SQLITE3_RESULTSET_METADATA_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetMetaData.h"

namespace bOS
{
	namespace SQL
	{
		namespace SQLite3
		{
			class BOS_API SQLiteResultSetMetaData : public bOS::SQL::ResultSetMetaData
			{
			public:
				SQLiteResultSetMetaData();
				~SQLiteResultSetMetaData();

				void typeToString(int type,char* ret);
				void nullableToString(int nullable,char* ret);
			};
		}
	}
}

#endif //_BOS_SQLITE3_RESULTSET_METADATA_H_