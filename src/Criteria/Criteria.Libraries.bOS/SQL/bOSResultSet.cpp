#include "CommonDefines.h"

#include "bOSResultSet.h"
using namespace bOS::SQL;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

ResultSet::ResultSet()
{
    /*
	vRows.clear();
    iRow=0;
	*/
}

ResultSet::~ResultSet()
{
    /*
	vRows.clear();
    iRow=0;
	*/
}

/*
bool ResultSet::eof()
{
    return ( iRow == vRows.size() );
}

void ResultSet::moveFirst()
{
    iRow = 0;
}

void ResultSet::moveLast()
{
    iRow = vRows.size();
	
	if ( iRow > 0 )
		iRow--;
}

bool ResultSet::moveNext()
{
    if ( iRow == vRows.size() )
        return false;
    else
	{
		iRow++;
        return true;
	}
}

bool ResultSet::movePrevious()
{
    if ( iRow == 0 )
        return false;
    else
	{
		iRow--;
        return true;
	}
}

long ResultSet::getRecordCount()
{
    return vRows.size();
}
*/
void ResultSet::close()
{
    delete this;
}

