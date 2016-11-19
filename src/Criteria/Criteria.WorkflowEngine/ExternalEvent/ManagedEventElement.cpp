#include "CommonDefines.h"

#include "ManagedEventElement.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

ManagedEventElement::ManagedEventElement() : XMLObject()
{
	this->init();
}

ManagedEventElement::ManagedEventElement(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

ManagedEventElement::~ManagedEventElement(void)
{
}

void ManagedEventElement::init()
{
	managedStatus = ManagedEventElement::UnManaged;
}

bool ManagedEventElement::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool ManagedEventElement::parse(XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLManagedEventElement::DATETIME_ATTRIBUTE.c_str() ) )
	{
		//TODO: Aggiungere a DateTime la possibilità di essere istanziata da stringa
		;
	}
	else if (!strcmp(attribute->getName(), XMLManagedEventElement::STATUS_ATTRIBUTE.c_str() ))
	{
		if ( !strcmp(attribute->getValue(), XMLManagedEventElement::MANAGED_STATUS.c_str() ) )
		{
			managedStatus = ManagedEventElement::Managed;
		}
		else if ( !strcmp(attribute->getValue(), XMLManagedEventElement::UNMANAGED_STATUS.c_str() ) )
		{
			managedStatus = ManagedEventElement::UnManaged;
		}
		else if ( !strcmp(attribute->getValue(), XMLManagedEventElement::MANAGING_STATUS.c_str() ) )
		{
			managedStatus = ManagedEventElement::Managing;
		}
	}
	else
		return false;

	return true;
}

bool ManagedEventElement::parse(XMLNode* node)
{
	return false;
}

XMLNode* ManagedEventElement::getXMLNode(unsigned int uiHow)
{
	XMLNode* nd = new XMLNode( XMLManagedEventElement::MAIN_NODE.c_str(), "" );

	nd->addAttribute ( new XMLAttribute(XMLManagedEventElement::DATETIME_ATTRIBUTE.c_str(), datetime.toString().c_str()) );

	XMLAttribute* managedAttribute = new XMLAttribute();
	managedAttribute->setName(XMLManagedEventElement::STATUS_ATTRIBUTE.c_str());

	switch ( managedStatus) 
	{
	case ManagedEventElement::Managed:
		managedAttribute->setValue(XMLManagedEventElement::MANAGED_STATUS.c_str());
		break;
	case ManagedEventElement::UnManaged:
		managedAttribute->setValue(XMLManagedEventElement::UNMANAGED_STATUS.c_str());
		break;
	case ManagedEventElement::Managing:
		managedAttribute->setValue(XMLManagedEventElement::MANAGING_STATUS.c_str());
		break;
	}

	nd->addAttribute (managedAttribute);

    return nd;
}

bool ManagedEventElement::isValid()
{
	return true;
}

void ManagedEventElement::setManagedStatus(ManagedStatus managedStatusValue)
{
	managedStatus = managedStatusValue;
}

void ManagedEventElement::setDateTime(const String& datetimeValue)
{
	//TODO: Prevedere per DateTime il costruttore di copia.
	//datetime = datetimeValue;
}

DateTime& ManagedEventElement::getDateTime()
{
	return datetime;
}

void ManagedEventElement::setDateTime2Now()
{
	datetime.set2CurrentDateTime();
}

int ManagedEventElement::getManagedStatus()
{
	return managedStatus;
}