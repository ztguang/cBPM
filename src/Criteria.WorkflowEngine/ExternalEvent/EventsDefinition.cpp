#include "CommonDefines.h"

#include "EventsDefinition.h"
#include "EventContext.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

EventsDefinition::EventsDefinition() : XMLObjectSet()
{
	this->init();
}

EventsDefinition::EventsDefinition(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

EventsDefinition::~EventsDefinition()
{
}
void EventsDefinition::init()
{
}

bool EventsDefinition::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool EventsDefinition::parse(XMLAttribute* attribute)
{
	return false;
}
bool EventsDefinition::parse(XMLNode* node)
{
    if ( !strcmp(node->getName(),XMLEventContext::MAIN_NODE.c_str()) )
    {
		EventContext* context = new EventContext(node);
		bOS::Collections::Collection::add((bOS::Collections::CollectionEntry*)context);
    }
	else
		return false;

	return true;
}

XMLNode* EventsDefinition::getXMLNode(unsigned int uiHow)
{
	XMLNode* root = new XMLNode( XMLEventsDefinition::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	EventContext* context=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		context = (EventContext*)(this->at(i));
		root->addNode( context->getXMLNode(uiHow) );
	}
    
    return root;
}

bool EventsDefinition::isValid()
{
	return true;
}

Event* EventsDefinition::getEvent(const String& sEventId)
{
	int iPos = sEventId.find(".");

	if ( iPos < 0 )
	{
		return NULL;
	}
	

	String sEventContext = sEventId.substr(0, iPos);
	EventContext context2Search;
	context2Search.setName (sEventContext);

	EventContext* context = (EventContext*)bOS::Collections::Collection::get ( (bOS::Collections::CollectionEntry*)&context2Search );
	if ( context == NULL )
	{
		return NULL;
	}

	return context->getEvent(sEventId.substr(iPos+1));
}
