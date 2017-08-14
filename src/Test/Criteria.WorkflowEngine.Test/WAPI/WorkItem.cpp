#include "WAPI/WAPI.h"
#include "WAPI/WAPIWorkItem.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void GetWorkItemList()
{
	CM_CODEBLOCK(GetWorkItemList)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getWorkItemList("antonio", response);
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

void GetWorkItemListCompleted()
{
	CM_CODEBLOCK(getWorkItemListCompleted)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getWorkItemListCompleted("antonio", response);

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
void GetWorkItemListNoRunning()
{
	CM_CODEBLOCK(GetWorkItemListNoRunning)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getWorkItemListNoRunning("antonio", response);
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
void GetWorkItemListNoRunningByProcess()
{
	CM_CODEBLOCK(GetWorkItemListNoRunning)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getWorkItemListNoRunningByProcess(response, "celentano", 499);
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


void GetWorkItemListRunning()
{
	CM_CODEBLOCK(GetWorkItemListRunning)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getWorkItemListRunning("celentano", response);
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

void GetNotify()
{
	CM_CODEBLOCK(GetNotify)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getWorkItemListByNotify("celentano", response);
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

void GetWorkItemsAttribute(string sUser)
{
	CM_CODEBLOCK(GetNotify)
	
	Response* response = new Response();

	response->iCode = 0;
	char* acRet = getWorkItemList("antonio", response);
	if ( response->iCode == 0 )
	{
		DataManager::Panorama::WorkflowProcesses::Activities* activities = new DataManager::Panorama::WorkflowProcesses::Activities();
		activities->init(acRet);

		for ( int i=0; i<activities->size(); i++)
		{
			DataManager::Panorama::WorkflowProcesses::Activity* activity = (DataManager::Panorama::WorkflowProcesses::Activity*)activities->at(i);
			
			/*char* acRet2 = getWorkItemAttributes((char* xmlActivity, char* xmlAttributes, char* acOwner,Response* response);
			if ( response->iCode == 0 )
			{
				cout << "Activity[" << acRet2 << "]" << endl;
			}
			else
			{
				cout << "Error[" << response->sMsg << "]" << endl;
				CM_TRACE_ERROR("getActivityList Error[" << response->sMsg << "]")
			}*/
		}

	}

	
}