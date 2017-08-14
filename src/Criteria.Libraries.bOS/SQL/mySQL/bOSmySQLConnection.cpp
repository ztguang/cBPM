#include "CommonDefines.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLException.h"
using namespace bOS::SQL;

#include "bOSmySQLConnection.h"
#include "bOSmySQLResultSet.h"
using namespace bOS::SQL::mySQL;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

mySQLConnection::mySQLConnection(mySQLConnectionData* data) : SQLConnection()
{
	sHost = data->sHost;
	iPort = data->iPort ? data->iPort : MYSQL_PORT;
	sDB = data->sDB;
	sUser = data->sUser;
	sPwd = data->sPassword;

	this->iTimeout = 10;
	this->bConnected = false;

	connection = NULL;
}

mySQLConnection::~mySQLConnection()
{
    this->close();
}

bool mySQLConnection::isConnected()
{
	return bConnected;
}

long mySQLConnection::execute( const char* acSql )
{
	if(!this->bConnected)
	{
		throw SQLException("Call Open() before Execute()");
	}

	int iState = mysql_query(connection, acSql);
	if(iState != 0)
	{
		string errormessage = mysql_error(connection);
		throw SQLException(mysql_error(connection));
	}
	//?necessario per eseguire altre query
	MYSQL_RES* resultset = mysql_store_result(connection);
	unsigned long lCount;
	if ( resultset)
	{
		//warning this sql do not must return a resultset.....
	}
	else
	{
		lCount =  (unsigned long)mysql_affected_rows(connection);
    }

	return lCount;
}

long mySQLConnection::executePrepare( SQLCommands& vCommands)
{
	MYSQL_STMT* stmt = mysql_stmt_init(&mySql);
	if (!stmt)
	{
		throw SQLException("Impossible to initialize statement");
	}

	if ( vCommands.size() < 1 )
	{
		mysql_stmt_close(stmt);
		throw SQLException("Impossible to prepare an empty commands list");
	}

	SQLCommand* sqlCommand = vCommands.at (0);

	String sPreparedSQL =sqlCommand->getPreparedSQLStringCommand();

	if (mysql_stmt_prepare(stmt, sPreparedSQL.c_str(), sPreparedSQL.length()))
	{
		StringBuffer sSQLError;
		sSQLError.append ("Impossible to prepare statement.");
		sSQLError.append (sPreparedSQL);

		mysql_stmt_close(stmt);
		throw SQLException(sSQLError.getData());
	}

	unsigned int uiSize =vCommands.size();
	unsigned long lCount =0;
	for ( unsigned int i=0; i<uiSize;i++)
	{
		bOS::SQL::ResultSetRecord& record = vCommands.at(i)->getRecord();

		unsigned int uiFieldSize = record.size();
		MYSQL_BIND*		bind = new MYSQL_BIND[uiFieldSize];
		unsigned long*	length = new unsigned long[uiFieldSize];
		memset(bind, 0, sizeof(bind));
		for ( unsigned int j=0; j<uiFieldSize;j++)
		{
			bOS::SQL::ResultSetField* field = record.at(j);

			switch ( field->iType )
			{
			case FieldType(VARCHAR):
				bind[j].buffer_type= MYSQL_TYPE_STRING;
				bind[j].buffer = (char*)field->sValue.getData();
				length[j]=field->sValue.size();
				break;

			case FieldType(NUMERIC):
				bind[j].buffer_type= MYSQL_TYPE_LONG;
				bind[j].buffer = (void*)atol(field->sValue.getData());
				break;

			case FieldType(INTEGER):
				bind[j].buffer_type= MYSQL_TYPE_LONG;
				bind[j].buffer = (void*)atoi(field->sValue.getData());
				break;
			}

			bind[j].length= &length[0];
			bind[j].is_null= 0;
		}

		/* Bind the buffers */
		if (mysql_stmt_bind_param(stmt, bind))
		{
			mysql_stmt_close(stmt);
			throw SQLException("Impossible to bind fields");
		}

		if (mysql_stmt_execute(stmt))
		{
			throw SQLException("Impossible to execute statement");
		}

		lCount+=(unsigned long)mysql_stmt_affected_rows(stmt);
	}

	if (mysql_stmt_close(stmt))
	{
		throw SQLException("Impossible to close binded statement");
	}

	return lCount;
}

unsigned long mySQLConnection::getAutoIncrement()
{
	return (unsigned long)mysql_insert_id(connection);
}

ResultSet* mySQLConnection::executeQuery( const char* acSql )
{
	if(!this->bConnected)
	{
		throw SQLException("Call Open() before Execute()");
	}

	int iState = mysql_query(connection, acSql);
	if(iState != 0)
	{
		throw SQLException(mysql_error(connection));
	}
	//?necessario per eseguire altre query
	MYSQL_RES* resultset = mysql_store_result(connection);
	mySQLResultSet* rslt = new mySQLResultSet(resultset);
	return rslt;
}

ResultSet* mySQLConnection::executeQuery(const char* acSql,int iCursorType,bool bScrollable)
{
	//TODO: Scrollable cursor to manage.
	return this->executeQuery(acSql);
}

void mySQLConnection::beginTrans()
{
	throw SQLException("Not Supported");
}

void mySQLConnection::commit()
{
	//TODO: commit operation to manage
}

void mySQLConnection::rollback()
{
	//TODO: rollback operation to manage
}

bool mySQLConnection::supportTransaction()
{
	return false;
}

void mySQLConnection::open()
{
	mysql_init(&mySql);
	connection = mysql_real_connect(&mySql, sHost.c_str(), sUser.c_str(), sPwd.c_str(), NULL, iPort ,  NULL, CLIENT_FOUND_ROWS);
	if ( connection == NULL)
	{
		throw SQLException(mysql_error(&mySql));
	}

	if ( mysql_select_db( &mySql, sDB.c_str() ) < 0 )
	{
		mysql_close( &mySql ) ;
		throw SQLException(mysql_error(&mySql));
	}

	bConnected = true;
}

void mySQLConnection::close()
{
	if (connection)
	{
		mysql_close(connection);
		this->bConnected = false;
	}
}

