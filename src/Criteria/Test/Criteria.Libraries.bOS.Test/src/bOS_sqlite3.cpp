#include "bOS/bOS.h"
#include "bOS/bOSSQLConnectionManager.h"
#include "bOS/bOSSQLConnection.h"
#include "bOS/bOSResultSet.h"
#include "bOS/bOSResultSetField.h"
#include "bOS/bOSResultSetRecord.h"
#include "bOS/bOSmySQLResultSetMetaData.h"
using namespace bOS::SQL;

#include "bOS/bOSSQLiteConnectionData.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

void sqlite3()
{
	SQLConnectionManager manager;
	manager.init(SQLConnectionManager::SQLITE3);
	SQLite3::SQLiteConnectionData* connData = new SQLite3::SQLiteConnectionData();
	connData->sDB = "scenario.db";
	connData->sPath=".";
	manager.createPool(connData, 1, 1);
	SQLConnection* connection = manager.get();
	
	
	//connection->execute("insert into sf_attributes values (5,\"111\", \"111\",\"2222\",\"3333\",\"4444\")");
	//connection->execute("insert into sf_attributes values (6,\"111\", \"111\",\"2222\",\"3333\",\"4444\")");
	//connection->execute("insert into sf_attributes values (7,\"111\", \"111\",\"2222\",\"3333\",\"4444\")");
	//connection->execute("insert into sf_attributes values (8,\"111\", \"111\",\"2222\",\"3333\",\"4444\")");
	
	ResultSet* rs = connection->executeQuery("select PROCESS_ID, ACTIVITY_ID from SF_Attributes");

	while (!rs->eof())
	{
		ResultSetRecord* record = rs->getRecord();
		int iCol = record->size();
		for ( int i=0; i<iCol; i++)
		{
			ResultSetField* field = record->at(i);
				cout << field->sName << "-" << field->sValue.getData() << endl;
		}
		rs->moveNext();
	}
	
	rs->close();
	
	manager.release(connection);

}