#include "WAPI\WAPI.h"
#include "WAPI/WAPI.h"
#include "WAPI/WAPIActivity.h"
#include "WAPI/WAPIWorkItem.h"
#include "WAPI/WAPIProcess.h"
#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include <iostream>
using namespace std;

//+++++++++++++++++++++++++++++++++++++++
#define _INIT_SESSION_
//#define _INIT_WITH_TRACE_
#define _END_SESSION_
//#define _END_WITHOUT_INIT_
//#define _INIT_END_NTIMES_

void TestInitEnd(int);
void InitSessionWithTrace();
void TestEndWithoutInit();
//--------------------------------------

//+++++++++++++++++++++++++++++++++++++++
//#define _ALL_WAPI_USER_
//#define _ALL_WAPI_ROLE_

void AllWAPIUser();
void AllWAPIRole();
//--------------------------------------

//+++++++++++++++++++++++++++++++++++++++
//#define _GET_DATA_TYPES_
void GetDataTypes();
void GetDataType(string, string);
//--------------------------------------

//+++++++++++++++++++++++++++++++++++++++
//#define _GET_WORKFLOWPROCESSES_LIST_
void GetWorkflowProcesses();
//--------------------------------------

//+++++++++++++++++++++++++++++++++++++++
//#define _SERVICES_
void GetServices();
void GetServicesForUser(const char* acUser);
void GetServicesForAttribute(const char* acUser, const char* acAttribute, const char* acValue);
void GetService(const char* acUser, const char* acServiceName);
void AddService(const char* acNewService, const char* acUser, const char* acServiceName);
void DeleteService(const char* acServiceName);
//--------------------------------------

//+++++++++++++++++++++++++++++++++++++++
//#define _ALL_WORKFLOW_PROCESS_INSTANCE_H_
void CreateNewWorkflowProcess(char*);
//--------------------------------------

//+++++++++++++++++++++++++++++++++++++++
//#define _APPLICATIONS_
void AllWAPIApplication();
//#define _APPLICATIONS_CONTEXT_
void WAPIApplicationContext(char* acAttributeName, char* acAttributeValue);
//--------------------------------------

//+++++++++++++++++++++++++++++++++++++++
//#define _START_WORKFLOW_PROCESS_START_
#define _START_WORKFLOW_APPLICATION_
//#define _START_WORKFLOW_PROCESS_20NONE_
//#define _START_10_WORKFLOW_PROCESS_START_
//#define _START_50_WORKFLOW_PROCESS_START_
//#define _START_100_WORKFLOW_PROCESS_START_
//#define _START_500_WORKFLOW_PROCESS_START_
//#define _START_1000_WORKFLOW_PROCESS_START_

//#define _START_WORKFLOW_PROCESS_XML_FILE_
void StartWorkflowProcessAlreadyCreated(long lProcessID);
void StartWorkflowProcess(char*);
void StartEnneWorkflowProcess(unsigned int, char*);

//--------------------------------------

//+++++++++++++++++++++++++++++++++++++++++
//#define _START_WORKFLOW_PROCESS_IN_SYNCH_WAY_
void StartProcessAndExecuteManualActivitySynch(char*);
void StartWorkflowProcessInSynchWay(char*);
//------------------------------------

//Activity - WorkItem
//#define _ASSIGN_DO_COMPLETE_
void StartProcessAndExecuteManualActivity(char*);

#define _GET_ACTIVITIES_H_
void GetAllMyActivities(const char* acOwner);
void GetActivities();
void GetAllActivities(const char* acOwner);
void GetAllActivitiesByProcess(long lProcessId);

//#define _GET_WORKITEMS_H_
void GetWorkItemList();
void GetWorkItemListCompleted();
void GetWorkItemListNoRunning();
void GetWorkItemListNoRunningByProcess();
void GetWorkItemListRunning();
void GetNotify();

//#define _Get_Activity_ResultList_
void GetActivityResultList(char*);

//#define _REPORTS_
void GetReports(long lProcessID);

//#define _ATTRIBUTES_
void GetProcessInstanceAttributes(long lProcessID);

