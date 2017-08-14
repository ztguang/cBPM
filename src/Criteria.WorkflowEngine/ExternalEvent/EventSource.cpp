#include "CommonDefines.h"

#include "EventSource.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

EventSource::EventSource() : XMLObject()
{
	this->init();
}

EventSource::EventSource(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

EventSource::~EventSource(void)
{
}

void EventSource::init()
{
	sType="";
	sName="";
}

bool EventSource::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool EventSource::parse(XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLEventSource::TYPE_ATTRIBUTE.c_str() ) )
	{
		sType = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLEventSource::NAME_ATTRIBUTE.c_str() ) )
	{
		sName = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLEventSource::DATETIME_ATTRIBUTE.c_str() ) )
	{
		//TODO: Aggiungere a DateTime la possibilità di essere istanziata da stringa
	}
	else
		return false;

	return true;
}

bool EventSource::parse(XMLNode* node)
{
	return false;
}

XMLNode* EventSource::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = new XMLNode( XMLEventSource::MAIN_NODE.c_str(), "" );
	nd->addAttribute ( new XMLAttribute(XMLEventSource::TYPE_ATTRIBUTE.c_str(), sType.c_str()) );
	nd->addAttribute ( new XMLAttribute(XMLEventSource::NAME_ATTRIBUTE.c_str(), sName.c_str()) );
	nd->addAttribute ( new XMLAttribute(XMLEventSource::DATETIME_ATTRIBUTE.c_str(), datetime.toString().c_str()) );

    return nd;
}

bool EventSource::isValid()
{
	return true;
}

void EventSource::setType(const String& sTypeValue)
{
	sType = sTypeValue;
}
void EventSource::setType(SourceType typeValue)
{
	switch ( typeValue) 
	{
	case Workflow:
		sType = XMLEventSource::WORKFLOW_TYPE;
		break;
	case User:
		sType = XMLEventSource::USER_TYPE;
		break;
	case System:
		sType = XMLEventSource::SYSTEM_TYPE;
		break;
	}
}

String& EventSource::getType()
{
	return sType;
}

void EventSource::setName(const String& sNameValue)
{
	sName = sNameValue;
}

String& EventSource::getName()
{
	return sName;
}

void EventSource::setDateTime(const String& datetimeValue)
{
	//TODO: Prevedere per DateTime il costruttore di copia.
	//datetime = datetimeValue;
}

DateTime& EventSource::getDateTime()
{
	return datetime;
}

void EventSource::setDateTime2Now()
{
	datetime.set2CurrentDateTime();
}