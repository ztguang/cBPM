#include "CommonDefines.h"

#include "CreatedProcessEvent.h"
using namespace WorkflowEngine::Criteria::Event::ProcessEvent;

String CreatedProcessEvent::_EventName = "CreatedProcessEvent";
int CreatedProcessEvent::_EventID = 102;

CreatedProcessEvent::CreatedProcessEvent( const char* pID ) : BaseProcessEvent(pID, _EventName, _EventID) 
{
}

CreatedProcessEvent::CreatedProcessEvent( WorkflowProcesses::WorkflowProcess* p ) : BaseProcessEvent(p, _EventName, _EventID) 
{
}

CreatedProcessEvent::~CreatedProcessEvent()
{
}

