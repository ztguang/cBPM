#include "CommonDefines.h"

#include "ConditionTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Condition;

#include "EvalExpressionAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Condition::Action;

ConditionTask::ConditionTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) : BaseTask(process, task) 
{
	CM_CODEBLOCK(DatabaseTask)

}

ConditionTask::~ConditionTask()
{
	CM_CODEBLOCK(~DatabaseTask)
}

int ConditionTask::execute( )
{
	CM_CODEBLOCK(execute)

	int feRet = BaseTask::execute();

	if ( feRet != FE_OK ) 
	{
		CM_TRACE_DEBUG("Error Executing Task. [" << feRet << "]")
		return feRet;
	}

	EvalExpressionAction* eval = NULL;

	String sScriptType = _task->getBehaviour().getScriptType();
	if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::EVAL_EXPRESSION_TYPE.c_str()) == 0 ) 
	{
		eval = new EvalExpressionAction(_process, _task);
    }
	else
	{
            return FE_TASK_ACTIONTYPE_ERROR;
    }
    
	String sResult = "";
	feRet = eval->action(sResult);
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
    _action = eval;

	return feRet;
}




