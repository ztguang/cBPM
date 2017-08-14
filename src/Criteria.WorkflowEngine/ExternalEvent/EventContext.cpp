#include "CommonDefines.h"

#include "EventContext.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

EventContext::EventContext() : XMLObjectSet()
{
	this->init();
}

EventContext::EventContext(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

EventContext::~EventContext()
{
}

void EventContext::init()
{
	sName="";
	events.init();
}

bool EventContext::parse (XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLEventContext::NAME_ATTRIBUTE.c_str()) )
	{
		sName = attribute->getValue();
	}
	else
		return false;

	return true;
}

bool EventContext::parse (XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLEvents::MAIN_NODE.c_str() ) )
    {
		events.init(node);
    }
	else if ( !strcmp(node->getName(),XMLEventContext::MAIN_NODE.c_str()) )
    {
		EventContext* context = new EventContext(node);
		bOS::Collections::Collection::add ( (bOS::Collections::CollectionEntry*)context);
    }
	else
		return false;

	return true;
}

XMLNode* EventContext::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = new XMLNode( XMLEventContext::MAIN_NODE.c_str(), "" );
	nd->addAttribute ( new XMLAttribute(XMLEventContext::NAME_ATTRIBUTE.c_str(), sName.c_str()) );

	nd->addNode ( events.getXMLNode(uiHow) );

    unsigned int uiSize=this->size();
	EventContext* context=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		context = (EventContext*)(this->at(i));
		nd->addNode( context->getXMLNode(uiHow) );
	}
    
    return nd;
}

bool EventContext::isValid()
{
	return true;
}

String& EventContext::getName()
{
	return sName;
}

void EventContext::setName(const String& sNameValue)
{
	sName = sNameValue;
}

Event* EventContext::getEvent(const String& sEventId)
{
	int iPos = sEventId.find(".");

	if ( iPos < 0 )
	{
		return events.getEvent(sEventId);
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

bool EventContext::equalTo(bOS::Collections::CollectionEntry* entry)
{
	EventContext* context = (EventContext*)entry;

	if ( strcmp( context->getName().c_str(), this->getName().c_str()) == 0 )
		return true;

	return false;
}