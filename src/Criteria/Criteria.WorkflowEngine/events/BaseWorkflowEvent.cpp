#include "CommonDefines.h"

#include "Workflow.h"
using namespace WorkflowEngine::Criteria::Core;

#include "BaseWorkflowEvent.h"
using namespace WorkflowEngine::Criteria::Event::WorkflowEvent;

BaseWorkflowEvent::BaseWorkflowEvent( Workflow* wf, String eventName, int eventID )
    : BaseEvent(eventName, eventID)
{
	_WF = wf;
}

BaseWorkflowEvent::~BaseWorkflowEvent()
{
//TODO
}

const char* BaseWorkflowEvent::getProcessID()
{
    return _WF->getProcess()->getProcessId();
}


