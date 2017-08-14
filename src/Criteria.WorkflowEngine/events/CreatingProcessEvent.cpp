#include "CommonDefines.h"

#include "CreatingProcessEvent.h"
using namespace WorkflowEngine::Criteria::Event::ProcessEvent;

String CreatingProcessEvent::_EventName = "CreatingProcessEvent";
int CreatingProcessEvent::_EventID = 101;

CreatingProcessEvent::CreatingProcessEvent( const char* pID ) : BaseProcessEvent(pID, _EventName, _EventID) 
{
}

CreatingProcessEvent::CreatingProcessEvent( WorkflowProcesses::WorkflowProcess* p ) : BaseProcessEvent(p, _EventName, _EventID) 
{
}

CreatingProcessEvent::~CreatingProcessEvent()
{
}

