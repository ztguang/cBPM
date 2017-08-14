#include "CommonDefines.h"

#include "bOSODBCConnectionData.h"
using namespace bOS::SQL::ODBC;

ODBCConnectionData::ODBCConnectionData() : bOS::SQL::SQLConnectionData()
{
}

ODBCConnectionData::~ODBCConnectionData()
{
}

void ODBCConnectionData::init(SQLConnectionData* connData)
{
	ODBCConnectionData* odbc = (ODBCConnectionData*)connData;
	this->sUser = odbc->sUser;
	this->sPassword = odbc->sPassword;
	this->sDsn = odbc->sDsn;
}