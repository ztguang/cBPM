#ifndef _BOS_SQL_COMMAND_H_
#define _BOS_SQL_COMMAND_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetField.h"
#include "bOSResultSetRecord.h"

namespace bOS
{
	namespace SQL
	{
		class BOS_API SQLCommand
		{
		public:
			SQLCommand();
			virtual ~SQLCommand();

			enum SQLOperation
			{
				ADD,
				MODIFY,
				ERASE,
				SELECT,
				CREATE,
				DROP
			};

			void setOperation (SQLOperation _operation) { iOperation = _operation;}
			void setTable(const char* acTable) { sTable = acTable;}
			void addField( ResultSetField* field) { record.add(field); }
			void addRecord( ResultSetRecord& record);
			ResultSetRecord* addRecord(); 
			void addWhere(const char* acWhere);

			String getSQLStringCommand();
			String getPreparedSQLStringCommand();

			ResultSetRecord& getRecord() { return record;}

		private:
			SQLOperation iOperation;
			String sTable;
			String sWhere;

			ResultSetRecord record;

		};
	}
}

#endif //_BOS_SQL_COMMAND_H_
