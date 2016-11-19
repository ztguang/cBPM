#include "WAPI/WAPI.h"
#include "WAPI/WAPIProcess.h"
#include "WAPI/WAPIActivity.h"
#include "WAPI/WAPIWorkItem.h"

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

#include "bOS/Tracer.h"

#include "DataBase/DataBaseHelper.h"
using namespace DataManager::DataBase;

void CreateNewWorkflowProcess(char* acWorkflowName)
{
	CM_CODEBLOCK(CreateNewWorkflowProcess)

	Response* response = new Response();
	long lProcessId;
	char* acRet = createNewProcessInstance(acWorkflowName, lProcessId, response);
	if ( response->iCode == 0 )
	{
		cout << "WorkflowProcess[" << lProcessId << "]. Created" << endl;
	}
	else
	{
		cout << "Error creating Workflow.[" << response->sMsg << "]" << endl;
	}
}

void StartWorkflowProcess(char* acWorkflowName)
{
	CM_CODEBLOCK(StartWorkflowProcess)

	Response* response = new Response();
	long lProcessId;
	char* acRet = createNewProcessInstance(acWorkflowName, lProcessId, response);
	if ( response->iCode == 0 )
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] Created. ProcessID["<<lProcessId << "]." << endl;
		
		startProcessInstance(lProcessId, response);
		if ( response->iCode == 0 )
		{
			cout << "WorkflowProcess[" << lProcessId << "]. started" << endl;
		}
		else
		{
			cout << "WorkflowProcess[" << lProcessId << "]. NOT STARTED" << endl;
		}
	}
	else
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] ERROR.[" << response->sMsg << "]" << endl;
	}
}

void StartWorkflowProcessAlreadyCreated(long lProcessID)
{
	CM_CODEBLOCK(StartWorkflowProcessAlreadyCreated)

	Response* response = new Response();
	startProcessInstance(lProcessID, response);
	if ( response->iCode == 0 )
	{
		cout << "WorkflowProcess[" << lProcessID << "]. started" << endl;
	}
	else
	{
		cout << "WorkflowProcess[" << lProcessID << "]. NOT STARTED" << endl;
	}
}

void StartProcessAndExecuteManualActivity(char* acWorkflowName)
{
	CM_CODEBLOCK(StartProcessAndExecuteManualActivity)

	WorkflowProcesses::Activity activity;
	Response* response = new Response();
	long lProcessId;
	char* acRet = createNewProcessInstance(acWorkflowName, lProcessId, response);
	if ( response->iCode == 0 )
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] Created. ProcessID["<<lProcessId << "]." << endl;
		startProcessInstance(lProcessId, response);
		if ( response->iCode == 0 )
		{
			cout << "WorkflowProcess[" << lProcessId << "]. started" << endl;

			cout << "Waiting for manual activity" << endl;
			getchar();

			activity.setName ("Manuale");
			activity.setProcessId (lProcessId);
			String sUser="mfarina";
			String sActivity = activity.getXMLString(0);
			acquireActivity((char*)sActivity.c_str(), (char*)sUser.c_str(), response);
			doWorkItem((char*)sActivity.c_str(), (char*)sUser.c_str(), response);
			completeWorkItem((char*)sActivity.c_str(), (char*)sUser.c_str(),"", response);
		}
		else
		{
			cout << "WorkflowProcess[" << lProcessId << "]. NOT STARTED" << endl;
		}
	}
	else
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] ERROR.[" << response->sMsg << "]" << endl;
	}
}

void StartProcessAndExecuteManualActivitySynch(char* acWorkflowName)
{
	CM_CODEBLOCK(StartProcessAndExecuteManualActivity)

	WorkflowProcesses::Activity activity;
	Response* response = new Response();
	long lProcessId;
	char* acRet = createNewProcessInstance(acWorkflowName, lProcessId, response);
	if ( response->iCode == 0 )
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] Created. ProcessID["<<lProcessId << "]." << endl;
		startProcessInstance(lProcessId, response);
		if ( response->iCode == 0 )
		{
			cout << "WorkflowProcess[" << lProcessId << "]. started" << endl;

			cout << "Waiting for manual activity" << endl;
			getchar();

			activity.setName ("Manuale");
			activity.setProcessId (lProcessId);
			String sUser="mfarina";
			String sActivity = activity.getXMLString(0);
			acquireActivity((char*)sActivity.c_str(), (char*)sUser.c_str(), response);
			doWorkItem((char*)sActivity.c_str(), (char*)sUser.c_str(), response);
			completeWorkItemSynch((char*)sActivity.c_str(), (char*)sUser.c_str(),"", response);
		}
		else
		{
			cout << "WorkflowProcess[" << lProcessId << "]. NOT STARTED" << endl;
		}
	}
	else
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] ERROR.[" << response->sMsg << "]" << endl;
	}
}
void StartWorkflowProcessInSynchWay(char* acWorkflowName)
{
	CM_CODEBLOCK(StartWorkflowProcess)

	Response* response = new Response();
	long lProcessId;
	char* acRet = createNewProcessInstance(acWorkflowName, lProcessId, response);
	if ( response->iCode == 0 )
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] Created. ProcessID["<<lProcessId << "]." << endl;
		startProcessInSynchWay(lProcessId, response);
		if ( response->iCode == 0 )
		{
			cout << "WorkflowProcess[" << lProcessId << "]. started" << endl;
		}
		else
		{
			cout << "WorkflowProcess[" << lProcessId << "]. NOT STARTED" << endl;
		}
	}
	else
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] ERROR.[" << response->sMsg << "]" << endl;
	}
}

void StartEnneWorkflowProcess(unsigned int ui, char* acWorkflowName)
{
	for (unsigned int i=0; i<ui; i++)
	{
		StartWorkflowProcess(acWorkflowName);
	}
}

void GetActivityResultList(char* acWorkflowName)
{
	CM_CODEBLOCK(StartWorkflowProcess)

	Response* response = new Response();
	long lProcessId;
	char* acRet = createNewProcessInstance(acWorkflowName, lProcessId, response);
	if ( response->iCode == 0 )
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] Created. ProcessID["<<lProcessId << "]." << endl;
		startProcessInstance(lProcessId, response);
		if ( response->iCode == 0 )
		{
			cout << "WorkflowProcess[" << lProcessId << "]. started. Press a key" << endl;

			getchar();

			acRet = getActivityResultList("Manuale", lProcessId, response);
			if ( response->iCode == 0 )
			{
				cout << acRet << endl;
			}
		}
		else
		{
			cout << "WorkflowProcess[" << lProcessId << "]. NOT STARTED" << endl;
		}
	}
	else
	{
		cout << "WorkflowProcess[" << acWorkflowName <<"] ERROR.[" << response->sMsg << "]" << endl;
	}
}

void GetProcessInstanceAttributes(long lProcessId)
{
	CM_CODEBLOCK(GetProcessInstanceAttributes)

	Response* response = new Response();
	char* acRet = getProcessInstanceAttributes( response, lProcessId);
	if ( response->iCode == 0 )
	{
		cout << "Attributes[" << acRet <<"]" << endl;
	}
	else
	{
		cout << "ERROR.[" << response->sMsg << "]" << endl;
	}
}
