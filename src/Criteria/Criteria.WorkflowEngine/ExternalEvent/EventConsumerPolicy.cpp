#include "CommonDefines.h"

#include "EventConsumerPolicy.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

EventConsumerPolicy::EventConsumerPolicy() : XMLObject()
{
	this->init();
}

EventConsumerPolicy::EventConsumerPolicy(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

EventConsumerPolicy::~EventConsumerPolicy(void)
{
}

void EventConsumerPolicy::init()
{
	sType = "";
	sValue = "";
}

bool EventConsumerPolicy::init (XMLNode* node)
{
	bool bRet = XMLObject::init(node);

	sValue = node->getValue();

	return bRet;
}

bool EventConsumerPolicy::parse (XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLEventConsumerPolicy::TYPE_ATTRIBUTE.c_str()) )
	{
		sType = attribute->getValue();
	}
	else
		return false;

	return true;
}	

bool EventConsumerPolicy::parse (XMLNode* node)
{
	return false;
}

XMLNode* EventConsumerPolicy::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = new XMLNode( XMLEventConsumerPolicy::MAIN_NODE.c_str(), sValue );
	nd->addAttribute ( new XMLAttribute(XMLEventConsumerPolicy::TYPE_ATTRIBUTE.c_str(), sType.c_str()) );

    return nd;
}

bool EventConsumerPolicy::isValid()
{
	return true;
}

void EventConsumerPolicy::setType(const String& sTypeValue)
{
	sType = sTypeValue;
}

String& EventConsumerPolicy::getType()
{
	return sType;
}

void EventConsumerPolicy::setValue(const String& sValueValue)
{
	sValue = sValueValue;
}

String& EventConsumerPolicy::getValue()
{
	return sValue;
}