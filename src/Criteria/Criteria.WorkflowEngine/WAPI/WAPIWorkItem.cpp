#include "CommonDefines.h"

#include "WAPIWorkItem.h"
#include "WAPIError.h"

#include "bOS.h"
#include "bOSStringUtils.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

//Engine
#include "Engine.h"
#include "EngineException.h"
using namespace WorkflowEngine::Criteria::Core;

#include "Activity.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "Grants.h"
#include "Grant.h"
using namespace DataManager::Panorama::Common;

void changeOwnerAndStatusActivity(char* xmlActivity, char* sOwner, char* sStatus, Response* response);

extern "C" ENGINE_API char* setWorkItemAttributes(char* xmlActivity, char* xmlAttributes, char* acOwner,Response* response)
{
	CM_CODEBLOCK(setWorkItemAttributes::setWorkItemAttributes)

	Activity activity;
	activity.init (xmlActivity);

	try
	{
		DataBaseHelper::instance()->getActivity (activity);
	}
	catch ( DBException& dbErr )
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());
		return NULL;
	}

	String sXML;

	if ( strcmp(activity.getOwner().c_str(), acOwner) == 0 )
	{
		Attributes& vAttributes = activity.getAttributes();
		Attributes vAttributes2Set;
		vAttributes2Set.init (xmlAttributes);
		Attributes vAttributesNotFound;

		unsigned int uiSize = vAttributes2Set.size();
		for ( unsigned int i=0; i<uiSize; i++)
		{
			Attribute* attribute2Set = (Attribute*)vAttributes2Set.at(i);
			Attribute* attribute = vAttributes.get(attribute2Set->getName().c_str());

			if ( attribute != NULL ) 
			{
				attribute->setValue(attribute2Set->getValue());
			}
			else
			{
				vAttributesNotFound.add(*attribute2Set);
			}
		}

		//Modify by mfarina on 24/01/06 for manage "Process" in memory
		//DataBaseHelper::instance()->updateAttributes(vAttributes);
		DataBaseHelper::instance()->SetAttributes(vAttributes);
		sXML = vAttributesNotFound.getXMLString(0);
	}
	else
	{
		response->iCode = WAPIERR_USER_NOGRANTS;
		response->sMsg = WAPIERR_USER_NOGRANTS_DESCR;
	}

	return StringUtils::toChar(sXML);
}


extern "C" ENGINE_API char* getWorkItemAttributes(char* xmlActivity, char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemAttributes)

	Activity activity;
	activity.init (xmlActivity);

	try
	{
		DataBaseHelper::instance()->getActivity (activity);
	}
	catch ( DBException& dbErr )
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());
		return NULL;
	}

	String sXML;

	/*if ( strcmp(activity.getOwner().c_str(), acOwner) == 0 )
	{*/
		Attributes& vAttributes = activity.getAttributes();
		sXML = vAttributes.getXMLString(0);
	/*}
	else
	{
		response->iCode = WAPIERR_USER_NOGRANTS;
		response->sMsg = WAPIERR_USER_NOGRANTS_DESCR;
	}*/

	return StringUtils::toChar(sXML);
}

extern "C" ENGINE_API char* getWorkItemList(char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemList)

	Activities vActivities;
	DataBaseHelper::instance()->getActivities (vActivities, "", acOwner, true);

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getWorkItemListByNotify(char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemListByNotify)

	Activities vNotifies;

	DataBaseHelper::instance()->getNotifies (vNotifies, acOwner);

	return StringUtils::toChar (vNotifies.getXMLString (0) );
}

extern "C" ENGINE_API char* getWorkItemListNoRunning(char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemListNoRunning)

	Activities vActivities;
	DataBaseHelper::instance()->getActivities (vActivities, XMLActivity::MANUAL_STATUS, acOwner, true);

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getWorkItemListNoRunningByProcess(char* processId, char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemListNoRunningByProcess)

	Activities vActivities;
	vActivities.setProcessId (processId);
	DataBaseHelper::instance()->getActivities (vActivities, XMLActivity::MANUAL_STATUS, acOwner, true);

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getWorkItemListRunningByProcess(char* processId, char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemListNoRunningByProcess)

	Activities vActivities;
	vActivities.setProcessId (processId);
	DataBaseHelper::instance()->getActivities (vActivities, XMLActivity::RUNNING_STATUS, acOwner, true);

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getWorkItemListRunning(char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemListRunning)

	Activities vActivities;
	DataBaseHelper::instance()->getActivities (vActivities, XMLActivity::RUNNING_STATUS, acOwner, true);

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getWorkItemListRunningNoNotify(char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemListRunningNoNotify)

	Activities vActivities;
	DataBaseHelper::instance()->getActivityRunningNotifies(vActivities, acOwner);

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getWorkItemListCompleted(char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::getWorkItemListCompleted)

	Activities vActivities;
	DataBaseHelper::instance()->getActivities (vActivities, XMLActivity::COMPLETED_STATUS, acOwner, true);

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API void doWorkItem(char* xmlActivity, char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::doWorkItem)

	changeOwnerAndStatusActivity(xmlActivity, "", (char*)XMLActivity::RUNNING_STATUS.c_str(), response);
}

