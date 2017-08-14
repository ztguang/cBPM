#include "CommonDefines.h"

#include "bOSSQLTable.h"
using namespace bOS::SQL;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

SQLTable::SQLTable(bool _isRecord)
{
	bIsRecord = _isRecord;
	bIsSetted = true;
}

SQLTable::~SQLTable()
{
	;
}

void SQLTable::addSQLCommands(SQLCommands& vCommands,int operation)
{
	//
	SQLCommand* command = new SQLCommand();

	command->setOperation ((SQLCommand::SQLOperation)operation);
	command->setTable(this->acGetTableName() );

	ResultSetRecord* record = command->addRecord();
	this->setRecord(*record);

	switch ( operation )
	{
	case SQLCommand::ERASE:
	case SQLCommand::MODIFY:
	case SQLCommand::SELECT:
		command->addWhere(this->acGetWhere().c_str() );	
		break;
	}

	vCommands.add (command);
}

void SQLTable::getCreateSQLCommand(SQLCommands& vCommands)
{
	addSQLCommands(vCommands, SQLCommand::CREATE);
}

void SQLTable::getInsertSQLCommand(SQLCommands& vCommands)
{
	addSQLCommands(vCommands, SQLCommand::ADD);
}

void SQLTable::getUpdateSQLCommand(SQLCommands& vCommands)
{
	addSQLCommands(vCommands, SQLCommand::MODIFY);
}

void SQLTable::getDeleteSQLCommand(SQLCommands& vCommands)
{
	addSQLCommands(vCommands, SQLCommand::ERASE);
}

void SQLTable::getSelectSQLCommand(SQLCommands& vCommands)
{
	addSQLCommands(vCommands, SQLCommand::SELECT);
}

void SQLTable::getDropSQLCommand(SQLCommands& vCommands)
{
	addSQLCommands(vCommands, SQLCommand::DROP);
}

bool SQLTable::parse(ResultSetRecord* record)
{
	unsigned int uiSize = record->size();
	for ( unsigned int i=0;i<uiSize;i++)
	{
		ResultSetField* field = record->at(i);

		if ( this->parse(field) )
		{
			continue;
		}
		else
			return false;
	}

	return true;
}


