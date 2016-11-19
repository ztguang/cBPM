#include <iostream>
#include "fcgio.h"
#include <regex>
#include "json/json.h"

#include "bOSString.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

#include "Tracer.h"

#include "bOSTimer.h"

#include "WAPI.h"
#include "WAPIActivity.h"
#include "WAPIWorkItem.h"
#include "WAPIProcess.h"
#include "WAPIWorkflow.h"
#include "WAPIForms.h"

#include "Activity.h"

using namespace std;


#define CONTENT_TYPE_XML	"Content-type: application/xml\r\n\r\n"
#define CONTENT_TYPE_JSON	"Content-type: application/json\r\n\r\n"

#define HTTP_METHOD_GET		"GET"
#define HTTP_METHOD_POST	"POST"

//criteria
#define CRITERIA_V1_VERSION							"/criteria/release"
#define CRITERIA_V1_PROCESS_TEMPLATES				"/criteria/processes/templates"
#define CRITERIA_V1_PROCESS_TEMPLATES_CREATE		"/criteria/processes/templates/create"
#define CRITERIA_V1_PROCESS_INSTANCES				"/criteria/processes/instances"
#define CRITERIA_V1_PROCESS_INSTANCES_GET			"/criteria/processes/instances/process"
#define CRITERIA_V1_PROCESS_INSTANCES_ATTRIBUTES	"/criteria/processes/instances/process/attributes" //GET-POST
#define CRITERIA_V1_PROCESS_INSTANCES_ACTIVITIES	"/criteria/activities"
#define CRITERIA_V1_WORKITEM_RUN					"/criteria/tasks/execute"
#define CRITERIA_V1_WORKITEM_ATTRIBUTES				"/criteria/tasks/attributes" //GET-POST

//forms
#define FORMS_V1_FORMS								"/forms/templates"
#define FORMS_V1_FORM								"/forms/form"


#define CRITERIA_QUERY_STRING_PROCESS				"process"
#define CRITERIA_QUERY_STRING_ACTIVITY				"activity"
#define CRITERIA_QUERY_STRING_USER					"user"

std::string UriDecode(const std::string & sSrc);
std::string getErrorJsonFormat(int code, std::string message);

#define ERROR_JSON_FORMAT(code, msg)  {\
	ostringstream TRC__os;\
	TRC__os << msg;\
	return getErrorJsonFormat(code, TRC__os.str());\
}

