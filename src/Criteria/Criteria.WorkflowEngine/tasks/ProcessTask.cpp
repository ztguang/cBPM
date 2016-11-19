#include "CommonDefines.h"

#include "ProcessTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Process;

//Action
#include "ProcessAction.h"
#include "ProcessActionAttach.h"
using namespace WorkflowEngine::Criteria::BasicTask::Process::Action;

ProcessTask::ProcessTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel ) 
    : BaseTask(process, task) 
{
    iWorkflowLevel = iLevel;
}

ProcessTask::~ProcessTask()
{
}

int ProcessTask::execute()
{
	CM_CODEBLOCK(execute)

	int feRet = BaseTask::execute();
	if ( feRet != FE_OK ) 
	{
		return feRet;
	}

	ProcessAction* processAction = NULL;

	String sScriptType = _task->getBehaviour().getScriptType();
	if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::SUBFLOW_SYNCH_TYPE.c_str()) == 0 ) 
	{
		processAction = new ProcessActionAttach( _process, _task, iWorkflowLevel, true );
    }
	else if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::SUBFLOW_ASYNC_TYPE.c_str()) == 0 ) 
	{
		//processAction = new ProcessActionDetach( _process, _task, iRID, iWorkflowLevel );
		processAction = new ProcessActionAttach( _process, _task, iWorkflowLevel, false );
    }
	else if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::SUBFLOW_SPECIAL_TYPE.c_str()) == 0 ) 
	{
		processAction = new ProcessActionAttach( _process, _task, iWorkflowLevel, true );
    }
	else
	{
            return FE_TASK_ACTIONTYPE_ERROR;
    }

    String sResult = "";
	feRet = processAction->action(sResult);

	CM_TRACE_CODEPATH( "Action is terminated with result.[" << sResult << "] ReturCode[" << feRet << "]")

	switch ( feRet )
	{
	case FE_OK:
	case FE_TASK_TASKACTION_NONE:
		_task->setResult(sResult);
		feRet = FE_OK;
		break;
	default:
		break;

	}
    _action = processAction;

	return feRet;
}


