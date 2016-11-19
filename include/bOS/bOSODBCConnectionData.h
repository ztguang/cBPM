#ifndef __BOS_SQL_ODBC_CONNECTION_DATA_H__
#define __BOS_SQL_ODBC_CONNECTION_DATA_H__

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLConnectionData.h"

namespace bOS
{
	namespace SQL
	{
		namespace ODBC
		{
			class BOS_API ODBCConnectionData : public bOS::SQL::SQLConnectionData
			{
			public:
				
				ODBCConnectionData();
				~ODBCConnectionData();

				void init(SQLConnectionData*);

				String sUser;
				String sPassword;
				String sDsn;
			};
		}
	}
}


#endif //__BOS_SQL_ODBC_CONNECTION_DATA_H__