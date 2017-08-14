#include "CommonDefines.h"

#include "EventListener.h"
using namespace WorkflowEngine::Criteria::Event;

EventListener::EventListener( String Name )
{
	_Name = Name;
}

EventListener::~EventListener()
{
}

String EventListener::getName()
{
	return _Name;
}


