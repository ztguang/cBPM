#include "CommonDefines.h"

#include "Engine.h"
#include "Workflow.h"
#include "WorkflowException.h"
#include "WorkflowManager.h"
#include "EventsManagerThread.h"
using namespace WorkflowEngine::Criteria::Core;

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "ApplicationManager.h" 
#include "ApplicationException.h"
#include "EventsManager.h"
using namespace WorkflowEngine;

#include "bOS.h" 

Engine* Engine::_instance = NULL;

Engine* Engine::instance()
{
	if ( _instance == NULL )
	{
		_instance = new Engine();
	}

	return _instance;
}

void Engine::deinstance()
{
	if ( _instance != NULL )
	{
		delete _instance;
	}
	_instance=NULL;
}

Engine::Engine() 
{
	bOS::XML::XMLHelper::initialize();

    eProducer = new EventMaker("Engine");
    assert(eProducer != NULL);

	DataBaseHelper::instance();
	ApplicationManager::instance();

#ifdef _ADD_EVENTS_MANAGER_H_
	EventsManager::instance();
	eventsManagerThread = new EventsManagerThread(EventsManager::instance());
	eventsManagerThread->start();
#endif 

	WorkflowManager::instance();
}

Engine::~Engine()
{
    if ( eProducer ) 
	{
        delete eProducer;
		eProducer=NULL;
	}

	ApplicationManager::deinstance();
	DataBaseHelper::deinstance();
	WorkflowManager::deinstance();

#ifdef _ADD_EVENTS_MANAGER_H_
	EventsManager::deinstance();
	eventsManagerThread->stopEventManager();
	delete eventsManagerThread;
#endif

	bOS::XML::XMLHelper::terminate();

}

void Engine::startWorkFlow(const char* processID)
{
    CM_CODEBLOCK(startWorkFlow)

    //exectpion are catched from calling method
    execute(processID, false, (const char*)NULL, false);
}

void Engine::startWorkFlowInSynchWay(const char* processID)
{
    CM_CODEBLOCK(startWorkFlowInSynchWay)

    //exectpion are catched from calling method
    execute(processID, false, (const char*)NULL, true);
}

void Engine::restartWorkFlow(const char* processID)
{
    CM_CODEBLOCK(restartWorkFlow)

    //exectpion are catched from calling method
    execute(processID, true, (const char*)NULL, false);
}

void Engine::restartWorkFlowInSynchWay(const char* processID)
{
    CM_CODEBLOCK(restartWorkFlowInSynchWay)

    //exectpion are catched from calling method
    execute(processID, true, (const char*)NULL, true);
}


void Engine::restartWorkFlow(const char* processID, const char *acStatus)
{
    CM_CODEBLOCK(restartWorkFlow)

    //exectpion are catched from calling method
    execute(processID, true, acStatus, false);
}

void Engine::restartWorkFlowInSynchWay(const char* processID, const char *acStatus)
{
    CM_CODEBLOCK(restartWorkFlowInSynchWay)

    //exectpion are catched from calling method
    execute(processID, true, acStatus, true);
}

void Engine::execute(const char* processInstanceID, bool bRestart, const char* acStatus, bool bSynchWay)
{
	CM_CODEBLOCK(execute)

    try
    {
        CM_TRACE_DEBUG( "Searching for Job inside WorkFlows list")
		IWorkflow* wf = WorkflowManager::instance()->find(processInstanceID);
        if ( wf != NULL ) 
        {
            throw EngineException(FE_JOBM_JOB_JUST_PRESENT);
        }
    }
    catch ( WorkflowException &je ) 
    {
        throw EngineException(FE_JOBM_ERROR, je.getMessage().c_str());
    }

	ostrstream ostrErr;
	ostrErr << "Impossible to start Process Id: [" << processInstanceID << "]";

	Workflow* workflow = NULL;
	int iErrorCode=FE_OK;
	
	try
	{
        /*
        ProcessInstance Loading is done by WorkFlow class for Database Connection re-using.
        DB connection is requests inside WorkFlow instance and used otherwise Engine will must to establish 
        a connection and to pass it to WorkFlow instance.
        */
        workflow = new Workflow(processInstanceID);

        if ( bRestart )
		{
            workflow->setRestart();
		}

        workflow->setFather();

        if ( acStatus != (const char*)NULL ) 
		{
            workflow->setBeginTask(String(acStatus));
		}

        //TODO: Add Module Listener
        workflow->addEventListener( &wfListener );
        
        if ( bSynchWay)
		{
			WorkflowManager::instance()->executeJob( workflow, false );
		}
		else
		{
			WorkflowManager::instance()->executeJob( workflow, true );
		}

	} 
    catch ( EngineException& fee )
	{
		ostrErr << "Process not loaded. " << fee.getMessage() << ends;
		iErrorCode = fee.getErrorCode();
	}
	catch (WorkflowException& je)
	{
		ostrErr << "Thread not created. " << je.getMessage() << ends;
		iErrorCode = FE_THREAD_NOTCREATED;
	}

	if ( iErrorCode != FE_OK) 
	{
        if ( workflow )
        {
            try 
            {
                delete workflow;
            }
            catch ( EngineException) 
            {
            }
        }
		throw EngineException(iErrorCode, ostrErr.str());
	}
}

