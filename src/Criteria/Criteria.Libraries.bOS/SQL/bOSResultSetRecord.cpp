#include "CommonDefines.h"

#include "bOSResultSetRecord.h"
using namespace bOS::SQL;

ResultSetRecord::ResultSetRecord()
{
	;
}

ResultSetRecord::~ResultSetRecord()
{
	this->clear();
}

void ResultSetRecord::clear()
{
	int iSize = vFields.size();
	for ( int i=0; i<iSize;i++)
	{
		delete vFields.at(i);
	}

	vFields.clear();
}

ResultSetField* ResultSetRecord::add(const char* acName)
{
	ResultSetField* field = new ResultSetField(acName);

	vFields.push_back(field);

	return field;
}

void ResultSetRecord::add(ResultSetField* field)
{
	vFields.push_back(field);
}


int ResultSetRecord::size()
{
	return vFields.size();
}

ResultSetField* ResultSetRecord::at(int i)
{
	return vFields.at(i);
}