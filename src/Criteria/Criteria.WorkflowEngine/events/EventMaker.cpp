#include "CommonDefines.h"

#include "EventMaker.h"
using namespace WorkflowEngine::Criteria::Event;

EventMaker::EventMaker( String Name )
{
	_Name = Name;
}

EventMaker::~EventMaker()
{
}

void EventMaker::addEventListener( EventListener* evl )
{
	assert( evl != NULL );
	eList.push_back(evl);
}

void EventMaker::addEventListeners (EventListenerList& evls)
{
	EventListenerList::iterator iEL = evls.begin();
	for ( iEL = eList.begin(); iEL < evls.end(); iEL++)
	{
		addEventListener( *iEL);
	}
}

//void EventMaker::throwEvent( BaseEvent& evt )     //ztg delete
void EventMaker::throwEvent( BaseEvent* evt )
{
	EventListenerList::iterator iEL = eList.begin();
	for ( iEL = eList.begin(); iEL < eList.end(); iEL++)
	{
		(*iEL)->eventAction( evt );
	}
}

