#include "CommonDefines.h"

#include "StartingWorkflowEvent.h"
using namespace WorkflowEngine::Criteria::Event::WorkflowEvent;

String StartingWorkflowEvent::_EventName = "StartingWorkflowEvent";
int StartingWorkflowEvent::_EventID = 201;

StartingWorkflowEvent::StartingWorkflowEvent( Workflow* wf ) : BaseWorkflowEvent(wf, _EventName, _EventID) 
{
}

StartingWorkflowEvent::~StartingWorkflowEvent()
{
}

//do not remove blank line belove. It's useful for aC++ compiler
