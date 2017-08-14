#include "CommonDefines.h"

#include "EventInvocationPolicy.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

EventInvocationPolicy::EventInvocationPolicy() : XMLObject()
{
	this->init();
}

EventInvocationPolicy::EventInvocationPolicy(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

EventInvocationPolicy::~EventInvocationPolicy()
{
}

void EventInvocationPolicy::init()
{
	sType = "";
	sValue = "";
}

bool EventInvocationPolicy::init (XMLNode* node)
{
	bool bRet = XMLObject::init(node);

	sValue = node->getValue();

	return bRet;
}

bool EventInvocationPolicy::parse (XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLEventInvocationPolicy::TYPE_ATTRIBUTE.c_str()) )
	{
		sType = attribute->getValue();
	}
	else
		return false;

	return true;
}	

bool EventInvocationPolicy::parse (XMLNode* node)
{
	return false;
}	

XMLNode* EventInvocationPolicy::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = new XMLNode( XMLEventInvocationPolicy::MAIN_NODE.c_str(), sValue );
	nd->addAttribute ( new XMLAttribute(XMLEventInvocationPolicy::TYPE_ATTRIBUTE.c_str(), sType.c_str()) );

    return nd;
}

bool EventInvocationPolicy::isValid()
{
	return true;
}

void EventInvocationPolicy::setType(const String& sTypeValue)
{
	sType = sTypeValue;
}

String& EventInvocationPolicy::getType()
{
	return sType;
}

void EventInvocationPolicy::setValue(const String& sValueValue)
{
	sValue = sValueValue;
}

String& EventInvocationPolicy::getValue()
{
	return sValue;
}