void Engine::execute(const char* processInstanceID, bool bRestart, const char* acStatus, const char* acResultCode, bool bSynchWay)
{
	CM_CODEBLOCK(execute)

    try
    {
        CM_TRACE_DEBUG( "Searching for Job inside WorkFlows list")
		IWorkflow* wf = WorkflowManager::instance()->find(processInstanceID);
        if ( wf != NULL ) 
        {
            throw EngineException(FE_JOBM_JOB_JUST_PRESENT);
        }
    }
    catch ( WorkflowException &je ) 
    {
        throw EngineException(FE_JOBM_ERROR, je.getMessage().c_str());
    }

	ostrstream ostrErr;
	ostrErr << "Impossible to start Process Id: [" << processInstanceID << "]";

	Workflow* workflow = NULL;
	int iErrorCode=FE_OK;
	
	try
	{
        /*
        ProcessInstance Loading is done by WorkFlow class for Database Connection re-using.
        DB connection is requests inside WorkFlow instance and used otherwise Engine will must to establish 
        a connection and to pass it to WorkFlow instance.
        */
        workflow = new Workflow(processInstanceID);

        if ( bRestart )
            workflow->setRestart();

        workflow->setFather();

        if ( acStatus != (const char*)NULL ) 
		{
            workflow->setBeginTask(String(acStatus), String(acResultCode) );
		}

        //TODO: Add Module Listener
        workflow->addEventListener( &wfListener );
        
		if ( bSynchWay)
		{
			WorkflowManager::instance()->executeJob( workflow, false );
		}
		else
		{
			WorkflowManager::instance()->executeJob( workflow, true );
		}
	} 
    catch ( EngineException& fee )
	{
		ostrErr << "Process not loaded. " << fee.getMessage() << ends;
		iErrorCode = fee.getErrorCode();
	}
	catch (WorkflowException& je)
	{
		ostrErr << "Thread not created. " << je.getMessage() << ends;
		iErrorCode = FE_THREAD_NOTCREATED;
	}

	if ( iErrorCode != FE_OK) 
	{
        if ( workflow )
        {
            try 
            {
                delete workflow;
            }
            catch ( EngineException) 
            {
            }
        }
		throw EngineException(iErrorCode, ostrErr.str());
	}
}


std::vector<String> Engine::getNextStatusList(unsigned long idRequest)
{
    CM_CODEBLOCK(getNextStatusList)

    std::vector<String> taskList;

	/*
	long lpID = DataBase::instance()->getProcessAssignToRequest (idRequest);
	WorkflowProcesses::WorkflowProcess* process = DataBase::instance()->getProcessInstance(lpID);
	taskList = process->getNextStatusList();
	delete process;
    */

    return taskList;
}

unsigned long Engine::numberWorkflowRunning()
{
	return WorkflowManager::instance()->getWorkflowCount();
}

std::vector<String> Engine::getWorkflowRunningList()
{
	std::vector<String> sWorkflows;

	WorkflowList wfList = WorkflowManager::instance()->getList();
	unsigned int uiSize = wfList.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Workflow* workflow = (Workflow*)wfList.at(i);
		WorkflowProcesses::WorkflowProcess* process = workflow->getProcess();

		sWorkflows.push_back( process->getName() );
	}

	return sWorkflows;
}

String Engine::executeApplicationApi(const char* acAPI)
{
	CM_CODEBLOCK(executeApplicationApi)

	ApplicationFunction function;
	function.init (acAPI);
	ApplicationFunctionResult* resultFunction = NULL;

	try
    {
		//TODO: memory leak?
		ApplicationFunctionResult* resultFunction = ApplicationManager::instance()->execute(function);
		return resultFunction->getXMLString(0).c_str();
	}
	catch ( ApplicationException& ae)
	{
		CM_TRACE_ERROR( "Error [" << function.getName() << "] is not execute. [" << ae.getMessage() << "]")
    }
	catch ( ChannelException& ce)
	{
		CM_TRACE_ERROR( "Function [" <<  function.getName() << "] is not execute. [" << ce.getMessage() << "]")
    }

	return NULL;
}