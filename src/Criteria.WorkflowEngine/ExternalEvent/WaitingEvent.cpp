#include "CommonDefines.h"

#include "WaitingEvent.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

WaitingEvent::WaitingEvent()  : Event()
{
	this->init();
}

WaitingEvent::WaitingEvent(XMLNode* node) : Event()
{
	XMLObject::init(node);
}

WaitingEvent::~WaitingEvent(void)
{
}

void WaitingEvent::init()
{
	activities.init();
}

bool WaitingEvent::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool WaitingEvent::parse(XMLAttribute* attribute)
{
	return Event::parse (attribute);
}

bool WaitingEvent::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLWaitingActivities::MAIN_NODE.c_str()) )
    {
		activities.init(node);
    }
	else
		return Event::parse(node);

	return true;
}

XMLNode* WaitingEvent::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = Event::getXMLNode(uiHow);
	
	nd->setName (XMLWaitingEvent::MAIN_NODE.c_str());

	nd->addNode ( activities.getXMLNode(uiHow) );
    
    return nd;
}

bool WaitingEvent::isValid()
{
	return true;
}

WaitingActivities& WaitingEvent::getActivities()
{
	return activities;
}

