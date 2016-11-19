#ifndef __BOS_SQLITE3_RESULTSET_H__
#define __BOS_SQLITE3_RESULTSET_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSet.h"
#include "bOSResultSetMetaData.h"

#include "bOSSQLiteResultSetMetaData.h"

#include "CppSQLite3.h"

namespace bOS
{
    namespace SQL
    {
		namespace SQLite3
		{
			class BOS_API SQLiteResultSet : public bOS::SQL::ResultSet
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

				CppSQLite3Query query;

				//mySQL not manage Bind Function and so for every move it'mandatory re-execute setRecord;
				SQLiteResultSetMetaData mtdt_bind;
				ResultSetRecord record_bind;

				SQLiteResultSet(CppSQLite3Query&);
				~SQLiteResultSet();

				void binding_column();
				

				SQLiteResultSetMetaData mtdt;
				
				long lNumRows;
				long lRec;


				bool bFirstTime;

				friend class SQLiteConnection;
			};
		}
	}
}

#endif //__BOS_SQLITE3_RESULTSET_H__
