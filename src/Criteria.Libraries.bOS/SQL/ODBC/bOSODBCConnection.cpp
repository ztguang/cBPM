#include "CommonDefines.h"

#include "bOSSqlException.h"
using namespace bOS::SQL;

#include "bOSODBCConnection.h"
#include "bOSODBCResultSet.h"
using namespace bOS::SQL::ODBC;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

/*********************************************************/
int ODBCConnection::db_dynamic = SQL_CURSOR_DYNAMIC;
int ODBCConnection::db_keysetdriven = SQL_CURSOR_KEYSET_DRIVEN;
int ODBCConnection::db_static = SQL_CURSOR_STATIC;
int ODBCConnection::db_forwardonly = SQL_CURSOR_FORWARD_ONLY;
/*********************************************************/

ODBCConnection::ODBCConnection(ODBCConnectionData* data) : SQLConnection()
{
	this->m_hEnv = NULL;
	this->m_hDbc = NULL;
	this->m_hStmt = NULL;
	this->iTimeout = 10;
	this->bConnected = false;

	this->m_iRec = 1;

	sUser = data->sUser;
	sPwd = data->sPassword;
	sDsn = data->sDsn;
}

ODBCConnection::~ODBCConnection()
{
    this->close();
}

bool ODBCConnection::isConnected()
{
	return bConnected;
}

long ODBCConnection::execute( const char* acSql)
{
	if(!this->bConnected)
	{
		throw SQLException("Call Open() before Execute()");
	}

	SQLRETURN ret;
	try
	{
		SQLFreeStmt(this->m_hStmt,SQL_CLOSE);
		ret = SQLAllocStmt(this->m_hDbc, &this->m_hStmt);
	}
	catch(...)
	{
		handleError("STMT");
	}
	try
	{
		ret = SQLPrepare(this->m_hStmt,(unsigned char*)acSql,SQL_NTS);
	}
	catch(...)
	{
		handleError("STMT");
	}

	if(ret == SQL_ERROR)
	{
		handleError("STMT");
	}

	try
	{
		ret = SQLExecute(this->m_hStmt);
	}
	catch(...)
	{
		handleError("STMT");
	}

	if(ret == SQL_ERROR || ret < 0)
	{
		handleError("STMT");
	}

	long count = 0;

	try
	{
		ret = SQLRowCount(this->m_hStmt,&count);
	}
	catch(...)
	{
		handleError("STMT");
	}

	if ( bAutoCommit )
	{
		this->commit();
	}
	
	return count;
}

ResultSet* ODBCConnection::executeQuery( const char* acSql )
{

	if(!this->bConnected)
	{
		throw SQLException("Call Open() before Execute()");
	}

	SQLRETURN ret;
	try
	{
		SQLFreeStmt(this->m_hStmt,SQL_CLOSE);
		ret = SQLAllocStmt(this->m_hDbc, &this->m_hStmt);
	}
	catch(...)
	{
		handleError("STMT");
	}

	if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0)
	{
		handleError("DBC");
	}

	try
	{
		ret = SQLSetStmtAttr(this->m_hStmt, SQL_ATTR_CURSOR_TYPE,
				(SQLPOINTER)SQL_CURSOR_DYNAMIC,SQL_IS_INTEGER);

	}
	catch(...)
	{
		handleError("STMT");
	}

	if(ret < 0)
	{
		handleError("STMT");
	}
		
	try
	{
		ret = SQLExecDirect(this->m_hStmt,(SQLTCHAR*)acSql,strlen(acSql));
	}
	catch(...)
	{
		handleError("STMT");
	}

	if(ret == SQL_ERROR)
	{
		handleError("STMT");
	}
	
	ODBCResultSet* rslt = new ODBCResultSet(&this->m_hStmt);
	return rslt;
}

