#include "CommonDefines.h"

#include "OccurredEvent.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

OccurredEvent::OccurredEvent()  : Event()
{
	this->init();
}

OccurredEvent::OccurredEvent(XMLNode* node) : Event()
{
	XMLObject::init(node);
}

OccurredEvent::~OccurredEvent(void)
{
}

void OccurredEvent::init()
{
	source.init();
	managed.init();
}

bool OccurredEvent::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool OccurredEvent::parse(XMLAttribute* attribute)
{
	return Event::parse (attribute);
}

bool OccurredEvent::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLEventSource::MAIN_NODE.c_str() ) )
	{
		source.init(node);
	}
	else if (!strcmp(node->getName(),XMLManagedEventElement::MAIN_NODE.c_str() ))
	{
		managed.init(node);
	}
	else
		return Event::parse(node);

	return true;
}

XMLNode* OccurredEvent::getXMLNode(unsigned int uiHow)
{

	XMLNode* nd = Event::getXMLNode(uiHow);
	
	nd->setName (XMLOccurredEvent::MAIN_NODE.c_str());

	nd->addNode ( source.getXMLNode(uiHow) );
	nd->addNode ( managed.getXMLNode(uiHow)) ;
    
    return nd;
}

bool OccurredEvent::isValid()
{
	return true;
}

EventSource& OccurredEvent::getSource()
{
	return source;
}

ManagedEventElement& OccurredEvent::getManaged()
{
	return managed;
}

void OccurredEvent::set2Managing()
{
	managed.setManagedStatus(ManagedEventElement::Managing);
}

void OccurredEvent::set2Managed()
{
	managed.setManagedStatus(ManagedEventElement::Managed);
}