extern "C" ENGINE_API void completeWorkItem(char* xmlActivity, char* acOwner, char* acResultCode, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::completeWorkItem)

	CM_TRACE_DEBUG("Inovked by[" << acOwner << "] Result[" << acResultCode << "]")

	//cout<<"owner="<<acOwner<<" Reesultcode "<<acResultCode<<endl;
	changeOwnerAndStatusActivity(xmlActivity, "", (char*)XMLActivity::COMPLETED_STATUS.c_str(), response);

	/*
	if ( strcmp(acResultCode,"") == 0) 
	{
		response->iCode	= WAPIERR_ACTIVITY_NO_RESULTCODE;
		response->sMsg	=WAPIERR_ACTIVITY_NO_RESULTCODE_DESCR;
		return;
	}
	*/

	Activity activity;
	activity.init (xmlActivity);

	try
	{
		Engine::instance()->execute(activity.getProcessId(), true, activity.getActivityName().c_str(), (const char*)acResultCode, false);
	}
	catch ( EngineException& feErr)
	{
		response->iCode = WAPIERR_PROCESS_NOTEXECUTED;
		response->sMsg=StringUtils::toChar(feErr.getMessage());
	}
}

extern "C" ENGINE_API void completeWorkItemSynch(char* xmlActivity, char* acOwner, char* acResultCode, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::completeWorkItemSynch)

	CM_TRACE_DEBUG("Inovked by[" << acOwner << "] Result[" << acResultCode << "]")

	//cout<<"owner="<<acOwner<<" Reesultcode "<<acResultCode<<endl;
	changeOwnerAndStatusActivity(xmlActivity, "", (char*)XMLActivity::COMPLETED_STATUS.c_str(), response);

	/*
	if ( strcmp(acResultCode,"") == 0) 
	{
		response->iCode	= WAPIERR_ACTIVITY_NO_RESULTCODE;
		response->sMsg	=WAPIERR_ACTIVITY_NO_RESULTCODE_DESCR;
		return;
	}
	*/

	Activity activity;
	activity.init (xmlActivity);

	try
	{
		Engine::instance()->execute(activity.getProcessId(), true, activity.getActivityName().c_str(), (const char*)acResultCode, true);

		/*
		*/
	}
	catch ( EngineException& feErr)
	{
		response->iCode = WAPIERR_PROCESS_NOTEXECUTED;
		response->sMsg=StringUtils::toChar(feErr.getMessage());
	}
}

extern "C" ENGINE_API void stopWorkItem(char* xmlActivity, char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::stopWorkItem)

	changeOwnerAndStatusActivity(xmlActivity, "", (char*)XMLActivity::MANUAL_STATUS.c_str(), response);
}

extern "C" ENGINE_API void reassignWorkItem(char* xmlActivity, char* sOwner, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::reassignWorkItem)
	response->iCode = 0;
	changeOwnerAndStatusActivity(xmlActivity, sOwner, "", response);
}

extern "C" ENGINE_API void releaseWorkItem(char* xmlActivity, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::releaseWorkItem)
	changeOwnerAndStatusActivity(xmlActivity, "", "", response);
}

void changeOwnerAndStatusActivity(char* xmlActivity, char* sOwner, char* sStatus, Response* response)
{
	CM_CODEBLOCK(WAPIWorkItem::changeOwnerAndStatusActivity)

	Activity activity;
	activity.init (xmlActivity);

	try
	{
		DataBaseHelper::instance()->getActivity (activity);
	}
	catch ( DBException& dbErr )
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());
	}

	if ( sOwner != "" )
	{
		CM_TRACE_CODEPATH("Set Owner to[" << sOwner << "]")
		activity.setOwner(sOwner);
	}

	if ( sStatus == XMLActivity::CREATED_STATUS )
	{
		CM_TRACE_CODEPATH("Set Task Status to [" << XMLActivity::CREATED_STATUS << "]")
		activity.setCreated();
	}
	else if ( sStatus == XMLActivity::QUEUED_STATUS )
	{
		CM_TRACE_CODEPATH("Set Task Status to [" << XMLActivity::QUEUED_STATUS << "]")
		activity.setQueued();
	}
    else if ( sStatus == XMLActivity::RUNNING_STATUS )
	{
		CM_TRACE_CODEPATH("Set Task Status to [" << XMLActivity::RUNNING_STATUS << "]")
		activity.setRunning();
	}
    else if ( sStatus == XMLActivity::COMPLETED_STATUS )
	{
		CM_TRACE_CODEPATH("Set Task Status to [" << XMLActivity::COMPLETED_STATUS << "]")
		activity.setCompleted();
	}
    else if ( sStatus == XMLActivity::ERROR_STATUS )
	{
		CM_TRACE_CODEPATH("Set Task Status to [" << XMLActivity::ERROR_STATUS << "]")
		activity.setError();
	}
    else if ( sStatus == XMLActivity::MANUAL_STATUS )
	{
		CM_TRACE_CODEPATH("Set Task Status to [" << XMLActivity::MANUAL_STATUS << "]")
		activity.setManual();
	}

	if ( (sOwner == "") && (sStatus == "") )
	{
		CM_TRACE_CODEPATH("Setting Task Status to [" << XMLActivity::MANUAL_STATUS << "] and Owner to[NULL]")
		activity.setOwner("");
		activity.setManual();
	}

	DataBaseHelper::instance()->updateActivity(&activity, false);
}