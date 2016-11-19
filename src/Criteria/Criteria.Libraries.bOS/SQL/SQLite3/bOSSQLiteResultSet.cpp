#ifdef _USE_SQLITE3_

#include "CommonDefines.h"

#include "bOSResultSetMetaData.h"
#include "bOSSQLException.h"
#include "bOSResultSetColumn.h"
using namespace bOS::SQL;

#include "bOSSQLiteResultSet.h"
#include "bOSSQLiteResultSetMetaData.h"
#include "bOSSQLiteResultSetField.h"
using namespace bOS::SQL::SQLite3;

SQLiteResultSet::SQLiteResultSet(CppSQLite3Query& _query) : ResultSet()
{
	//utilizzato per evitare di fare la moveNext la prima volta..
	bFirstTime = true;

	this->query= _query;
	this->lRec = 0;

	int iCols = query.numFields() ;
	mtdt_bind.setNumCols(iCols);

	for (int fld = 0; fld < query.numFields(); fld++)
	{
		ResultSetColumn* col = mtdt_bind.addColumn();
		strcpy( col->title, query.fieldName(fld) ) ;

		switch ( query.fieldDataType(fld) )
		{
		case SQLITE_INTEGER:
		case SQLITE_FLOAT:
			col->type = FieldType(INTEGER);
			break;

		case SQLITE_TEXT:
			col->type = FieldType(VARCHAR);
			break;

		case SQLITE_BLOB:
		case SQLITE_NULL:
			col->type = FieldType(VARCHAR);
			break;
		}
		//TODO:
		//col->size = query.fieldlength;
		col->nullable = false;
	}

}

SQLiteResultSet::~SQLiteResultSet()
{
}

bool SQLiteResultSet::eof()
{
	return query.eof();
}

long SQLiteResultSet::getRecordCount()
{
	return lNumRows;
}

ResultSetMetaData* SQLiteResultSet::getMetaData()
{
	return &mtdt_bind;
}

ResultSetRecord* SQLiteResultSet::getRecord()
{
	this->binding_column();
	return &record_bind;
}

bool SQLiteResultSet::moveNext()
{
	if ( bFirstTime )
		bFirstTime = false;
	else
		query.nextRow();

	return !this->eof();
}

bool SQLiteResultSet::movePrevious()
{
	//TODO: Implement movePrevious
	return false;
}

bool SQLiteResultSet::moveFirst()
{
	//TODO: Implement moveFirst
	return false;
}

bool SQLiteResultSet::moveLast()
{
	//TODO: Implement moveLast
	return false;
}

void SQLiteResultSet::binding_column()
{
	record_bind.clear();
	//this->getMetaData();
	int iColSize = mtdt_bind.getColumnCount();
	for(int i=0;i<iColSize;i++)
	{
		ResultSetColumn* col = mtdt_bind.getColumn(i);
		ResultSetField* field = record_bind.add (col->title);
		field->iType  = col->type;
		field->sValue.clear();
		field->sValue.append(query.getStringField(i));
	}
}

bool SQLiteResultSet::bind(int col_no,char* buff,int buff_len)
{
	return true;
}

#endif
