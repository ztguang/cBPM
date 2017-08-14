#include "CommonDefines.h"

#include "RestartedWorkflowEvent.h"
using namespace WorkflowEngine::Criteria::Event::WorkflowEvent;

String RestartedWorkflowEvent::_EventName = "RestartedWorkflowEvent";
int RestartedWorkflowEvent::_EventID = 203;

RestartedWorkflowEvent::RestartedWorkflowEvent( Workflow* wf ) : BaseWorkflowEvent( wf, _EventName, _EventID) 
{
}

RestartedWorkflowEvent::~RestartedWorkflowEvent()
{
}

//do not remove blank line belove. It's useful for aC++ compiler

