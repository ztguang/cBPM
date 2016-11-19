#include "CommonDefines.h"

#include "ApplicationFunctionTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Application;

//Action
#include "ApplicationFunctionAction.h"
#include "ApplicationFunctionActionAttach.h"
using namespace WorkflowEngine::Criteria::BasicTask::Application::Action;

ApplicationFunctionTask::ApplicationFunctionTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) : BaseTask(process, task)
{
}

ApplicationFunctionTask::~ApplicationFunctionTask()
{
}

int ApplicationFunctionTask::execute()
{
	CM_CODEBLOCK(execute)

	int feRet = BaseTask::execute();

	if ( feRet != FE_OK ) 
	{
		CM_TRACE_DEBUG("Error Executing Task. [" << feRet << "]")
		return feRet;
	}

	ApplicationFunctionAction* functionAction = NULL;

	String sScriptType = _task->getBehaviour().getScriptType();
	if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::APPLICATION_API_TYPE.c_str()) == 0 ) 
	{
		CM_TRACE_CODEPATH( "Executing Attach function.")
        functionAction = new ApplicationFunctionActionAttach( _process, _task );
    }
	else
	{
            return FE_TASK_ACTIONTYPE_ERROR;
    }

    String sResult = "";
	feRet = functionAction->action(sResult);

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
    _action = functionAction;

	return feRet;
}

