#include "WAPI/WAPI.h"
#include "WAPI/WAPIApplication.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void AllWAPIApplication()
{
	CM_CODEBLOCK(AllWAPIApplication)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getApplications(response);
	if ( response->iCode == 0 )
	{
		cout << "Applications[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getApplications Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	acRet = getApplicationForExtendedAttribute("Type", "DLL", response);
	if ( response->iCode == 0 )
	{
		cout << "Applications[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getApplications Error[" << response->sMsg << "]")
	}

}

void WAPIApplicationContext(char* acAttributeName, char* acAttributeValue)
{
	CM_CODEBLOCK(AllWAPIApplication)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getApplicationForExtendedAttribute(acAttributeName, acAttributeValue, response);
	if ( response->iCode == 0 )
	{
		cout << "Applications[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getApplications Error[" << response->sMsg << "]")
	}

	response->iCode = 0;
	acRet = getApplicationForExtendedAttribute("Type", "DLL", response);
	if ( response->iCode == 0 )
	{
		cout << "Applications[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getApplications Error[" << response->sMsg << "]")
	}

}