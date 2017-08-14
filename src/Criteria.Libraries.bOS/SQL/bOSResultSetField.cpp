#include "CommonDefines.h"

#include "bOSResultSetField.h"
using namespace bOS::SQL;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

ResultSetField::ResultSetField(const char* acName)
{
	sName = acName;
	iType = VARCHAR;
}

//ResultSetField::ResultSetField(const char* acName, String& _sValue, int _Size)	//ztg delete
ResultSetField::ResultSetField(const char* acName, String _sValue, int _Size)
{
	sName = acName;
	sValue.append(_sValue.c_str());
	iType = VARCHAR;

	if ( _Size == 0)
	{
		iSize= 255;
	}
	else
		iSize = _Size;
}

ResultSetField::ResultSetField(const char* acName, const char* acValue, int _Size)
{
	sName = acName;
	sValue.append(acValue);
	iType = VARCHAR;

	if ( _Size == 0)
	{
		iSize= 255;
	}
	else
		iSize = _Size;

}

ResultSetField::ResultSetField(const char* acName, long lValue)
{
	sName = acName;
	sValue.append(lValue);
	iType = NUMERIC;
}

ResultSetField::ResultSetField(const char* acName, int iValue)
{
	sName = acName;
	sValue.append(iValue);
	iType = INTEGER;
}

/*
ResultSetField::ResultSetField( const ResultSetField& field)
{
	sName = field.sName;
	iType = field.iType;
}
*/
ResultSetField::~ResultSetField()
{
}

