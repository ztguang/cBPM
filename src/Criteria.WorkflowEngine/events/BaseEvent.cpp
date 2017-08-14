#include "CommonDefines.h"

#include "BaseEvent.h"
using namespace WorkflowEngine::Criteria::Event;

BaseEvent::BaseEvent(String _Name, int _ID)
{
	sName = _Name;
    iID = _ID;
	sDateTime = DateTime::getCurrentDateTime().toString();
}

BaseEvent::~BaseEvent()
{
}

String BaseEvent::getName()
{
	return sName;
}

int BaseEvent::getID()
{
	return iID;
}

String BaseEvent::getDateTime()
{
    return sDateTime;
}

