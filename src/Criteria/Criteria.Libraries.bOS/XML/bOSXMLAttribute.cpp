#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLAttribute.h"   
using namespace bOS::XML;

XMLAttribute::XMLAttribute()  
{
    sName = "";
    sValue = "";
}

XMLAttribute::XMLAttribute( const char* acName, const char* acValue)
{
    sName = acName;
    sValue = acValue;
}

XMLAttribute::XMLAttribute( const char* acName, const String& _Value)
{
    sName = acName;
    sValue = _Value;
}

XMLAttribute::XMLAttribute( const char* acName, long lValue)
{
	sName = acName;
	sValue = StringUtils::toString (lValue);
}

XMLAttribute::XMLAttribute( const char* acName, int iValue)
{
	sName = acName;
	sValue = StringUtils::toString(iValue);
}

XMLAttribute::XMLAttribute( const char* acName, unsigned int uiValue)
{
	sName = acName;
	sValue = StringUtils::toString(uiValue);
}

XMLAttribute::~XMLAttribute()
{
}

const char* XMLAttribute::getName()
{
    return sName.c_str();
}

const char* XMLAttribute::getValue()
{
    return sValue.c_str();
}

unsigned int XMLAttribute::getUIntValue()
{
	return bOS::CoreString::StringUtils::toInteger(sValue);
}

int XMLAttribute::getIntValue()
{
	return bOS::CoreString::StringUtils::toInteger(sValue);
}

long XMLAttribute::getLongValue()
{
	return bOS::CoreString::StringUtils::toLong(sValue);
}

void XMLAttribute::setName( const char* theName )
{
    sName = theName;
}

void XMLAttribute::setValue( const char* theValue )
{
    sValue = theValue;
}

bool XMLAttribute::equalTo (CollectionEntry* entry)
{
	XMLAttribute* attribute = (XMLAttribute*)entry;
	return ( strcmp(attribute->getName(), this->getName() ) == 0 );
}