#ifndef __BOS_SQL_SQLITE3_CONNECTION_DATA_H__
#define __BOS_SQL_SQLITE3_CONNECTION_DATA_H__

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLConnectionData.h"

namespace bOS
{
	namespace SQL
	{
		namespace SQLite3
		{
			class BOS_API SQLiteConnectionData : public bOS::SQL::SQLConnectionData
			{
			public:
				
				SQLiteConnectionData();
				~SQLiteConnectionData();

				void init(SQLConnectionData*);

				String sDB;
				String sPath;
			};
		}
	}
}


#endif //__BOS_SQL_SQLITE3_CONNECTION_DATA_H__