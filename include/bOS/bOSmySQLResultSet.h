#ifndef __BOS_MYSQL_RESULTSET_H__
#define __BOS_MYSQL_RESULTSET_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSet.h"
#include "bOSResultSetMetaData.h"

#include "bOSmySQLResultSetMetaData.h"

//#include <windows.h>      //ztg delete
#include "mySQL/mysql.h"

namespace bOS
{
    namespace SQL
    {
		namespace mySQL
		{
			class BOS_API mySQLResultSet : public bOS::SQL::ResultSet
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

				MYSQL_RES* mySqlResultSet;
				MYSQL_ROW mySqlRow;

				//mySQL not manage Bind Function and so for every move it'mandatory re-execute setRecord;
				mySQLResultSetMetaData mtdt_bind;
				ResultSetRecord record_bind;	//record corrente

				mySQLResultSet(MYSQL_RES*);
				~mySQLResultSet();

				void binding_column();

				unsigned long lNumRows;
				unsigned long lRec;

				friend class mySQLConnection;
			};
		}
	}
}

#endif //__BOS_MYSQL_RESULTSET_H__
