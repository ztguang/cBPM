#include "CommonDefines.h"

#include "EventAction.h"

WorkflowEngine::Criteria::BasicTask::Event::Action::EventAction::EventAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
: BaseAction(process, task)
{
	event = NULL;
}

WorkflowEngine::Criteria::BasicTask::Event::Action::EventAction::~EventAction()
{
	if ( event != NULL )
	{
		delete event;
	}
}

int WorkflowEngine::Criteria::BasicTask::Event::Action::EventAction::evaluateAction()
{
	if ( strcmp(_ActionText.c_str(), BaseAction::ACTION_NONE.c_str() )  == 0 )
	{
		return FE_TASK_TASKACTION_NONE;
	}

	event = new WorkflowEvents::Event();
	event->init (_ActionText.c_str());

	return FE_OK;
}
