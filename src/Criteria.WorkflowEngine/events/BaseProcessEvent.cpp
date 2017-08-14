#include "CommonDefines.h"

#include "BaseProcessEvent.h"
using namespace WorkflowEngine::Criteria::Event::ProcessEvent;

BaseProcessEvent::BaseProcessEvent( WorkflowProcesses::WorkflowProcess* p, String eventName, int eventID )
    : BaseEvent(eventName, eventID)
{

	process = p;
    processID = "";
}

BaseProcessEvent::BaseProcessEvent( const char* pID, String eventName, int eventID ) 
    : BaseEvent(eventName, eventID)
{
    process = NULL;
    processID = pID;
}

BaseProcessEvent::~BaseProcessEvent()
{
}

const char* BaseProcessEvent::getProcessID()
{
    if ( process ) 
    	return process->getProcessId();
    else
		return processID.c_str();
}
