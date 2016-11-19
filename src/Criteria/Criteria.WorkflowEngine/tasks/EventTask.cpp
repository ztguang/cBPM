#include "CommonDefines.h"

#include "EventTask.h"
using namespace WorkflowEngine::Criteria::BasicTask::Event;

//Action
#include "EventAction.h"
#include "MakeEventAction.h"
#include "ConsumeEventAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Event::Action;

EventTask::EventTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, Common::FormalParameters& eventParameters ) : BaseTask(process, task)
{
	parametersByOccurredEvent.addParameter(eventParameters);
}

EventTask::~EventTask()
{
}

int EventTask::execute()
{
	CM_CODEBLOCK(execute)

	int feRet = BaseTask::execute();

	if ( feRet != FE_OK ) 
	{
		CM_TRACE_DEBUG("Error Executing Task. [" << feRet << "]")
		return feRet;
	}

	EventAction* eventAction = NULL;

	String sScriptType = _task->getBehaviour().getScriptType();
	if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::EVENT_MAKER_TYPE.c_str()) == 0 ) 
	{
		CM_TRACE_CODEPATH( "Executing Attach Primitive.")
        eventAction = new MakeEventAction( _process, _task );
    }
	else if ( strcmp(sScriptType.c_str(), WorkflowProcesses::XMLScript::EVENT_CONSUMER_TYPE.c_str()) == 0 ) 
	{
		CM_TRACE_CODEPATH( "Executing Attach Primitive.")
        eventAction = new ConsumeEventAction( _process, _task , parametersByOccurredEvent);
    }
	else
	{
            return FE_TASK_ACTIONTYPE_ERROR;
    }

    String sResult = "";
	feRet = eventAction->action(sResult);

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
    _action = eventAction;

	return feRet;
}

