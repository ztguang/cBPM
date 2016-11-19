
#include "CommonDefines.h"
#include "ErrorWorkflowEvent.h"
using namespace WorkflowEngine::Criteria::Event::WorkflowEvent;

String ErrorWorkflowEvent::_EventName = "ErrorWorkflowEvent";
int ErrorWorkflowEvent::_EventID = 205;

ErrorWorkflowEvent::ErrorWorkflowEvent( Workflow* wf ) : BaseWorkflowEvent( wf, _EventName, _EventID) 
{
}

ErrorWorkflowEvent::~ErrorWorkflowEvent()
{
}


