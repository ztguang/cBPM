#include "CommonDefines.h"

#include "ManualWorkflowEvent.h"
using namespace WorkflowEngine::Criteria::Event::WorkflowEvent;

String ManualWorkflowEvent::_EventName = "ManualWorkflowEvent";
int ManualWorkflowEvent::_EventID = 204;

ManualWorkflowEvent::ManualWorkflowEvent( Workflow* wf ) : BaseWorkflowEvent( wf, _EventName, _EventID) 
{
}

ManualWorkflowEvent::~ManualWorkflowEvent()
{
}