int main(int argc, char* argv[])
{
	CM_SETTING_TO("EngineTest", 7);
	CM_CODEBLOCK(main)

	Response* response = new Response();
	response->iCode= 0;

#ifdef _END_WITHOUT_INIT_
	TestEndWithoutInit();
#endif

#ifdef _INIT_END_NTIMES_
	TestInitEnd(20);
#endif

#ifdef _INIT_WITH_TRACE_
	InitSessionWithTrace();
#endif

#ifdef _INIT_SESSION_
	cout << "InitSession......." << endl;

	

	InitSession(response);
	if ( response->iCode != 0 ) 
	{
		cout << "Initializing [KO].Error[" << response->sMsg << "]. Exit." << endl;
		exit(1);
	}
	cout << "InitSession [OK]" << endl;
#endif

//insert here the test code.
//**********************************************************************************************************************
//************************************************************************************************************************
#ifdef _ALL_WAPI_USER_
	AllWAPIUser();
#endif 

#ifdef _ALL_WAPI_ROLE_
	AllWAPIRole();
#endif 

#ifdef _GET_DATA_TYPES_
	GetDataTypes();
	GetDataType("OK-KO", "Accept");
#endif

#ifdef _GET_WORKFLOWPROCESSES_LIST_
	GetWorkflowProcesses();
#endif 

#ifdef _SERVICES_
	GetServices();
	GetServicesForUser("melina");
	GetServicesForUser("antonio");
	GetServicesForAttribute("melina", "Context", "General");
	GetService("mfarina", "prova");
	GetService("mfarina", "Simple2");
	AddService("Simple4", "mfarina", "Simple2");
	AddService("Simple4", "mfarina", "Simple2");
	DeleteService("Simple5");
	DeleteService("Simple4");
#endif

#ifdef _ALL_WORKFLOW_PROCESS_INSTANCE_H_
	CreateNewWorkflowProcess("StartEnd");
	//CreateNewWorkflowProcess("Assembly Idraulic Lift");
#endif

#ifdef _APPLICATIONS_
	AllWAPIApplication();
#endif

#ifdef _APPLICATIONS_CONTEXT_
	WAPIApplicationContext("Context", "Configuration");
#endif
	
#ifdef _START_WORKFLOW_PROCESS_START_
	for ( int i=0; i<200; i++)
		StartWorkflowProcess("StartEndMessaggio");
	//StartWorkflowProcessAlreadyCreated(1021);
	//StartWorkflowProcess("CCR");
#endif

#ifdef _START_WORKFLOW_PROCESS_XML_FILE_
	StartWorkflowProcess("GetPistoni");
#endif

#ifdef _START_WORKFLOW_APPLICATION_
	StartWorkflowProcess("KPI");
#endif


#ifdef _START_WORKFLOW_PROCESS_20NONE_
	StartWorkflowProcess("20NONE");
#endif

#ifdef _START_10_WORKFLOW_PROCESS_START_
	{
		CM_CODEBLOCK("_START_10_WORKFLOW_PROCESS_START_")
		StartEnneWorkflowProcess(10, "StartEnd");
	}
#endif

#ifdef _START_50_WORKFLOW_PROCESS_START_
	{
		CM_CODEBLOCK("_START_50_WORKFLOW_PROCESS_START_")
		StartEnneWorkflowProcess(50, "StartEnd");
	}
#endif

#ifdef _START_100_WORKFLOW_PROCESS_START_
	{
		CM_CODEBLOCK("_START_100_WORKFLOW_PROCESS_START_")
		StartEnneWorkflowProcess(100, "StartEnd");
	}
#endif 

#ifdef _START_500_WORKFLOW_PROCESS_START_
	{
		CM_CODEBLOCK("_START_500_WORKFLOW_PROCESS_START_")
		StartEnneWorkflowProcess(500, "StartEnd");
	}
#endif

#ifdef _START_1000_WORKFLOW_PROCESS_START_
	{
		CM_CODEBLOCK("_START_1000_WORKFLOW_PROCESS_START_")
		StartEnneWorkflowProcess(1000, "StartEnd");
	}
#endif

#ifdef _START_WORKFLOW_PROCESS_IN_SYNCH_WAY_
	StartWorkflowProcessInSynchWay("StartEnd");
	StartProcessAndExecuteManualActivitySynch("ManualManual");
#endif

#ifdef _ASSIGN_DO_COMPLETE_
	StartProcessAndExecuteManualActivity("manual");
#endif

#ifdef _GET_ACTIVITIES_H_
	GetAllMyActivities("millepiani");
	GetActivities();
	GetAllActivities("millepiani");
	GetAllActivitiesByProcess(206);
#endif

#ifdef _GET_WORKITEMS_H_
	GetWorkItemListNoRunningByProcess();
	cout <<"............." <<endl;
	GetNotify();
	cout <<"............." <<endl;
	GetWorkItemList();
	cout <<"............." <<endl;
	GetWorkItemListCompleted();
	cout <<"............." <<endl;
	GetWorkItemListNoRunning();
	cout <<"............." <<endl;
	GetWorkItemListRunning();
	cout <<"............." <<endl;

#endif

#ifdef _Get_Activity_ResultList_
	GetActivityResultList("manual");
#endif

#ifdef _REPORTS_
	GetReports(22);
#endif

#ifdef _ATTRIBUTES_
	GetProcessInstanceAttributes(106);
#endif

#ifdef _END_SESSION_
	cout << "EndSession......." << endl;
	long lWorkflowRunning;
	do
	{
		lWorkflowRunning= getNumberRunningWorkflow(response);
		if ( response->iCode == 0 )
		{
			cout << "WorkflowRunning[" << lWorkflowRunning << "]" << endl;
		}
		else
		{
			cout << "Error retreiving RunningWorkflow.Err[" << response->sMsg << "]" << endl;
		}
	}
	while ( lWorkflowRunning > 0);

	//EndSession(response);
	if ( response->iCode == 0 ) 
	{
		cout << "Terminating [OK]" << endl;
	}
	else 
	{
		cout << "Terminating [KO].Err[" << response->sMsg << "]" << endl;
	}
#endif
	return 0;
}

