#include "CommonDefines.h"

#include "bOSResultSetMetaData.h"
#include "bOSSQLException.h"
#include "bOSResultSetColumn.h"
using namespace bOS::SQL;

#include "bOSmySQLResultSet.h"
#include "bOSmySQLResultSetMetaData.h"
#include "bOSmySQLResultSetField.h"
using namespace bOS::SQL::mySQL;

mySQLResultSet::mySQLResultSet(MYSQL_RES* rslt) : ResultSet()
{
	assert(rslt != NULL);
	this->mySqlResultSet = rslt;
	this->lNumRows = (unsigned long)mysql_num_rows(mySqlResultSet);
	//TODO:
	this->lRec = 0;

	//Fixing MetaData
	int iCols = mysql_num_fields( mySqlResultSet ) ;
	mtdt_bind.setNumCols(iCols);

	MYSQL_FIELD* mySqlField = NULL;
	for ( iCols = 0 ; mySqlField = mysql_fetch_field( mySqlResultSet ) ; iCols++ )
	{
		ResultSetColumn* col = mtdt_bind.addColumn();
		strcpy( col->title, mySqlField->name ) ;

		if ( IS_NUM (mySqlField->type) )
		{
			col->type = FieldType(INTEGER);
		}
		else
		{
			col->type = FieldType(VARCHAR);
		}
		col->size = mySqlField->length;
		col->nullable = !(IS_NOT_NULL(mySqlField->flags));
	}

}

mySQLResultSet::~mySQLResultSet()
{
	mysql_free_result(mySqlResultSet);
}

bool mySQLResultSet::eof()
{
	if ( lNumRows == 0 )
		return true;

	if (this->lRec > lNumRows)
	{
		return true;
	}

	return !(this->moveNext());
}

long mySQLResultSet::getRecordCount()
{
	return lNumRows;
}

ResultSetMetaData* mySQLResultSet::getMetaData()
{
	return &mtdt_bind;
}

ResultSetRecord* mySQLResultSet::getRecord()
{
	return &record_bind;
}

bool mySQLResultSet::moveNext()
{
	mySqlRow = mysql_fetch_row(mySqlResultSet);
	if ( mySqlRow == NULL )
	{
		return false;
	}

	this->binding_column();

	lRec++;
	return true;
}

bool mySQLResultSet::movePrevious()
{
	//TODO: Implement movePrevious
	return false;

	//this->binding_column();
}

bool mySQLResultSet::moveFirst()
{
	//TODO: Implement moveFirst
	return false;

	//this->binding_column();
}

bool mySQLResultSet::moveLast()
{
	//TODO: Implement moveLast
	return false;

	//this->binding_column();
}

void mySQLResultSet::binding_column()
{
	record_bind.clear();
	//this->getMetaData();
	int iColSize = mtdt_bind.getColumnCount();
	for(int i=0;i<iColSize;i++)
	{
		ResultSetColumn* col = mtdt_bind.getColumn(i);
		ResultSetField* field = record_bind.add (col->title);
		field->iType  = col->type;
		field->sValue.append((const char*)mySqlRow[i]);
		/*
		strncpy(field->acValue, (const char*)mySqlRow[i], col->size);
		field->acValue[col->size]='\0';
		*/
	}
}

bool mySQLResultSet::bind(int col_no,char* buff,int buff_len)
{
	return true;
}
