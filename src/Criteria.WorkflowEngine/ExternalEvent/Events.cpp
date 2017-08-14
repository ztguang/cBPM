#include "CommonDefines.h"

#include "Events.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

Events::Events() : XMLObjectSet()
{
	this->init();
}

Events::Events(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Events::~Events()
{
}

void Events::init()
{
}

bool Events::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool Events::parse(XMLAttribute* attribute)
{
	return false;
}

bool Events::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLEvent::MAIN_NODE.c_str() ) )
    {
		Event* event = new Event(node);
		bOS::Collections::Collection::add((bOS::Collections::CollectionEntry*)event);
    }
	else if ( !strcmp(node->getName(),XMLOccurredEvent::MAIN_NODE.c_str() ) )
    {
		OccurredEvent* event = new OccurredEvent(node);
		bOS::Collections::Collection::add((bOS::Collections::CollectionEntry*)event);
    }
	if ( !strcmp(node->getName(),XMLWaitingEvent::MAIN_NODE.c_str() ) )
    {
		WaitingEvent* event = new WaitingEvent(node);
		bOS::Collections::Collection::add((bOS::Collections::CollectionEntry*)event);
    }
	else
		return false;

	return true;
}

XMLNode* Events::getXMLNode(unsigned int uiHow)
{
	XMLNode* root = new XMLNode( XMLEvents::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	Event* event=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		event = (Event*)(this->at(i));
		root->addNode( event->getXMLNode(uiHow) );
	}
    
    return root;
}

bool Events::isValid()
{
	return true;
}

Event* Events::getEvent(const String& sEventId)
{
	Event event;
	event.setId(sEventId);
	
	return (Event*)bOS::Collections::Collection::get ( (bOS::Collections::CollectionEntry*)&event );
}
