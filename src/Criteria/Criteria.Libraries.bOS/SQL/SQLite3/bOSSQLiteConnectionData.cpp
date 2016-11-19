#ifdef _USE_SQLITE3_

#include "CommonDefines.h"

#include "bOSSQLiteConnectionData.h"
using namespace bOS::SQL::SQLite3;

SQLiteConnectionData::SQLiteConnectionData() : bOS::SQL::SQLConnectionData()
{
}

SQLiteConnectionData::~SQLiteConnectionData()
{
}

void SQLiteConnectionData::init(SQLConnectionData* connData)
{
	SQLiteConnectionData* sqlite = (SQLiteConnectionData*)connData;

	this->sDB = sqlite->sDB;
	this->sPath = sqlite->sPath;
}


#endif