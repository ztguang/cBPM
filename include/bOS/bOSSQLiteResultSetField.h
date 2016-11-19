#ifndef _BOS_SQLITE3_RESULTSET_FIELD_H_
#define _BOS_SQLITE3_RESULTSET_FIELD_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetField.h"

namespace bOS
{
	namespace SQL
	{
		namespace SQLite3
		{
			class BOS_API SQLiteResultSetField : public bOS::SQL::ResultSetField
			{
			public:

				SQLiteResultSetField(const char* acName);
				SQLiteResultSetField(const char* acName, String& acValue);
				SQLiteResultSetField(const char* acName, const char* acValue);
				SQLiteResultSetField(const char* acName, long lValue);
				SQLiteResultSetField(const char* acName, int iValue);
				//ODBCResultSetField( const ODBCResultSetField&);
				~SQLiteResultSetField();
			};
		}
	}
}

#endif //_BOS_SQLITE3_RESULTSET_FIELD_H_ 
