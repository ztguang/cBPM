#include "CommonDefines.h"

#include "WAPIApplication.h"
#include "WAPIError.h"

#include "bOS.h"
#include "bOSStringUtils.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

//DataModel
#include "ExtendedAttributes.h"
#include "ExtendedAttribute.h"
using namespace DataManager::Panorama::Common;

#include "Applications.h"
#include "Application.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

//Engine

#include "Engine.h"
using namespace WorkflowEngine::Criteria::Core;

extern "C" ENGINE_API char* executeApi(char* acAPI, Response* response)
{
	CM_CODEBLOCK(executeApi)

	assert (acAPI != NULL);
	response->iCode = 0;
	response->sMsg = "";

	String sResult;
	try
	{
		sResult = Engine::instance()->executeApplicationApi(acAPI);
	}
	catch ( EngineException& wfErr) 
	{
		CM_TRACE_ERROR("Error excuting Api. [" << wfErr.getMessage() << "]")
		response->iCode = 1000;
		strcpy(response->sMsg,wfErr.getMessage().c_str());
	}
	catch ( ... )
	{
		CM_TRACE_ERROR("Error excuting Api.[Unknow Error]")
		response->iCode = 1000;
		response->sMsg = "Unknow Error";
	}

	return StringUtils::toChar(sResult);
}


extern "C" ENGINE_API char* getApplicationForExtendedAttribute(char* acAttributeName, char* acAttributeValue, Response* response)
{
	CM_CODEBLOCK(getApplicationForExtendedAttribute)
	assert (response != NULL);

	Applications vApplications;
	
	try
	{
		DataBaseHelper::instance()->getApplications (vApplications);
	}
	catch (  DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Roles..Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	} 

	Applications vApplications2Ret;
	Application* application = NULL;
	ExtendedAttribute* attribute = NULL;
	unsigned int uiSize = vApplications.size();
	for ( unsigned int i=0; i<uiSize;i++)
	{
		application = (Application*)vApplications.at(i);
		ExtendedAttributes& attributes = application->getExtendedAttributes();
		attribute = attributes.get(acAttributeName, acAttributeValue);

		if ( attribute != NULL)
		{
			XMLNode* node = application->getXMLNode(0);
			vApplications2Ret.add ( new Application(node));
			delete node;
		}
	}

	return StringUtils::toChar(vApplications2Ret.getXMLString(0));
}

extern "C" ENGINE_API char* getApplications(Response* response)
{
	CM_CODEBLOCK(getApplications)
	assert (response != NULL);

	Applications vApplications;
	
	try
	{
		DataBaseHelper::instance()->getApplications (vApplications);
	}
	catch (  DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to retrieve Roles..Err[" << dbErr.getMessage() << "]");
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	} 

	return StringUtils::toChar(vApplications.getXMLString(0));
}