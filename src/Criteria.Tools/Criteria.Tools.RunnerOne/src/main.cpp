#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "Criteria/WAPI.h"
#include "Criteria/WAPIActivity.h"
#include "Criteria/WAPIWorkItem.h"
#include "Criteria/WAPIProcess.h"

#include "Criteria/Activity.h"

static void usage() 
{
	cout << "\nUsage:\n"
		"	Criteria.Tools.RunnerOne <DBFileName> <WorkflowName> [TraceLevel]\n\n"
			"This program invokes criteria workflow engine and execute <WorkflowName>\n"
			"[TraceLevel] is not present the application doesn't write trace"
	<< endl;
}

static int EXIT_OK = 0;
static int EXIT_KO_INIT_CRITERIA = 1;
static int EXIT_KO_END_CRITERIA = 2;
static int EXIT_KO_CREATE_WORKFLOW = 3;
static int EXIT_KO_START_WORKFLOW = 4;
static int EXIT_KO_BADPARAMS = 5;

int main(int argc, char* argv[])
{
	if ( argc <4 )
	{
		usage();	
		exit(EXIT_KO_BADPARAMS);
	}

	
	
	//application exit
	int iExit = EXIT_OK;
	
	cout << "The program will perform the following steps:\n\n"
				"1: Criteria session initialization (only one time)\n"
				"2: Create process instance from template\n"
				"3: Execute process instance just created\n"
				"4: Querying for activity pending\n"
				"5: close criteria session\n\n";

	cout << "Press a Key for beginning................................................" << endl;
	getchar();

	Response* response = new Response();
	response->iCode= 0;

	cout << "Criteria session Initialization.....(look at Executor trace file)" << endl;

	int iTraceLevel = -1;
	if ( argc >= 4 )
		iTraceLevel = atoi(argv[3]);

	if ( iTraceLevel >= 0 )
		CM_SETTING_TO("RunnerOne", iTraceLevel);
	
	InitSessionWithParams(argv[1],response);
	if ( response->iCode != 0 ) 
	{
		cout << "Criteria session Initialization [KO].Error[" << response->sMsg << "]. Exit." << endl;
		exit(EXIT_KO_INIT_CRITERIA);
	}
	cout << "Criteria session Initialization [OK]" << endl;
	
	
	char* lProcessId = new char[50];
	char* acRet = NULL;
	
	cout << "Create process instance from template" << endl;
	createWorkflowProcess((char*)argv[2], lProcessId, response);
	if ( response->iCode == 0 )
	{
		cout << "Create process instance [OK]. Process Instance Id[" << lProcessId << "]" << endl;
		
		{
			CM_CODEBLOCK("Process Execution")
			startProcessInSynchWay(lProcessId, response);
			if ( response->iCode == 0 )
			{
				cout << "Execute process instance [OK]. Process Instance Id[" << lProcessId << "] just started" << endl;
			}
			else
			{
				cout << "Execute process instance [KO]. Process Instance Id[" << lProcessId << "] not started" << endl;
				iExit = EXIT_KO_START_WORKFLOW;
			}
		}
	}
	else
	{
		cout << "Create process instance [KO]. Err[" << response->sMsg << "]" << endl;
		iExit = EXIT_KO_CREATE_WORKFLOW;

	}

	cout << "EndSession......." << endl;
	response->iCode = 0;
	EndSession(response);
	if ( response->iCode == 0 ) 
	{
		cout << "Session Terminated [OK]" << endl;
	}
	else 
	{
		cout << "Terminating [KO].Err[" << response->sMsg << "]" << endl;

		if ( iExit == EXIT_OK) 
			iExit = EXIT_KO_END_CRITERIA;
	}

	exit ( iExit );

	return 0;
}

