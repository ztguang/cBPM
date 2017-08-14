#include "CommonDefines.h"

#include "WAPIService.h"

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

//DB
#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "Roles.h"
#include "Role.h"
#include "Users.h"
#include "User.h"
using namespace DataManager::Panorama::WorkflowParticipantsData;

#include "Services.h"
#include "Service.h"
using namespace DataManager::Panorama::WorkflowServices;

#include "WAPIError.h"

extern "C" ENGINE_API char* getServices( Response* response )
{
	CM_CODEBLOCK(WAPIService::getServices)
	assert(response!=NULL);

	Services vServices;

	try
	{
		DataBaseHelper::instance()->getServices(vServices);
	}
	catch ( DBException& dbErr) 
	{
		response->iCode = WAPIERR_GENERIC_ERROR;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
		return NULL;
	}

	String sServices = vServices.getXMLString(0);
	return StringUtils::toChar (sServices);
}

extern "C" ENGINE_API char* getServicesForUser(char* acUser, Response* response)
{
	CM_CODEBLOCK(WAPIService::getServiceForUser)

	Services vServices;

	try 
	{
		DataBaseHelper::instance()->getServicesForUser(acUser, vServices);
	}
	catch ( DBException dbErr )
	{
		response->iCode = 1000;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
	}

	String sServices = vServices.getXMLString(0);
	return StringUtils::toChar (sServices);
}

extern "C" ENGINE_API char* getServicesForExtendedAttribute(char* acUser, char* acAttributeName, char* acAttributeValue, Response* response)
{
	CM_CODEBLOCK(WAPIService::getServicesForExtendedAttribute)

	Services vServices;
	Services vServices2Add;

	try 
	{
		DataBaseHelper::instance()->getServicesForUser(acUser, vServices);
	}
	catch ( DBException dbErr )
	{
		response->iCode = 1000;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
	}

	unsigned int uiSize = vServices.size();
	Service* service = NULL;
	Common::ExtendedAttribute* attribute = NULL;
	for (unsigned int i=0; i<uiSize; i++)
	{
		Service* service = (Service*)vServices.at(i);
		Common::ExtendedAttributes& attributes = service->getExtendedAttributes();
		attribute = attributes.get(acAttributeName, acAttributeValue);

		if ( attribute != NULL )
		{
			XMLNode* node = service->getXMLNode(0);
			vServices2Add.add ( new Service(node) );
			delete node;
		}
	}

	String sServices = vServices2Add.getXMLString(0);
	return StringUtils::toChar (sServices);
}

extern "C" ENGINE_API char* getService(char* acUser, char* acServiceName, Response* response)
{
	CM_CODEBLOCK(WAPIService::getService)
	assert(response!=NULL);

	Services vServices;

	try 
	{
		DataBaseHelper::instance()->getServicesForUser(acUser, vServices);
	}
	catch ( DBException dbErr )
	{
		response->iCode = 1000;
		response->sMsg = StringUtils::toChar (dbErr.getMessage());
	}

	Service service2Search;
	service2Search.setName(acServiceName);

	Service* service = (Service*)vServices.get(&service2Search);

	if ( service == NULL )
	{
		CM_TRACE_DEBUG("Service[" << acServiceName << "] not found")
		response->iCode = WAPIERR_SERVICE_NOTFOUND;
		response->sMsg = WAPIERR_SERVICE_NOTFOUND_DESCR;

		return NULL;
	}

	String sService = service->getXMLString(0);
	return StringUtils::toChar (sService);
}

extern "C" ENGINE_API void addService(char* acService, Response* response)
{
	CM_CODEBLOCK(WAPIService::addService)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->addService (acService);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to insert Service.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_SERVICE_ALREADY_EXIST;
		response->sMsg = WAPIERR_SERVICE_ALREADY_EXIST_DESCR;
	}
}

extern "C" ENGINE_API void deleteService(char* acServiceName, Response* response)
{
	CM_CODEBLOCK(WAPIService::addService)
	assert(response!=NULL);

	try
	{
		DataBaseHelper::instance()->deleteService (acServiceName);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to insert Service.[" << dbErr.getMessage() << "]")
		response->iCode = WAPIERR_SERVICE_NOT_FOUND;
		response->sMsg = WAPIERR_SERVICE_NOT_FOUND_DESCR;
	}
}

