#include "CommonDefines.h"

#include "bOSResultSetMetaData.h"
#include "bOSSqlException.h"
#include "bOSResultSetColumn.h"
using namespace bOS::SQL;

#include "bOSODBCResultSet.h"
#include "bOSODBCResultSetMetaData.h"
#include "bOSODBCResultSetField.h"
using namespace bOS::SQL::ODBC;

ODBCResultSet::ODBCResultSet(SQLHSTMT *stmt) : ResultSet()
{
	this->m_hStmt = stmt;		
	this->m_lNumRows = 0;

	SQLRETURN rc = SQLSetStmtAttr(*this->m_hStmt, SQL_ATTR_ROW_STATUS_PTR, m_nRowStatusArray, 0);
	rc = SQLSetStmtAttr(*this->m_hStmt,SQL_ATTR_ROWS_FETCHED_PTR, &m_lNumRows, 0);

	this->m_iRec = 1;

	try
	{
		SQLSMALLINT column_count = 0;
		SQLRETURN ret = SQLNumResultCols(*this->m_hStmt,&column_count);
		if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE)
		{
			handleError();
		}			
		mtdt_bind.setNumCols(column_count);
		for(int i=1;i<=column_count;i++)
		{
			ResultSetColumn* col = mtdt_bind.addColumn();

			int name_length = 0;
			ret =  SQLDescribeCol(*this->m_hStmt,(SQLSMALLINT)i,
						(SQLCHAR*)(col->title),
						(SQLSMALLINT)sizeof(col->title),
						(SQLSMALLINT*)&name_length,
						(SQLSMALLINT*)&(col->type),
						(SQLUINTEGER*)&(col->size),
						(SQLSMALLINT*)&(col->decim_size),
						(SQLSMALLINT*)&(col->nullable));			
			if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE)
			{
				handleError();
			}
		}		
	}
	catch(...)
	{
		handleError();
	}

	//binding record to ODBC Record.
	{
		int iColSize = mtdt_bind.getColumnCount();
		for(int i=0;i<iColSize;i++)
		{
			ResultSetColumn* col = mtdt_bind.getColumn(i);

			ResultSetField* field = record_bind.add (col->title);
			//TODO: Modificare per l'utilizzo di StringBuffer.
			//this->bind(i+1, field->acValue, col->size);
		}
	}
}

ODBCResultSet::~ODBCResultSet()
{
}

bool ODBCResultSet::eof()
{
	if ( m_lNumRows == 0 )
		return true;

	return (this->m_iRec == m_lNumRows);
}

long ODBCResultSet::getRecordCount()
{
	return m_lNumRows;
}

ResultSetMetaData* ODBCResultSet::getMetaData()
{
	return &mtdt_bind;
}

bool ODBCResultSet::moveNext()
{
	try
	{
		SQLRETURN rc = SQLFetchScroll(*this->m_hStmt,SQL_FETCH_NEXT,0);
		if(rc == SQL_NO_DATA) return false;
		if(rc == SQL_ERROR)
		{
			handleError(); 
		}
	}
	catch(...)
	{
		handleError();
	}

	return true;
}

bool ODBCResultSet::movePrevious()
{
	try
	{
		SQLRETURN rc = SQLFetchScroll(*this->m_hStmt,SQL_FETCH_PRIOR,0);
		if(rc == SQL_NO_DATA || rc < 0) return false;
		if(rc == SQL_ERROR)
		{
			handleError();
		}
	}
	catch(...)
	{
		handleError();
	}
	return true;
}

bool ODBCResultSet::moveFirst()
{
	try
	{		
		SQLRETURN rc = SQLFetchScroll(*this->m_hStmt,SQL_FETCH_FIRST,0);
		if(rc == SQL_NO_DATA) return false;
		
		if(rc < 0)
		{
			return false;
		}
		if(rc == SQL_ERROR)
		{
			handleError();
		}
	}
	catch(...)
	{
		handleError();
	}
	return true;
}

bool ODBCResultSet::moveLast()
{
	try
	{
		SQLRETURN rc = SQLFetchScroll(*this->m_hStmt,SQL_FETCH_LAST,0);
		if(rc == SQL_NO_DATA || rc < 0) return false;
		if(rc == SQL_ERROR)
		{
			handleError();
		}
	}
	catch(...)
	{
		handleError();
	}
	return true;
}

ResultSetRecord* ODBCResultSet::getRecord()
{
	return &record_bind;
}

bool ODBCResultSet::bind(int col_no,char* buff,int len)
{
	SQLRETURN rc;
	try 
	{
		SQLINTEGER sz = 0;			

		rc = SQLBindCol(*this->m_hStmt, col_no, SQL_C_CHAR,buff, len, &sz);
	}
	catch(...)
	{	
		handleError();
	}

	if( rc == SQL_ERROR)
	{
		handleError();
	}

	return true;
}

void ODBCResultSet::handleError()
{
	SQLGetDiagRec(SQL_HANDLE_STMT,*this->m_hStmt,this->m_iRec,
		this->m_cState,&this->m_nErr,this->m_cMsg,
		sizeof(m_cMsg),&this->m_nMsg);

	throw SQLException((char*)this->m_cMsg);
}