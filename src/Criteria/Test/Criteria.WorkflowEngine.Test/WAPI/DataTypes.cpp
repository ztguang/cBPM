#include "WAPI/WAPI.h"
#include "WAPI/WAPIDataType.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
#include "DataBase/DBException.h"
using namespace DataManager::DataBase;

void GetDataTypes()
{
	CM_CODEBLOCK(GetDataTypes)

	Response* response = new Response();
	char* acRet = getDataTypes(response);
	if ( response->iCode == 0 )
	{
		cout << "DataTypes[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving DataTypes.[" << response->sMsg << "]" << endl;
	}
}

void GetDataType(string sKey, string sCode)
{
	CM_CODEBLOCK(GetDataType)

	WorkflowDataTypes::DataType datatype;
	datatype.setKey ( sKey);

	try
	{
		DataBaseHelper::instance()->getDataType(datatype);
	}
	catch (DBException dbErr)
	{
		cout << "Impossible to retrieve DataType[" << dbErr.getMessage() << "]" << endl;
		return;
	}

	WorkflowDataTypes::DataTypeValue* code = datatype.getDataTypeValues().getValue(sCode);
	if ( code == NULL )
	{
		cout << "Impossible to retrieve code[" << sCode << "]" << endl;
	}
	else
	{
		cout << "Code[" << sCode << "] Value[" << code->getValue() << "]" << endl;
	}
}