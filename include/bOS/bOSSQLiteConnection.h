#ifndef __BOS_SQLITE3_CONNECTION_H__
#define __BOS_SQLITE3_CONNECTION_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLConnection.h"

#include "bOSSQLiteConnectionData.h"

#include "CppSQLite3.h"

namespace bOS
{
    namespace SQL
    {
		namespace SQLite3
		{
			class BOS_API SQLiteConnection : public bOS::SQL::SQLConnection
			{
				public:

					bool isConnected();
					long execute( const char* acSql );
					long executePrepare( SQLCommands& ) {return 0;}
					ResultSet* executeQuery( const char* acSql );
					ResultSet* executeQuery(const char* acSql,int iCursorType,bool bScrollable);

					unsigned long getAutoIncrement() { return 0;}

					//Transaction Manager
					void beginTrans();
					void commit();
					void rollback();
					bool supportTransaction();

				//protected:      //ztg delete

				//private:      //ztg delete

					SQLiteConnection(SQLiteConnectionData* data);
					~SQLiteConnection();

					void open();
					void close();

					/**************************************/
					bool bConnected;
					String	sDB;
					/**************************************/


					CppSQLite3DB sqlliteDB;
					/************************************/

					friend class SQLConnectionManager;
			};
		}
    }
};

#endif //__BOS_SQLITE3_CONNECTION_H__
