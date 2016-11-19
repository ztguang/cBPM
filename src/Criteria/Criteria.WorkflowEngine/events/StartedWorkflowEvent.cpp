#include "CommonDefines.h"

#include "StartedWorkflowEvent.h"
using namespace WorkflowEngine::Criteria::Event::WorkflowEvent;

String StartedWorkflowEvent::_EventName = "StartedWorkflowEvent";
int StartedWorkflowEvent::_EventID = 202;

StartedWorkflowEvent::StartedWorkflowEvent( Workflow* wf ) : BaseWorkflowEvent( wf, _EventName, _EventID) 
{
}

StartedWorkflowEvent::~StartedWorkflowEvent()
{
}


