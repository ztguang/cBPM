#include "CommonDefines.h"

#include "bOSSQLField.h"
using namespace bOS::SQL;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

SQLField::SQLField(const char* acName, String& sValue)
{
	sName = acName;
	strcpy(uValue.sValue,sValue.c_str());
	iType = SQLField::STRING;
}

SQLField::SQLField(const char* acName, const char* acValue)
{
	sName = acName;
	strcpy(uValue.sValue,acValue);
	iType = SQLField::STRING;
}

SQLField::SQLField(const char* acName, long lValue)
{
	sName = acName;
	uValue.lValue = lValue;
	iType = SQLField::LONG;
}

SQLField::SQLField(const char* acName, int iValue)
{
	sName = acName;
	uValue.iValue = iValue;
	iType = SQLField::INT;
}

SQLField::SQLField( const SQLField& field)
{
	sName = field.sName;
	iType = field.iType;

	switch ( iType)
	{
	case STRING:
		strcpy(uValue.sValue, field.uValue.sValue);
		break;
	case LONG:
		uValue.lValue = field.uValue.lValue;
		break;
	}
}

SQLField::~SQLField()
{
}

String SQLField::getValue()
{
	switch ( iType)
	{
	case STRING:
		return uValue.sValue;
		break;

	case LONG:
		return StringUtils::toString(uValue.lValue);
		break;
	default:
		return uValue.sValue;
		break;

	}
}

