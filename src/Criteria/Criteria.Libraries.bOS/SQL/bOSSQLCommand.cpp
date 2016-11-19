#include "CommonDefines.h"

#include "bOSSQLCommand.h"
using namespace bOS::SQL;

#include "bOSStringBuffer.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

SQLCommand::SQLCommand()
{
}

SQLCommand::~SQLCommand()
{
}

String SQLCommand::getSQLStringCommand()
{

	int iSize = record.size();
	StringBuffer sSQL;

	int i;
	bool bComma=false;
	bool bWhere=true;

	switch (iOperation) 
	{
	case SQLCommand::ADD:

		sSQL.append("insert into ");
		sSQL.append(sTable);
		sSQL.append(" (");
		bComma=false;
		for ( i=0; i<iSize;i++)
		{
			if ( record.at(i)->iType != FieldType(AUTOINCREMENT) )
			{
				if ( bComma )
				{
					sSQL.append(",");
				}
				else
					bComma = true;

				sSQL.append(record.at(i)->sName);
			}
		}
		sSQL.append(") VALUES (");
		bComma=false;
		for ( i=0; i<iSize;i++)
		{
			if ( record.at(i)->iType != FieldType(AUTOINCREMENT) )
			{
				if ( bComma )
				{
					sSQL.append(",");
				}
				else
					bComma = true;

				if ( record.at(i)->iType == FieldType(VARCHAR) )
				{
					sSQL.append(StringUtils::returnQuoteAndTwice(record.at(i)->sValue.getData() ));
				}
				else
				{
					sSQL.append(record.at(i)->sValue.getData());
				}
			}			
		}
		sSQL.append(")");

		bWhere = false;
		break;

	case SQLCommand::MODIFY:
		sSQL.append("Update ");
		sSQL.append(sTable);
		sSQL.append(" SET ");
		bComma=false;
		for ( i=0; i<iSize;i++)
		{
			if ( record.at(i)->iType != FieldType(AUTOINCREMENT) ) 
			{
				if ( bComma )
				{
					sSQL.append(",");
				}
				else 
					bComma =true;

				sSQL.append(record.at(i)->sName);
				sSQL.append("=");
				if ( record.at(i)->iType == FieldType(VARCHAR) )
				{
					sSQL.append(StringUtils::returnQuoteAndTwice(record.at(i)->sValue.getData()));
				}
				else
				{
					sSQL.append(record.at(i)->sValue.getData());
				}
			}
		}
		break;

	case SQLCommand::ERASE:
		sSQL.append("delete from ");
		sSQL.append(sTable);
		break;

	case SQLCommand::DROP:
		sSQL.append("drop table ");
		sSQL.append(sTable);
		bWhere = false;
		break;

	case SQLCommand::SELECT:
		sSQL.append("select ");
		for ( i=0; i<iSize;i++)
		{
			if ( i > 0 )
			{
				sSQL.append(",");
			}
			sSQL.append(record.at(i)->sName);
		}
		if ( iSize == 0) 
		{
			sSQL.append("*");
		}

		sSQL.append(" from ");
		sSQL.append(sTable);
		break;

	case SQLCommand::CREATE:
		sSQL.append("create table ");
		sSQL.append(sTable);
		sSQL.append("(");
		for ( i=0; i<iSize;i++)
		{
			if ( i > 0 )
			{
				sSQL.append(",");
			}
			sSQL.append(record.at(i)->sName);
			sSQL.append(" ");

			switch ( record.at(i)->iType ) 
			{
			case FieldType(VARCHAR):
				sSQL.append ( "varchar(");
				sSQL.append ( record.at(i)->iSize);
				sSQL.append (")");
				break;
			case FieldType(NUMERIC):
				sSQL.append ( "bigint");
				break;
			case FieldType(INTEGER):
				sSQL.append ( "int");
				break;
			case FieldType(AUTOINCREMENT):
				sSQL.append("SMALLINT IDENTIFY(1,1) NOT NULL"); 
				break;
			}
		}
		sSQL.append(")");

		bWhere = false;
		break;
	}

	if ( bWhere && sWhere.size() > 0 )
	{
		sSQL.append(" WHERE ");
		sSQL.append(sWhere);
	}
	
	
	return sSQL.getData();
}

