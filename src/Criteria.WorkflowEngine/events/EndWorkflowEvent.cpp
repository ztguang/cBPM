#include "CommonDefines.h"

#include "EndWorkflowEvent.h"
using namespace WorkflowEngine::Criteria::Event::WorkflowEvent;

String EndWorkflowEvent::_EventName = "EndWorkflowEvent";
int EndWorkflowEvent::_EventID = 206;

EndWorkflowEvent::EndWorkflowEvent( Workflow* wf ) : BaseWorkflowEvent( wf, _EventName, _EventID) 
{
}

EndWorkflowEvent::~EndWorkflowEvent()
{
}
