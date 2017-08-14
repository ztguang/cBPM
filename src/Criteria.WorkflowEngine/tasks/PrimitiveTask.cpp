#include "CommonDefines.h"

#include "PrimitiveTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Primitive;

//Action
#include "PrimitiveAction.h"
#include "PrimitiveActionAttach.h"
#include "PrimitiveActionDetach.h"
using namespace WorkflowEngine::Criteria::BasicTask::Primitive::Action;

PrimitiveTask::PrimitiveTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) : BaseTask(process, task)
{
}

PrimitiveTask::~PrimitiveTask()
{
}

int PrimitiveTask::execute()
{
	CM_CODEBLOCK(execute)

	int feRet = BaseTask::execute();

	if ( feRet != FE_OK ) 
	{
		CM_TRACE_DEBUG("Error Executing Task. [" << feRet << "]")
		return feRet;
	}

	PrimitiveAction* primitiveAction = NULL;

	String sScriptType = _task->getBehaviour().getScriptType();
	if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::API_SYNCH_TYPE.c_str()) == 0 ) 
	{
		CM_TRACE_CODEPATH( "Executing Attach Primitive.")
		primitiveAction = new PrimitiveActionAttach( _process, _task );
    }
	else if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::API_ASYNC_TYPE.c_str()) == 0 ) 
	{
		CM_TRACE_CODEPATH( "Executing Detach Primitive.")
		primitiveAction = new PrimitiveActionDetach( _process, _task);
    }
	else
	{
            return FE_TASK_ACTIONTYPE_ERROR;
    }

    String sResult = "";
	feRet = primitiveAction->action(sResult);

	CM_TRACE_CODEPATH( "Action is terminated with result.[" << sResult << "] ReturnCode[" << feRet << "]")

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
    _action = primitiveAction;

	return feRet;
}

