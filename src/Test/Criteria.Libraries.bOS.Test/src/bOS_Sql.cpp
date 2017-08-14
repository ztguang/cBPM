#include "bOS/bOS.h"
#include "bOS/bOSSQLConnectionManager.h"
#include "bOS/bOSSQLConnection.h"
#include "bOS/bOSResultSet.h"
#include "bOS/bOSResultSetField.h"
#include "bOS/bOSResultSetRecord.h"
#include "bOS/bOSmySQLResultSetMetaData.h"
using namespace bOS::SQL;

#include "bOS/bOSmySQLConnectionData.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

void mySql()
{
	SQLConnectionManager manager;
	manager.init(SQLConnectionManager::MYSQL);
	mySQL::mySQLConnectionData* connData = new mySQL::mySQLConnectionData();
	connData->iPort=3306;
	connData->sDB="scenario";
	connData->sHost="127.0.0.1";
	connData->sPassword="scenario";
	connData->sUser="scenario";

	manager.createPool(connData, 1, 1);
	SQLConnection* connection = manager.get();
	connection->execute ("pippo");
	ResultSet* rs = connection->executeQuery("select * from activities");

	ResultSetMetaData* rsmd = rs->getMetaData();
	ResultSetRecord* record = rs->getRecord();
	
	while ( rs->moveNext() )
	{
		int iCol = record->size();
		for ( int i=0; i<iCol; i++)
		{
			ResultSetField* field = record->at(i);

			cout << field->sName << "-" << field->sValue.getData() << endl;
		}
	}
	rs->close();

	manager.release(connection);

}