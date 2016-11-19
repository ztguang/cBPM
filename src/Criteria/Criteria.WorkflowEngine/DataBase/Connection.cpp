#include "CommonDefines.h"

#include "Connection.h"
using namespace DataManager::Panorama::DataBase;

Connection::Connection() : XMLObject()
{
}

Connection::Connection( XMLNode* node ) : XMLObject()
{
	//Connection is base class and so the init methods must be invoked from derived class
	//otherwise derived class not never invoke its init method. 
	//this->init(node);
}

Connection::~Connection()
{
}

void Connection::init()
{
	sId="";
	sType="";

	idType=0;

	poolManager.init();
	objectManager.init();
}

bool Connection::init(XMLNode*node)
{
	return XMLObject::init(node);
}

bool Connection::parse( XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(), XMLConnection::ID_ATTRIBUTE.c_str() ) == 0 )
	{
		sId = attribute->getValue();
	}
	else if ( strcmp(attribute->getName(), XMLConnection::TYPE_ATTRIBUTE.c_str() ) == 0 )
	{
		sType = attribute->getValue();
	}
	else
	{
		return false;
	}

	return true;
}

bool Connection::parse( XMLNode* node)
{
	if ( strcmp(node->getName(),XMLPoolManager::MAIN_NODE.c_str()) == 0 )
	{
        poolManager.init(node);
	}
	else if ( strcmp(node->getName(),XMLDataBaseObjectManager::MAIN_NODE.c_str()) == 0 )
	{
		objectManager.init(node);
	}
	else
		return false;
        
	return true;
}

XMLNode* Connection::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(Connection::getXmlNode)
    
    XMLNode* node = new XMLNode( "", "" );

	node->addAttribute ( new XMLAttribute(XMLConnection::ID_ATTRIBUTE.c_str(), sId) );
	node->addAttribute ( new XMLAttribute(XMLConnection::TYPE_ATTRIBUTE.c_str(), sType) );

	node->addNode( poolManager.getXMLNode(iHow) );
	node->addNode( objectManager.getXMLNode(iHow) );

	return node;
}

bool Connection::isValid()
{
	//TODO: PoolManager::isValid to developer.
    return true;
}

bool Connection::equalTo(bOS::Collections::CollectionEntry* entry)
{
	Connection* connection = (Connection*)entry;

	if ( strcmp(this->getId().c_str(), connection->getId().c_str() ) == 0 )
	{
		return true;
	}

	return false;
}

bool Connection::isPrimary()
{
	if ( strcmp( this->sType.c_str(), XMLConnection::PRIMARY_TYPE.c_str() ) == 0 )
		return true;

	return false;
}

bool Connection::manageProcessTemplates()
{
	return this->manage(XMLDataBaseObject::PROCESSESTEMPLATE_TYPE);
}

bool Connection::manageReports()
{
	return this->manage(XMLDataBaseObject::REPORTS_TYPE);
}

bool Connection::manageProcessInstances()
{
	return this->manage(XMLDataBaseObject::PROCESSESINSTANCE_TYPE);
}

bool Connection::manageDataTypes()
{
	return this->manage(XMLDataBaseObject::DATATYPES_TYPE);
}

bool Connection::manageServices()
{
	return this->manage(XMLDataBaseObject::SERVICES_TYPE);
}

bool Connection::manageUsers()
{
	return this->manage(XMLDataBaseObject::USERS_TYPE);
}

bool Connection::manageRoles()
{
	return this->manage(XMLDataBaseObject::ROLES_TYPE);
}

bool Connection::manageApplicationsDataBase()
{
	return this->manage(XMLDataBaseObject::APPLICATIONS_DATABASE_TYPE);
}

bool Connection::manageApplications()
{
	return this->manage(XMLDataBaseObject::APPLICATIONS_TYPE);
}

bool Connection::manageEvents()
{
	return this->manage(XMLDataBaseObject::EVENTS_TYPE);
}

bool Connection::manageOccurredEvents()
{
	return this->manage(XMLDataBaseObject::OCCURREDEVENTS_TYPE);
}

bool Connection::manageWaitingEvents()
{
	return this->manage(XMLDataBaseObject::WAITINGEVENTS_TYPE);
}

bool Connection::manageCheckList()
{
	return this->manage(XMLDataBaseObject::CHECKLIST_TYPE);
}

bool Connection::manageForms()
{
	return this->manage(XMLDataBaseObject::FORMS_TYPE);
}

//
String Connection::getProcessInstancesValue()
{
	return this->getObjectValue(XMLDataBaseObject::PROCESSESINSTANCE_TYPE);
}

String Connection::getProcessTemplatesValue()
{
	return this->getObjectValue(XMLDataBaseObject::PROCESSESTEMPLATE_TYPE);
}


String Connection::getDataTypesValue()
{
	return this->getObjectValue(XMLDataBaseObject::DATATYPES_TYPE);
}

String Connection::getServicesValue()
{
	return this->getObjectValue(XMLDataBaseObject::SERVICES_TYPE);
}

String Connection::getUsersValue()
{
	return this->getObjectValue(XMLDataBaseObject::USERS_TYPE);
}

String Connection::getRolesValue()
{
	return this->getObjectValue(XMLDataBaseObject::ROLES_TYPE);
}

String Connection::getApplicationsValue()
{
	return this->getObjectValue(XMLDataBaseObject::APPLICATIONS_TYPE);
}

String Connection::getEventsValue()
{
	return this->getObjectValue(XMLDataBaseObject::EVENTS_TYPE);
}

String Connection::getOccurredEventsValue()
{
	return this->getObjectValue(XMLDataBaseObject::OCCURREDEVENTS_TYPE);
}

String Connection::getWaitingEventsValue()
{
	return this->getObjectValue(XMLDataBaseObject::WAITINGEVENTS_TYPE);
}

String Connection::getCheckListValue()
{
	return this->getObjectValue(XMLDataBaseObject::CHECKLIST_TYPE);
}

String Connection::getFormsValue()
{
	return this->getObjectValue(XMLDataBaseObject::FORMS_TYPE);
}

String Connection::getObjectValue(String sManaged)
{
	DataBaseObject object;
	object.setType ( sManaged);

	DataBaseObject* objectRet = (DataBaseObject*)objectManager.get ( (CollectionEntry*) &object);

	if ( objectRet == NULL )
		return "";

	return objectRet->getValue();
}

DataBaseObject* Connection::getObject(String sManaged)
{
	DataBaseObject object;
	object.setType ( sManaged);

	return (DataBaseObject*)objectManager.get ( (CollectionEntry*) &object);
}


bool Connection::manage(String sManaged)
{
	DataBaseObject object;
	object.setType ( sManaged);

	DataBaseObject* objectRet = (DataBaseObject*)objectManager.get ( (CollectionEntry*) &object);

	if ( objectRet == NULL )
		return false;

	return objectRet->isManaged();
}
