#include "CommonDefines.h"

#include "EMailTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Mail;

//Action
#include "EMailAction.h"
#include "EMailActionSmtp.h"
using namespace WorkflowEngine::Criteria::BasicTask::Mail::Action;

EMailTask::EMailTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) : BaseTask(process, task)
{
}

EMailTask::~EMailTask()
{
}

int EMailTask::execute()
{
	CM_CODEBLOCK(execute)

	int feRet = BaseTask::execute();

	if ( feRet != FE_OK ) 
	{
		CM_TRACE_DEBUG("Error Executing Task. [" << feRet << "]")
		return feRet;
	}

	EMailAction* emailAction = NULL;

	String sScriptType = _task->getBehaviour().getScriptType();
	if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::EMAIL_SMTP_TYPE.c_str()) == 0 ) 
	{
		emailAction = new EMailActionSmtp( _process, _task );
    }
	else
	{
            return FE_TASK_ACTIONTYPE_ERROR;
    }

    String sResult = "";
	feRet = emailAction->action(sResult);

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
    _action = emailAction;

	return feRet;
}

