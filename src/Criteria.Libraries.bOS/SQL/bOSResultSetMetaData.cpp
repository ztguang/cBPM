#include "CommonDefines.h"

#include "bOSResultSetMetaData.h"
using namespace bOS::SQL;

ResultSetMetaData::ResultSetMetaData()
{
	iNumCols = 0;
}

ResultSetMetaData::~ResultSetMetaData()
{
	this->clear();
}

void ResultSetMetaData::setNumCols(int n)
{
	iNumCols = n;
}
		
int ResultSetMetaData::getColumnCount()
{
	return iNumCols;
}

void ResultSetMetaData::addColumn(ResultSetColumn* col)
{ 
	vColumns.push_back(col); 
}

ResultSetColumn* ResultSetMetaData::getColumn(unsigned int nrCol)
{ 
	if ( (nrCol>=0) && (nrCol<vColumns.size()) ) 
	{
		return vColumns[nrCol]; 
	}

	return NULL;
}

ResultSetColumn* ResultSetMetaData::getColumn(const char* acTitle)
{
	int iSize = vColumns.size();

	ResultSetColumn* column = NULL;
	for(int i=0;i<iSize;i++)
	{
		column = vColumns.at(i);
		if ( strcmp(column->title, acTitle) == 0 )
		{
			return column;
		}
	}

	return NULL;
}

void ResultSetMetaData::clear()
{
	int iSize = vColumns.size();

	for ( int i=0; i<iSize; i++)
	{
		delete vColumns.at(i);
	}
	vColumns.clear();
}

ResultSetColumn* ResultSetMetaData::addColumn ()
{
	ResultSetColumn* col = new ResultSetColumn();
	vColumns.push_back(col);
	return col;
}