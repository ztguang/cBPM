#ifndef __BOS_ODBC_RESULTSET_H__
#define __BOS_ODBC_RESULTSET_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSet.h"
#include "bOSResultSetMetaData.h"

#include "bOSODBCResultSetMetaData.h"

#include <windows.h>
#include <SQL.h>
#include <sqlext.h>

namespace bOS
{
    namespace SQL
    {
		namespace ODBC
		{
			class BOS_API ODBCResultSet : public bOS::SQL::ResultSet
			{
			public:

				bool eof();
				bool moveFirst();
				bool moveLast();
				bool moveNext();
				bool movePrevious();
				long getRecordCount();
				void close();

				bool bind(int col_no,char* buff,int buff_len);
				
				ResultSetMetaData* getMetaData();
				ResultSetRecord* getRecord();


			private:

				SQLHSTMT*		m_hStmt;	
				SQLUINTEGER		m_lNumRows;
				SQLUSMALLINT	m_nRowStatusArray[10]; 

				// Error handling 
				SQLSMALLINT		m_iRec;
				SQLTCHAR		m_cState[6];
				SQLTCHAR		m_cMsg[SQL_MAX_MESSAGE_LENGTH];
				SQLINTEGER		m_nErr;
				SQLSMALLINT		m_nMsg;

				ODBCResultSet(SQLHSTMT *stmt);
				~ODBCResultSet();

				ODBCResultSetMetaData mtdt_bind;
				ResultSetRecord record_bind;
				void handleError();

				friend class ODBCConnection;
			};
		}
	}
}

#endif //__BOS_ODBC_RESULTSET_H__
