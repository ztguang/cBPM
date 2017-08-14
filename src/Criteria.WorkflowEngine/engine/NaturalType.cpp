#include "NaturalType.h"
using namespace WorkflowEngine::Criteria::DataTypes;

using namespace DataManager::Panorama::WorkflowDataTypes;

NaturalType::NaturalType(DataType* _datatype) : IDataType(_datatype)
{
    CM_CODEBLOCK(NaturalType)
}

NaturalType::~NaturalType()
{
    CM_CODEBLOCK(~NaturalType)
}

bool NaturalType::notEqualTo(const String& sCode, const String& sValue)
{
    CM_CODEBLOCK(equalTo)

    if ( sValue.compare ( this->sGetValue(sCode) ) != 0 ) 
    {
        return true;
    }

    return false;
}

bool NaturalType::equalTo(const String& sCode, const String& sValue)
{
    CM_CODEBLOCK(equalTo)

    if ( sValue.compare ( this->sGetValue(sCode) ) == 0 ) 
    {
        return true;
    }

    return false;
}

bool NaturalType::greaterThan(const String& sCode, const String& sValue)
{
    CM_CODEBLOCK(greaterThan)

    if ( sValue.compare (this->sGetValue(sCode)) > 0 ) 
    {
        return true;
    }

    return false;
}

bool NaturalType::lessThan(const String& sCode, const String& sValue)
{
    CM_CODEBLOCK(lessThan)

    if ( sValue.compare ( this->sGetValue(sCode) ) < 0) 
    {
        return true;
    }

    return false;
}

bool NaturalType::greaterThanEqualTo(const String& sCode, const String& sValue)
{
    CM_CODEBLOCK(greaterThanEqualTo)

    if ( sValue.compare ( this->sGetValue(sCode) ) >= 0) 
    {
        return true;
    }

    return false;
}

bool NaturalType::lessThanEqualTo(const String& sCode, const String& sValue)
{
    CM_CODEBLOCK(lessThanEqualTo)

    if ( sValue.compare (this->sGetValue(sCode)) <= 0 ) 
    {
        return true;
    }

    return false;
}

