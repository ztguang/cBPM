#include "CommonDefines.h"

#include "Event.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

Event::Event() : XMLObject()
{
	this->init();
}

Event::Event(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

Event::~Event()
{
}

void Event::init()
{
	sId="";

	parameters.init();
	actions.init();
	policies.init();
}

bool Event::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool Event::init(const char* acXML)
{
	return XMLObject::init(acXML);
}

bool Event::parse(XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLEvent::ID_ATTRIBUTE.c_str() ) )
	{
		sId = attribute->getValue();
	}
	else
		return false;

	return true;
}
		
bool Event::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),Common::XMLFormalParameters::MAIN_NODE.c_str()) )
    {
		parameters.init(node);
    }
	else if ( !strcmp(node->getName(),XMLEventActions::MAIN_NODE.c_str() ) )
	{
		actions.init(node);
	}
	else if ( !strcmp(node->getName(), XMLEventPolicies::MAIN_NODE.c_str()) )
	{
		policies.init(node);
	}
	else
		return false;

	return true;
}

XMLNode* Event::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = new XMLNode( XMLEvent::MAIN_NODE.c_str(), "" );
	nd->addAttribute ( new XMLAttribute(XMLEvent::ID_ATTRIBUTE.c_str(), sId.c_str()) );

	nd->addNode ( parameters.getXMLNode(0) );
	nd->addNode ( actions.getXMLNode(0) );
	nd->addNode ( policies.getXMLNode(0) );
    
    return nd;
}

bool Event::isValid()
{
	return true;
}

String& Event::getId()
{
	return sId;
}

void Event::setId(const String& sIdValue)
{
	sId = sIdValue;
}

Common::FormalParameters& Event::getParameters()
{
	return parameters;
}

EventActions& Event::getActions()
{
	return actions;
}

EventPolicies& Event::getPolicies()
{
	return policies;
}

bool Event::equalTo(bOS::Collections::CollectionEntry* entry)
{
	Event* event = (Event*)entry;
	if ( strcmp(event->getId().c_str(), this->getId().c_str()) == 0 )
	{
		return true;
	}

	return false;
}