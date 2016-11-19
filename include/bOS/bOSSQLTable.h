#ifndef _BOS_SQLTABLE_H_
#define _BOS_SQLTABLE_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLCommand.h"
#include "bOSSQLCommands.h"

namespace bOS
{
	namespace SQL
	{
		class SQLTable;
		typedef BOS_API vector<SQLTable*> SQLTablesList;

		class BOS_API SQLTable
		{
		public:

			SQLTable(bool bIsRecord);
			virtual ~SQLTable();

			//all get methods call addSqlCommands
			void getInsertSQLCommand(SQLCommands&);
			void getUpdateSQLCommand(SQLCommands&);
			void getDeleteSQLCommand(SQLCommands&);
			void getSelectSQLCommand(SQLCommands&);
			void getCreateSQLCommand(SQLCommands&);
			void getDropSQLCommand(SQLCommands&);

			virtual SQLTablesList getSQLTables() { return vTables;}

			virtual const char* acGetTableName() = 0;
			virtual void setRecord(ResultSetRecord&) = 0;
			virtual String acGetWhere() = 0;
			virtual bool parse(ResultSetRecord*);
			virtual bool parse(ResultSetField*) { return true;}

			bool isRecord() { return bIsRecord;}
			bool isSetted() { return bIsSetted;}

			virtual bool haveAutoIncrementField() = 0;
			virtual void setAutoIncrementField(long ) = 0;

			virtual void addSQLCommands(SQLCommands& vCommands, int operation);

		protected:



			//use only in recursive way
			bool bIsSetted;

			SQLTablesList vTables;

		private:
			//SQLTable is used for Record Object and Table Object.
			//the bIsRecord tell if derived class is a record or a table.
			bool bIsRecord;

		};
	}
}

#endif //_BOS_SQLTABLE_H_
