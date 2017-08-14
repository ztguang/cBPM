#ifndef __BOS_SQL_MYSQL_CONNECTION_DATA_H__
#define __BOS_SQL_MYSQL_CONNECTION_DATA_H__

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLConnectionData.h"

namespace bOS
{
	namespace SQL
	{
		namespace mySQL
		{
			class BOS_API mySQLConnectionData : public bOS::SQL::SQLConnectionData
			{
			public:
				
				mySQLConnectionData();
				~mySQLConnectionData();

				void init(SQLConnectionData*);

				String sHost;
				unsigned int iPort;
				String sDB;
				String sUser;
				String sPassword;
			};
		}
	}
}


#endif //__BOS_SQL_MYSQL_CONNECTION_DATA_H__