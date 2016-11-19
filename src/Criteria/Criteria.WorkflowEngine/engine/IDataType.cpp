#include "IDataType.h"
using namespace WorkflowEngine::Criteria::DataTypes;

using namespace DataManager::Panorama::WorkflowDataTypes;

IDataType::IDataType(DataType* _datatype)
{
    CM_CODEBLOCK(IDataType)
	assert(_datatype != NULL);
    
    datatype = _datatype;
}

IDataType::~IDataType()
{
    CM_CODEBLOCK(~IDataType)
}

String IDataType::sGetValue(const String& sCode)
{
    CM_CODEBLOCK(sGetValue)

    DataTypeValue* rValue = datatype->getDataTypeValues().getValue(sCode);

	if ( rValue == NULL )
	{
		CM_TRACE_CODEPATH( "Code Not Found.")
		return "";
	}

    return rValue->getValue();
}
