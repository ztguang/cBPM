#ifndef __BOS_ODBC_CONNECTION_H__
#define __BOS_ODBC_CONNECTION_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLConnection.h"

#include "bOSODBCConnectionData.h"

#include <windows.h>
#include <SQL.h>
#include <sqlext.h>

namespace bOS
{
    namespace SQL
    {
		namespace ODBC
		{
			class BOS_API ODBCConnection : public bOS::SQL::SQLConnection
			{
				public:

					bool isConnected();
					long execute( const char* acSql );
					long executePrepare( SQLCommands& ) {return 0;}
					ResultSet* executeQuery( const char* acSql );
					ResultSet* executeQuery(const char* acSql,int iCursorType,bool bScrollable);

					long getAutoIncrement() { return 0;}

					//Transaction Manager
					void beginTrans();
					void commit();
					void rollback();
					bool supportTransaction();

					/*************************************/
					// cursor types
					static int db_dynamic;
					static int db_static;
					static int db_keysetdriven;
					static int db_forwardonly;
					/*************************************/

				protected:

				private:

					ODBCConnection(ODBCConnectionData* data);
					~ODBCConnection();

					void open();
					void close();

					/**************************************/
					bool bConnected;
					String sUser;
					String sPwd;
					String sDsn;
					/**************************************/


					/************************************/
					SQLHENV m_hEnv; // environment handle
					SQLHDBC m_hDbc; // database handle
					SQLHSTMT m_hStmt; // statement handle

					// Error handling 
					SQLSMALLINT m_iRec;
					SQLTCHAR m_cState[6];
					SQLTCHAR m_cMsg[SQL_MAX_MESSAGE_LENGTH];
					SQLINTEGER m_nErr;
					SQLSMALLINT m_nMsg;
					/************************************/

					void handleError(const char* type);


					friend class SQLConnectionManager;
			};
		}
    }
};

#endif //__BOS_ODBC_CONNECTION_H__