ResultSet* ODBCConnection::executeQuery(const char* acSql,int iCursorType,bool bScrollable)
{
	if(!this->bConnected)
	{
		throw SQLException("Call Open() before Execute()");
	}

	if(iCursorType != ODBCConnection::db_dynamic &&
			iCursorType != ODBCConnection::db_forwardonly &&
			iCursorType != ODBCConnection::db_keysetdriven &&
			iCursorType != ODBCConnection::db_static)
	{
		throw SQLException("Invalid cursor type");
	}

	SQLRETURN ret;
	try
	{
		
		SQLFreeStmt(this->m_hStmt,SQL_CLOSE);
		ret = SQLAllocStmt(this->m_hDbc, &this->m_hStmt);
	}
	catch(...)
	{
		handleError("STMT");
	}

	if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0)
	{
		handleError("DBC");
	}

	try
	{
		ret = SQLSetStmtAttr(this->m_hStmt, SQL_ATTR_CURSOR_TYPE,
						(SQLPOINTER)iCursorType,SQL_IS_INTEGER);
	}
	catch(...)
	{
		handleError("STMT");
	}

	if(ret < 0)
	{
		handleError("STMT");
	}

	if(bScrollable)
	{
		try
		{
			ret = SQLSetStmtAttr(this->m_hStmt, SQL_ATTR_CURSOR_SCROLLABLE,
                    (SQLPOINTER)SQL_SCROLLABLE,
                    SQL_IS_INTEGER);
		}
		catch(...)
		{
			handleError("STMT");
		}
		
		if(ret < 0)
		{
			handleError("STMT");
		}

	}
		
	try
	{
		ret = SQLExecDirect(this->m_hStmt,(SQLTCHAR*)acSql,strlen(acSql));
	}
	catch(...)
	{
		handleError("STMT");
	}

	if(ret == SQL_ERROR)
	{
		handleError("STMT");
	}
	
	ODBCResultSet* rslt = new ODBCResultSet(&this->m_hStmt);

	return rslt;
}

void ODBCConnection::beginTrans()
{
	throw SQLException("Not Supported");
}

void ODBCConnection::commit()
{
	SQLRETURN ret = SQLEndTran(SQL_HANDLE_DBC,this->m_hDbc,SQL_COMMIT);
	if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE)
	{
		throw SQLException("Commit failed");
	}
}

void ODBCConnection::rollback()
{
	SQLRETURN ret = SQLEndTran(SQL_HANDLE_DBC,this->m_hDbc,SQL_ROLLBACK);
	if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE)
	{
		throw SQLException("Rollback failed");
	}
}

bool ODBCConnection::supportTransaction()
{
	return false;
}

void ODBCConnection::open()
{
	SQLRETURN ret = 0;

	try
	{
		ret = SQLAllocEnv(&this->m_hEnv);
	}
	catch(...)
	{
		handleError("ENV");
	}

	if (ret == SQL_ERROR)
	{
		handleError("ENV");
	}
	else if (ret == SQL_INVALID_HANDLE || ret < 0) 
	{
		handleError("ENV");
	}

	try
	{
		// allocates memory for ODBC
		ret = SQLAllocConnect(this->m_hEnv, &this->m_hDbc);
	}
	catch(...)
	{
		handleError("ENV");
	}

	if(ret == SQL_ERROR)
	{
		handleError("ENV");
	}
	else if(ret == SQL_INVALID_HANDLE || ret < 0)
	{
		handleError("ENV");
	}

	try
	{
		// connects to the ODBC driver
		ret = SQLConnect(this->m_hDbc,
					(SQLCHAR*)sDsn.c_str(),sDsn.size(),
					(SQLCHAR*)sUser.c_str(),sUser.size(),
					(SQLCHAR*)sPwd.size(),sPwd.size());
	}
	catch(...)
	{
		handleError("DBC");
	}

	if ( ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0)
	{
		handleError("DBC");
	}

	try
	{
		ret = SQLAllocStmt(this->m_hDbc, &this->m_hStmt);
	}
	catch(...)
	{
		handleError("DBC");
	}
	if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0)
	{
		handleError("DBC");
	}
		
	this->bConnected = true;
}

void ODBCConnection::close()
{
	if (bConnected) 
	{
		SQLFreeStmt(this->m_hStmt,SQL_CLOSE);
		SQLDisconnect(this->m_hDbc);
		SQLFreeConnect(this->m_hDbc);
		SQLFreeEnv(this->m_hEnv);

		this->bConnected = false;
	}
}

void ODBCConnection::handleError(const char* type)
{
	try {
		if(strcmp(type,"STMT") == 0)
		{
			SQLGetDiagRec(SQL_HANDLE_STMT,this->m_hStmt,this->m_iRec,
			this->m_cState,&this->m_nErr,this->m_cMsg,
			sizeof(m_cMsg),&this->m_nMsg);		
		}
		else if(strcmp(type,"ENV") == 0)
		{
			SQLGetDiagRec(SQL_HANDLE_ENV,this->m_hEnv,this->m_iRec,
			this->m_cState,&this->m_nErr,this->m_cMsg,
			sizeof(m_cMsg),&this->m_nMsg);		
		}
		else if(strcmp(type,"DBC") == 0)
		{
			SQLGetDiagRec(SQL_HANDLE_DBC,this->m_hDbc,this->m_iRec,
			this->m_cState,&this->m_nErr,this->m_cMsg,
			sizeof(m_cMsg),&this->m_nMsg);		
		}
	}catch(...)
	{
		throw SQLException("Database error",0);
	}

	throw SQLException((char*)this->m_cMsg);
}



