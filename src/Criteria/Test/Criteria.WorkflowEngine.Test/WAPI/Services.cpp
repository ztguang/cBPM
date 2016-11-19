#include "WAPI/WAPI.h"
#include "WAPI/WAPIService.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void GetServices()
{
	CM_CODEBLOCK(GetServices)

	Response* response = new Response();
	char* acRet = getServices(response);
	if ( response->iCode == 0 )
	{
		cout << "Services[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving Services.[" << response->sMsg << "]" << endl;
	}
}

void GetServicesForUser(const char* acUser)
{
	CM_CODEBLOCK(GetServices)

	Response* response = new Response();
	char* acRet = getServicesForUser((char*)acUser, response);
	if ( response->iCode == 0 )
	{
		cout << "Services[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving Services.[" << response->sMsg << "]" << endl;
	}
}

void GetServicesForAttribute(const char* acUser, const char* acAttribute, const char* acValue)
{
	CM_CODEBLOCK(GetServices)

	Response* response = new Response();
	char* acRet = getServicesForExtendedAttribute((char*)acUser, (char*)acAttribute, (char*)acValue, response);
	if ( response->iCode == 0 )
	{
		cout << "Services[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving Services.[" << response->sMsg << "]" << endl;
	}
}

void GetService(const char* acUser, const char* acServiceName)
{
	CM_CODEBLOCK(GetService)

	Response* response = new Response();
	char* acRet = getService((char*)acUser, (char*)acServiceName, response);
	if ( response->iCode == 0 )
	{
		cout << "Services[" << acRet << "]" << endl;
	}
	else
	{
		cout << "Error retrieving Services.[" << response->sMsg << "]" << endl;
	}
}

void AddService(const char* acNewService, const char* acUser, const char* acServiceName)
{
	CM_CODEBLOCK(AddService)

	Response* response = new Response();
	char* acRet = getService((char*)acUser, (char*)acServiceName, response);
	if ( response->iCode == 0 )
	{
		WorkflowServices::Service service(acRet);
		service.setName(acNewService);

		addService((char*)service.getXMLString(0).c_str(), response);

		if ( response->iCode == 0 )
		{
			cout << "Service[" << acNewService << " added."<< endl;
		}
		else
		{
			cout << "Impossible to add Service[" << acNewService << "] Err." << response->sMsg << "]" << endl;
		}
	}
	else
	{
		cout << "Error retrieving Services.[" << response->sMsg << "]" << endl;
	}
}

void DeleteService(const char* acServiceName)
{
	CM_CODEBLOCK(DeleteService)

	Response* response = new Response();
	deleteService((char*)acServiceName, response);
	if ( response->iCode == 0 )
	{
		cout << "Service[" << acServiceName << " deleted."<< endl;
	}
	else
	{
		cout << "Impossible to delete [" << response->sMsg << "]" << endl;
	}
}
	
	