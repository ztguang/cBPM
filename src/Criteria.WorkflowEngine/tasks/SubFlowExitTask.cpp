#include "CommonDefines.h"

#include "SubFlowExitTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Process;

//Action
#include "SubFlowExitAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Process::Action;

SubFlowExitTask::SubFlowExitTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel ) : BaseTask(process, task)
{
	iWorkflowLevel = iLevel;
	bEndTask = (task->getType() == WorkflowProcesses::Activity::END);
}

SubFlowExitTask::~SubFlowExitTask()
{
}

int SubFlowExitTask::execute()
{
	CM_CODEBLOCK(execute)

	int feRet = BaseTask::execute();

	if ( feRet != FE_OK ) 
	{
		CM_TRACE_DEBUG("Error Executing Task. [" << feRet << "]")
		return feRet;
	}

	SubFlowExitAction* subflowAction = NULL;

	subflowAction = new SubFlowExitAction(_process, _task,iWorkflowLevel);

    String sResult = "";
	if ( bEndTask )
	{
		subflowAction->setNotEvaluateAction();
	}

	feRet = subflowAction->action(sResult);

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
    _action = subflowAction;

	return feRet;
}

