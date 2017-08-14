#include "CommonDefines.h"

#include "WAPIActivity.h"
#include "WAPIError.h"

#include "bOS.h"
#include "bOSStringUtils.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "Activity.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "Grants.h"
#include "Grant.h"
using namespace DataManager::Panorama::Common;

extern "C" ENGINE_API char* getActivityLog(char* xmlActivity, char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getActivityLog)
	response->iCode = 0;

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

	//no check Grants. assignActivity is invoked only by Administrator.
	Grants& grants = activity.getGrants();
	if ( DataBaseHelper::instance()->CheckGrant (grants, acUser,  XMLGrant::VISIBLE_TYPE.c_str()) )
	//if ( grants.check (acUser, NULL, XMLGrant::VISIBLE_TYPE.c_str()) )
	{
		Log& log = activity.getLog();
		sXML = log.getXMLString(0);
	}
	else
	{
		response->iCode = WAPIERR_USER_NOGRANTS;
		response->sMsg = WAPIERR_USER_NOGRANTS_DESCR;
	}

	return StringUtils::toChar(sXML);
}

extern "C" ENGINE_API char* getActivityHistoryLog(char* xmlActivity, char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getActivityHistoryLog)
	response->iCode = 0;

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

	//no check Grants. assignActivity is invoked only by Administrator.
	Grants& grants = activity.getGrants();
	if ( DataBaseHelper::instance()->CheckGrant (grants, acUser,  XMLGrant::VISIBLE_TYPE.c_str()) )
	//if ( grants.check (acUser, NULL, XMLGrant::VISIBLE_TYPE.c_str()) )
	{
		Logs& logs = activity.getLogs();
		sXML = logs.getXMLString(0);
	}
	else
	{
		response->iCode = WAPIERR_USER_NOGRANTS;
		response->sMsg = WAPIERR_USER_NOGRANTS_DESCR;
	}

	return StringUtils::toChar(sXML);
}

extern "C" ENGINE_API char* getAttributesFromActivity(char* lProcessID, char* acActivityName, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getAttributesFromActivity)

	WorkflowRelevantData::Attributes vAttributes;
	vAttributes.setProcessId(lProcessID);
	vAttributes.setActivityId(acActivityName);
	DataBaseHelper::instance()->getAttributes(vAttributes);

	String sXML = vAttributes.getXMLString(0);

	return StringUtils::toChar(sXML);
}

extern "C" ENGINE_API char* getActivityAttributes(char* xmlActivity, char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getActivityAttributes)
	response->iCode = 0;

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

	//no check Grants. assignActivity is invoked only by Administrator.
	Grants& grants = activity.getGrants();

	bool bGranted = DataBaseHelper::instance()->CheckGrant (grants, acUser, XMLGrant::VISIBLE_TYPE.c_str());
	if ( bGranted )
	{
		Attributes& vAttributes = activity.getAttributes();
		sXML = vAttributes.getXMLString(0);
	}
	else
	{
		response->iCode = WAPIERR_USER_NOGRANTS;
		response->sMsg = WAPIERR_USER_NOGRANTS_DESCR;
	}

	return StringUtils::toChar(sXML);
}

extern "C" ENGINE_API char* setActivityAttributes(char* xmlActivity, char* xmlAttributes, char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::setActivityAttributes)
	response->iCode = 0;

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

	//no check Grants. assignActivity is invoked only by Administrator.
	Grants& grants = activity.getGrants();
	if ( DataBaseHelper::instance()->CheckGrant (grants, acUser,  XMLGrant::EXECUTION_TYPE.c_str()) )
	//if ( grants.check (acUser, NULL, XMLGrant::EXECUTION_TYPE.c_str()) )
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

extern "C" ENGINE_API char* getActivityList(char* acUser,Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getActivityList)
	response->iCode = 0;

	Activities vActivities;

	DataBaseHelper::instance()->getActivities (vActivities, XMLActivity::MANUAL_STATUS, acUser, false);
	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getAllActivityList(char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getAllActivityList)
	response->iCode = 0;

	Activities vActivities;

	DataBaseHelper::instance()->getAllActivities (vActivities, acUser, true);
	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getAllMyActivityList(char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getAllMyActivityList)
	response->iCode = 0;

	Activities vActivities;
								
	DataBaseHelper::instance()->getAllMyActivities (vActivities, acUser);
	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getActivitiesByProcess(char* lProcessId, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getActivityListByProcess)
	CM_TRACE_DEBUG("1")
	response->iCode = 0;

	Activities vActivities;
	vActivities.setProcessId (lProcessId);
	CM_TRACE_DEBUG("2")
	DataBaseHelper::instance()->getActivities (vActivities, XMLActivity::MANUAL_STATUS, "", false);
	CM_TRACE_DEBUG("4")

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API char* getActivityListByProcess(char* lProcessId, char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::getActivityListByProcess)
		CM_TRACE_DEBUG("1")
	response->iCode = 0;

	Activities vActivities;
	vActivities.setProcessId (lProcessId);
	CM_TRACE_DEBUG("2")
	DataBaseHelper::instance()->getActivities (vActivities, XMLActivity::MANUAL_STATUS, acUser, false);
	CM_TRACE_DEBUG("4")

	return StringUtils::toChar (vActivities.getXMLString (0) );
}

extern "C" ENGINE_API void acquireActivity(char* xmlActivity, char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::acquireActivity)
	response->iCode = 0;

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

	String sXML;

	//no check Grants. assignActivity is invoked only by Administrator.
	Grants& grants = activity.getGrants();
	if ( DataBaseHelper::instance()->CheckGrant (grants, acOwner,  XMLGrant::EXECUTION_TYPE.c_str()) )
	{
		CM_TRACE_DEBUG("User granted for execution.")
		activity.setOwner (acOwner);

		//TODO: Concurrent Access.
		try
		{
			//DataBaseHelper::instance()->updateActivityCheckStatus (&activity, XMLActivity::QUEUED_STATUS);
			DataBaseHelper::instance()->updateActivityNoOwner(&activity);
		}
		catch ( DBException& dbErr)
		{
			if ( !strcmp(dbErr.getMessage().c_str(), DB_RECORD_NOT_FOUND.c_str() ) )
			{
				CM_TRACE_ERROR("Impossible to acquire Activty. It's already assigned another user.")
				response->iCode = WAPIERR_ACTIVITY_NOTQUEUED;
				response->sMsg = StringUtils::toChar(WAPIERR_ACTIVITY_NOTQUEUED_DESCR);
			}
			else
			{
				CM_TRACE_ERROR("DBError[" << dbErr.getMessage() << "]")
				response->iCode = WAPIERR_ACTIVITY;
				response->sMsg = StringUtils::toChar(dbErr.getMessage());
			}
		}
	}
	else
	{
		response->iCode = WAPIERR_USER_NOGRANTS;
		response->sMsg = WAPIERR_USER_NOGRANTS_DESCR;
	}
}

extern "C" ENGINE_API void assignActivity(char* xmlActivity, char* acOwner, Response* response)
{
	CM_CODEBLOCK(WAPIActivity::assignActivity)
	response->iCode = 0;

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

	String sXML;

	activity.setOwner (acOwner);

	try
	{
		DataBaseHelper::instance()->updateActivity (&activity, false);
	}
	catch ( DBException& dbErr)
	{
		CM_TRACE_ERROR("DBError[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_ACTIVITY;
		response->sMsg = StringUtils::toChar(dbErr.getMessage());
	}
}

