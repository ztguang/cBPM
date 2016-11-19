#include "CommonDefines.h"

#include "WaitingActivity.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

WaitingActivity::WaitingActivity() : XMLObject()
{
	this->init();
}

WaitingActivity::WaitingActivity(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

WaitingActivity::~WaitingActivity()
{
}

void WaitingActivity::init()
{
	processId="";
	sActivityName="";
}

bool WaitingActivity::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool WaitingActivity::parse(XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLWaitingActivity::NAME_ATTRIBUTE.c_str()) )
	{
		sActivityName = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLWaitingActivity::PROCESSID_ATTRIBUTE.c_str()) )
	{
		processId = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLWaitingActivity::DATETIME_ATTRIBUTE.c_str()) )
	{
		//TODO: Costruttore per DateTime in modo da essere inizializzato da Stringa.
		//datetime = attribute->getValue();
	}
	else
		return false;

	return true;
}

bool WaitingActivity::parse(XMLNode* node)
{
	if (!strcmp(node->getName(),XMLManagedEventElement::MAIN_NODE.c_str() ))
	{
		managed.init(node);
	}
	else
		return false;

	return true;
}

XMLNode* WaitingActivity::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = new XMLNode( XMLWaitingActivity::MAIN_NODE.c_str(), "" );
	nd->addAttribute ( new XMLAttribute(XMLWaitingActivity::NAME_ATTRIBUTE.c_str(), sActivityName.c_str()) );
	nd->addAttribute ( new XMLAttribute(XMLWaitingActivity::PROCESSID_ATTRIBUTE.c_str(), processId.c_str()) );
	nd->addAttribute ( new XMLAttribute(XMLWaitingActivity::DATETIME_ATTRIBUTE.c_str(), datetime.toString().c_str()) );

	nd->addNode ( managed.getXMLNode(uiHow)) ;

    return nd;
}

bool WaitingActivity::isValid()
{
	return true;
}

String& WaitingActivity::getActivityName()
{
	return sActivityName;
}

void WaitingActivity::setActivityName(const String& sNameValue)
{
	sActivityName = sNameValue;
}

const char* WaitingActivity::getProcessId()
{
	return processId.c_str();
}

void WaitingActivity::setProcessId(const char* value)
{
	processId = value;
}

DateTime& WaitingActivity::getDatetime()
{
	return datetime;
}

void WaitingActivity::setDateTime (const DateTime& datetimeValue)
{
	//TODO: Aggiungere costruttore di copia per DateTime
	//datetime = datetimeValue;

}

void WaitingActivity::setDateTime2Now()
{
	datetime.set2CurrentDateTime();
}

ManagedEventElement& WaitingActivity::getManaged()
{
	return managed;
}

void WaitingActivity::set2Managing()
{
	managed.setManagedStatus(ManagedEventElement::Managing);
}

void WaitingActivity::set2Managed()
{
	managed.setManagedStatus(ManagedEventElement::Managed);
}

bool WaitingActivity::is2Manage()
{
	return managed.getManagedStatus() == ManagedEventElement::UnManaged;
}

bool WaitingActivity::equalTo(bOS::Collections::CollectionEntry* entry)
{
	WaitingActivity* activity = (WaitingActivity*)entry;
	if ( ( strcmp(activity->getProcessId(),this->getProcessId()) == 0  ) &&
		 (strcmp(activity->getActivityName().c_str(), this->getActivityName().c_str()) == 0 ))

	{
		return true;
	}

	return false;
}