String SQLCommand::getPreparedSQLStringCommand()
{

	int iSize = record.size();
	StringBuffer sSQL;
	StringBuffer sSQLValues;

	int i;
	bool bComma=false;
	bool bWhere=true;

	switch (iOperation) 
	{
	case SQLCommand::ADD:

		sSQL.append("Insert into ");
		sSQL.append(sTable);
		sSQL.append(" (");

		sSQLValues.append(") VALUES (");

		bComma=false;
		for ( i=0; i<iSize;i++)
		{
			if ( record.at(i)->iType != FieldType(AUTOINCREMENT) )
			{
				if ( bComma )
				{
					sSQL.append(",");
					sSQLValues.append(",");
				}
				else
					bComma = true;

				sSQLValues.append("?");
				sSQL.append(record.at(i)->sName);
			}
		}
		sSQL.append(sSQLValues.getData());
		sSQL.append(")");

		bWhere = false;
		break;

	case SQLCommand::MODIFY:
		sSQL.append("Update ");
		sSQL.append(sTable);
		sSQL.append(" SET ");
		bComma=false;
		for ( i=0; i<iSize;i++)
		{
			if ( record.at(i)->iType != FieldType(AUTOINCREMENT) ) 
			{
				if ( bComma )
				{
					sSQL.append(",");
				}
				else 
					bComma =true;

				sSQL.append(record.at(i)->sName);
				sSQL.append("=");
				sSQL.append("?");
			}
		}
		break;

	case SQLCommand::ERASE:
		sSQL.append("delete from ");
		sSQL.append(sTable);
		break;

	case SQLCommand::DROP:
		sSQL.append("drop table ");
		sSQL.append(sTable);
		bWhere = false;
		break;

	case SQLCommand::SELECT:
		sSQL.append("select ");
		for ( i=0; i<iSize;i++)
		{
			if ( i > 0 )
			{
				sSQL.append(",");
			}
			sSQL.append(record.at(i)->sName);
		}
		if ( iSize == 0) 
		{
			sSQL.append("*");
		}

		sSQL.append(" from ");
		sSQL.append(sTable);
		break;

	case SQLCommand::CREATE:
		sSQL.append("create table ");
		sSQL.append(sTable);
		sSQL.append("(");
		for ( i=0; i<iSize;i++)
		{
			if ( i > 0 )
			{
				sSQL.append(",");
			}
			sSQL.append(record.at(i)->sName);
			sSQL.append(" ");

			switch ( record.at(i)->iType ) 
			{
			case FieldType(VARCHAR):
				sSQL.append ( "varchar(");
				sSQL.append ( record.at(i)->iSize);
				sSQL.append (")");
				break;
			case FieldType(NUMERIC):
				sSQL.append ( "bigint");
				break;
			case FieldType(INTEGER):
				sSQL.append ( "int");
				break;
			case FieldType(AUTOINCREMENT):
				sSQL.append("SMALLINT IDENTIFY(1,1) NOT NULL"); 
				break;
			}
		}
		sSQL.append(")");

		bWhere = false;
		break;
	}

	if ( bWhere && sWhere.size() > 0 )
	{
		sSQL.append(" WHERE ");
		sSQL.append(sWhere);
	}
	
	
	return sSQL.getData();
}

void SQLCommand::addRecord( ResultSetRecord& _record)
{
	int iSize = _record.size();
	for ( int i=0; i<iSize;i++)
	{
		this->addField( _record.at(i) );
	}
}

ResultSetRecord* SQLCommand::addRecord()
{
	return &record;
}

void SQLCommand::addWhere(const char* acWhere)
{

	if ( sWhere.length() > 0 )
	{
		sWhere+=" AND ";
	}

	sWhere += acWhere;
}