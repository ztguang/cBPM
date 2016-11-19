#include "CommonDefines.h"

#include "LoopTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Iteration;

#include "IterationAction.h"
#include "IterationCounterAction.h"
#include "IterationExpressionAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Iteration::Action;

LoopTask::LoopTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) : BaseTask(process, task)
{
}

LoopTask::~LoopTask()
{
}

int LoopTask::execute()
{
	int feRet = BaseTask::execute();
	if ( feRet != FE_OK ) 
		return feRet;

	IterationAction* loopAction = NULL;

	String sScriptType = _task->getBehaviour().getScriptType();
	if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::LOOP_EXPRESSION_TYPE.c_str()) == 0 ) 
	{
		return FE_TASK_ACTIONTYPE_ERROR;
	}
	else if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::LOOP_EXPRESSION_TYPE.c_str()) == 0 ) 
	{
		loopAction = new IterationExpressionAction( _process, _task );
    }
	else
	{
		return FE_TASK_ACTIONTYPE_ERROR;
    }


    String sResult = "";
	feRet = loopAction->action(sResult);
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
    _action = loopAction;

	return feRet;
}