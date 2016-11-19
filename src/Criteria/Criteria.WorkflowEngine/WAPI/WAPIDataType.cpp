#include "CommonDefines.h"

#include "WAPIDataType.h"

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "DataTypes.h"
using namespace DataManager::Panorama::WorkflowDataTypes;

#include "WAPIError.h"

extern "C" ENGINE_API char* getDataTypes(Response* response)
{
	CM_CODEBLOCK(WAPIDataType::getDataTypes)
	assert(response!=NULL);

	DataTypes vDataTypes;

	try
	{
		DataBaseHelper::instance()->getDataTypes (vDataTypes);
	}
	catch ( DBException& dbErr) 
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	}

	String sDataTypes = vDataTypes.getXMLString(0);
	return StringUtils::toChar (sDataTypes);
}

//TODO: Da implementare il getDataType indipendentemente dal getDataTypes.
extern "C" ENGINE_API char* getDataType(char* acDataType, Response* response)
{
	CM_CODEBLOCK(WAPIDataType::getDataType)
	assert(response!=NULL);

	//DataTypes vDataTypes;
	DataType vDataType;
	vDataType.setKey (acDataType);

	try
	{
		//DataBaseHelper::instance()->getDataTypes (vDataTypes);
		DataBaseHelper::instance()->getDataType (vDataType);
	}
	catch ( DBException& dbErr) 
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	}

	/*CM_TRACE_DEBUG("DataTypes Retrieved. Try to search [" << acDataType << "]")
	DataType* dataType = vDataTypes.getDataType (acDataType);

	if ( dataType == 0 )
	{
		CM_TRACE_DEBUG("[" << acDataType << " not Found.")
		response->iCode = WAPIERR_DATATYPE_NOTFOUND;
		response->sMsg = StringUtils::toChar (WAPIERR_DATATYPE_NOTFOUND_DESCR);
		return NULL;
	}

	CM_TRACE_DEBUG("[" << acDataType << " Found.")

	String sDataType = dataType->getXMLString(0);
	*/
	String sDataType = vDataType.getXMLString(0);
	return StringUtils::toChar (sDataType);
}