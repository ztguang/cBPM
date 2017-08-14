#ifndef __BOS_MYSQL_CONNECTION_H__
#define __BOS_MYSQL_CONNECTION_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLConnection.h"

#include "bOSmySQLConnectionData.h"

//#include <windows.h>      //ztg delete
#include "mySQL/mysql.h"

namespace bOS
{
    namespace SQL
    {
		namespace mySQL
		{
			class BOS_API mySQLConnection : public bOS::SQL::SQLConnection
			{
				public:

					bool isConnected();
					long execute( const char* acSql );
					long executePrepare( SQLCommands& );
					ResultSet* executeQuery( const char* acSql );
					ResultSet* executeQuery(const char* acSql,int iCursorType,bool bScrollable);

					unsigned long getAutoIncrement();

					//Transaction Manager
					void beginTrans();
					void commit();
					void rollback();
					bool supportTransaction();

				//protected:     //ztg delete

				//private:      //ztg delete

					mySQLConnection(mySQLConnectionData* data);
					~mySQLConnection();

					void open();
					void close();

					/**************************************/
					bool bConnected;
					String sHost;
					int iPort;
					String sDB;
					String sUser;
					String sPwd;
					/**************************************/


					/************************************/
					MYSQL mySql;
					MYSQL* connection;

					friend class SQLConnectionManager;
			};
		}
    }
};

#endif //__BOS_MYSQL_CONNECTION_H__
