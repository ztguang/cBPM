#include "WAPI/WAPI.h"
#include "WAPI/WAPIActivity.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void GetActivities()
{
	CM_CODEBLOCK(GetActivities)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getActivityList("celentano", response);
	if ( response->iCode == 0 )
	{
		cout << "Activity[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getActivityList Error[" << response->sMsg << "]")
	}
}

void GetAllMyActivities(const char* acOwner)
{
	CM_CODEBLOCK(GetActivities)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getAllMyActivityList((char*)acOwner, response);
	if ( response->iCode == 0 )
	{
		cout << "Activity[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getActivityList Error[" << response->sMsg << "]")
	}
}

void GetAllActivities(const char* acOwner)
{
	CM_CODEBLOCK(GetActivities)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getAllActivityList((char*)acOwner, response);
	if ( response->iCode == 0 )
	{
		cout << "Activity[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getActivityList Error[" << response->sMsg << "]")
	}
}

void GetAllActivitiesByProcess(long lProcessId)
{
	CM_CODEBLOCK(GetAllActivitiesByProcess)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getActivityListByProcess(response, "", lProcessId);
	if ( response->iCode == 0 )
	{
		cout << "Activity[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error[" << response->sMsg << "]" << endl;
		CM_TRACE_ERROR("getActivityList Error[" << response->sMsg << "]")
	}
}