//return 0 if request is managed otherwise 0
int rest(const char* acRequestMethod, const char* acDocumentUri, std::map<std::string, std::string> queryString, char * content_buffer) {

	CM_CODEBLOCK("Managing Rest Call ")
	CM_TRACE_DEBUG("REST Verb[" << acRequestMethod << "] Uri[" << acDocumentUri << "]")
	
	Response* response = new Response();
	response->iCode= 0;

	int iret = 0;

	//processes template list
	if ( strcmp(acDocumentUri, CRITERIA_V1_PROCESS_TEMPLATES) == 0 ) {
		std::cout << CONTENT_TYPE_XML << getWorkflowList(response) << "\r\n";
	}
	else if ( strcmp(acDocumentUri, CRITERIA_V1_VERSION) == 0 ) {
		
		Json::Value root;
		root["name"] = "Criteria Workflow Engine";
		root["release"] = Version();
		Json::StyledWriter styledWriter;
		std::cout << CONTENT_TYPE_JSON << styledWriter.write(root) << "\r\n";
	}
	else if ( strcmp(acDocumentUri, CRITERIA_V1_PROCESS_TEMPLATES_CREATE) == 0 )  {
				
		std::cout << CONTENT_TYPE_JSON;

		std::string processName = queryString["process"];
		char* lProcessId = new char[50]; 
		createWorkflowProcess(processName.c_str(), lProcessId, response);
		if ( response->iCode == 0 )
		{
			startProcessInSynchWay(lProcessId, response);
			if ( response->iCode == 0 )
			{
				Json::Value root;
				root["processId"] = lProcessId;
				root["code"] = 0;

				Json::StyledWriter styledWriter;
				std::cout << styledWriter.write(root) << "\r\n";
			}
			else
			{
				std::cout 
					<< getErrorJsonFormat(1000, StringUtils::format("Execute process instance [KO]. Process Instance Id[%s] not started", lProcessId)) 
					<< endl;
			}
		}
		else
		{
			std::cout 
				<< getErrorJsonFormat(1000, StringUtils::format("Create process instance [KO]. Err[%s]", response->sMsg)) 
				<< endl;
		}
	}
	//get processes instances list
	else if ( strcmp(acDocumentUri, CRITERIA_V1_PROCESS_INSTANCES) == 0 ) {

		std::cout << CONTENT_TYPE_XML;
		string processes = getProcesses(response);
		std::cout << processes << "\r\n";

	}
	//get process 
	else if ( strcmp(acDocumentUri, "/criteria/processes/instances/process") == 0 )  {
				
		std::cout << CONTENT_TYPE_XML;

		std::string processID = queryString["id"];
		char* lProcessId = new char[50];
		std::string result = getProcessInstance((char*)processID.c_str(), response);
		if ( response->iCode == 0 )
		{
			std::cout << result << "\r\n";
		}
		else
		{
			std::cout << "Error Retrieving process process instance [KO]. Err[" << response->sMsg << "]" << endl;
		}

	} 
	//get process attributes
	else if ( strcmp(acDocumentUri, "/criteria/processes/instances/process/attributes") == 0 )  {
				
		std::cout << CONTENT_TYPE_XML;

		std::string processID = queryString["id"];

		if ( strcmp(acRequestMethod,"GET") == 0 ) {
			std::string result = getProcessInstanceAttributes((char*)processID.c_str(),response);
			if ( response->iCode == 0 )
			{
				std::cout << result << "\r\n";
			}
			else
			{
				std::cout << "Error Retrieving process process instance [KO]. Err[" << response->sMsg << "]" << endl;
			}
		} else if ( strcmp(acRequestMethod, "POST" )== 0) {

			std::string result = setProcessInstanceAttributes((char*)processID.c_str(), content_buffer, response);
			if ( response->iCode == 0 )
			{
				std::cout << result << "\r\n";
			}
			else
			{
				std::cout << "Error Retrieving process process instance [KO]. Err[" << response->sMsg << "]" << endl;
			}
		}

	}
	else if ( strcmp(acDocumentUri, "/criteria/activities") == 0 )  {
				
		std::cout << CONTENT_TYPE_XML;

		std::string strUser = queryString["user"];

		std::string activities = getActivityList((char*)strUser.c_str(), response);

		if ( response->iCode == 0 )
		{
			std::cout << activities << "\r\n";
		}
		else
		{
			std::cout << "Error Retrieving activities. Err[" << response->sMsg << "]" << endl;
		}

	}
	else if ( strcmp(acDocumentUri, "/criteria/workitems") == 0 )  {
				
		std::cout << CONTENT_TYPE_XML;

		std::string strUser = queryString["user"];

		std::string activities = getAllMyActivityList((char*)strUser.c_str(), response);

		if ( response->iCode == 0 )
		{
			std::cout << activities << "\r\n";
		}
		else
		{
			std::cout << "Error Retrieving activities. Err[" << response->sMsg << "]" << endl;
		}

	}
	else if ( strcmp(acDocumentUri, CRITERIA_V1_WORKITEM_RUN) == 0 )  {
				
		std::cout << CONTENT_TYPE_XML;

		std::string processID = queryString["id"];
		std::string activityName = queryString["activity"];

		DataManager::Panorama::WorkflowProcesses::Activity activity;
		activity.setName (activityName.c_str());
		activity.setProcessId (processID.c_str());
		String sUser="scenario";
		String sActivity = activity.getXMLString(0);
			

		acquireActivity((char*)sActivity.c_str(), (char*)sUser.c_str(), response);
		doWorkItem((char*)sActivity.c_str(), (char*)sUser.c_str(), response);
		completeWorkItem((char*)sActivity.c_str(), (char*)sUser.c_str(),"", response);

		char* lProcessId = new char[50];
		std::string result = getProcessInstance((char*)processID.c_str(), response);
		if ( response->iCode == 0 )
		{
			std::cout << result << "\r\n";
		}
		else
		{
			std::cout << "Error Retrieving process process instance [KO]. Err[" << response->sMsg << "]" << endl;
		}

	}
	//get task attribute 
	else if ( strcmp(acDocumentUri, "/criteria/tasks/attributes") == 0 )  {
				
		std::cout << CONTENT_TYPE_XML;

		std::string processID = queryString["id"];
		std::string activityName = queryString["activity"];

		DataManager::Panorama::WorkflowProcesses::Activity activity;
		activity.setName (activityName.c_str());
		activity.setProcessId (processID.c_str());
		String sUser="scenario";
		String sActivity = activity.getXMLString(0);
			
		if ( strcmp(acRequestMethod,"GET") == 0 ) {

			std::string strAttributes =  getActivityAttributes((char*)sActivity.c_str(), (char*)sUser.c_str(), response);
			if ( response->iCode == 0 )
			{
				cout << strAttributes << "\r\n";
			}
			else
			{
				cout << "Error Retrieving process process instance [KO]. Err[" << response->sMsg << "]" << endl;
			}
		} else {

			std::string strAttributes =  setActivityAttributes((char*)sActivity.c_str(), content_buffer, (char*)sUser.c_str(), response);
			if ( response->iCode == 0 )
			{
				cout << strAttributes << "\r\n";
			}
			else
			{
				cout << "Error Retrieving process process instance [KO]. Err[" << response->sMsg << "]" << endl;
			}
		}
	}
	//Forms
	else if ( strcmp(acDocumentUri, FORMS_V1_FORMS) == 0 )  {
				
		std::cout << CONTENT_TYPE_XML;

		if ( strcmp(acRequestMethod,"GET") == 0 ) {

			std::string result =  getFormsList(response);
			if ( response->iCode == 0 )
			{
				std::cout << result << "\r\n";
			}
			else
			{
				std::cout << "Error Retrieving process process instance [KO]. Err[" << response->sMsg << "]" << endl;
			}

		} else if ( strcmp(acRequestMethod, "POST" )== 0) {
		}
	}
	else if ( strcmp(acDocumentUri, FORMS_V1_FORM) == 0 )  {
				
		std::cout << CONTENT_TYPE_JSON;

		if ( strcmp(acRequestMethod,"GET") == 0 ) {

			std::string formName = queryString["formName"];
			std::string result =  getForm((char*)formName.c_str(), response);
			if ( response->iCode == 0 )
			{
				std::cout << result << "\r\n";
			}
			else
			{
				std::cout << "Error Retrieving process process instance [KO]. Err[" << response->sMsg << "]" << endl;
			}
		}
		else if ( strcmp(acRequestMethod,"POST") == 0 ) {
			
			std::string formName = queryString["formName"];
			
			setForm((char*)formName.c_str(), content_buffer, response);
			if ( response->iCode == 0 )
			{
				std::cout <<getErrorJsonFormat(0,"OK") << "\r\n";
			}
			else
			{
				std::cout << getErrorJsonFormat(1000,response->sMsg) << endl;
			}

		}
	}
	else {
		iret = 1;
	}

	return iret;
}

std::string getErrorJsonFormat(int code, std::string message) {

	Json::Value root;
	root["code"] = code;
	root["message"] = message;

	Json::StyledWriter styledWriter;
	return styledWriter.write(root);
}
