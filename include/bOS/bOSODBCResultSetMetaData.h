#ifndef _BOS_ODBC_RESULTSET_METADATA_H_
#define _BOS_ODBC_RESULTSET_METADATA_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetMetaData.h"

namespace bOS
{
	namespace SQL
	{
		namespace ODBC
		{
			class BOS_API ODBCResultSetMetaData : public bOS::SQL::ResultSetMetaData
			{
			public:
				ODBCResultSetMetaData();
				~ODBCResultSetMetaData();

				void typeToString(int type,char* ret);
				void nullableToString(int nullable,char* ret);
			};
		}
	}
}

#endif //_BOS_ODBC_RESULTSET_METADATA_H_