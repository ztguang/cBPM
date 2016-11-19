#include "CommonDefines.h"

#include "EventPolicies.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;
using namespace bOS::XML::Data;

#include "Tracer.h"

EventPolicies::EventPolicies() : XMLObject()
{
	this->init();
}

EventPolicies::EventPolicies(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

EventPolicies::~EventPolicies(void)
{
}

void EventPolicies::init()
{
	consumer.init();
	invocation.init();
}

bool EventPolicies::init (XMLNode* node)
{
	return XMLObject::init(node);
}

bool EventPolicies::parse(XMLAttribute* attribute)
{
	return false;
}

bool EventPolicies::parse(XMLNode* node)
{
	CM_CODEBLOCK(createFromNode)

	if ( !strcmp(node->getName(),XMLEventConsumerPolicy::MAIN_NODE.c_str()) )
    {
		consumer.init(node);
    }
	else if ( !strcmp(node->getName(),XMLEventInvocationPolicy::MAIN_NODE.c_str()) )
	{
		invocation.init(node);
	}
	else
		return false;

	return true;
}

XMLNode* EventPolicies::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = new XMLNode( XMLEventPolicies::MAIN_NODE.c_str(), "" );
	nd->addNode ( consumer.getXMLNode(0) );
	nd->addNode ( invocation.getXMLNode(0) );
    
    return nd;
}

bool EventPolicies::isValid()
{
	return true;
}
