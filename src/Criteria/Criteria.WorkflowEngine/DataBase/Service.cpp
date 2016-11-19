#include "CommonDefines.h"

#include "Service.h"
using namespace DataManager::Panorama::WorkflowServices;

using namespace bOS::XML;
using namespace bOS::SQL;

Service::Service() : XMLObject(), SQLTable(true)
{
	this->init();
}

Service::Service( bOS::XML::XMLNode* node) : XMLObject(), SQLTable(true)
{
	XMLObject::init(node);
}

Service::Service(const char* acXML) : XMLObject(), SQLTable(true)
{
	XMLObject::init(acXML);
}

Service::~Service()
{
}

void Service::init()
{
	sName = "";
    sDescription = "";
    sWorkflowName = "";

	vUsers.init();
	vRoles.init();

	vExtendedAttributes.init();
}

bool Service::init(bOS::XML::XMLNode* node)
{
	return XMLObject::init(node);
}

bool Service::parse(XMLNode* node )
{
	bool bRet = true;

	if ( strcmp(node->getName(),XMLService::WORKFLOW_NODE.c_str()) == 0 )
		sWorkflowName = node->getValue();

	else if ( strcmp(node->getName(),XMLService::DESCRIPTION_NODE.c_str() ) == 0 )
		sDescription = node->getValue();
	
	else if ( strcmp(node->getName(),WorkflowParticipantsData::XMLRoles::MAIN_NODE.c_str()) == 0 )
		bRet = vRoles.init(node);

	else if ( strcmp(node->getName(),WorkflowParticipantsData::XMLUsers::MAIN_NODE.c_str()) == 0 )
		bRet = vUsers.init(node);

	else if ( !strcmp(node->getName(), Common::XMLExtendedAttributes::MAIN_NODE.c_str() ) )
	{
		bRet= vExtendedAttributes.init(node);
	}
	else
		bRet=false;

	return bRet;
}

bool Service::parse( XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(),XMLService::NAME_ATTRIBUTE.c_str()) == 0 )
        sName = attribute->getValue();
	else
		return false;

	return true;
}


XMLNode* Service::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLService::MAIN_NODE.c_str(), "" );
	root->addAttribute ( new XMLAttribute ( XMLService::NAME_ATTRIBUTE.c_str(), sName) );
	root->addNode( new XMLNode( XMLService::DESCRIPTION_NODE.c_str(), sDescription ) );
	root->addNode( new XMLNode( XMLService::WORKFLOW_NODE.c_str(), sWorkflowName ) );

	root->addNode( vUsers.getXMLNode(1) );
	root->addNode( vRoles.getXMLNode(1) );

	root->addNode ( vExtendedAttributes.getXMLNode(iHow));

	return root;
}

bool Service::isValid()
{
    if ( sName == "" )
        return false;

    if ( sWorkflowName == "" )
        return false;

    return true;
}

bool Service::equalTo(bOS::Collections::CollectionEntry* entry)
{
	Service* service = (Service*)entry;

	if ( strcmp(service->getName().c_str(), this->sName.c_str() ) == 0 )
		return true;

	return false;
}

/*****************************************/
const char* Service::acGetTableName()
{
	return SQLService::TABLE_NAME.c_str();
}

void Service::setRecord(ResultSetRecord& record)
{
	record.clear();

	record.add ( new ResultSetField (SQLService::NAME_FIELD.c_str(), sName));
	record.add ( new ResultSetField (SQLService::WORKFLOW_FIELD.c_str(), sWorkflowName));
	record.add ( new ResultSetField (SQLService::DESCRIPTION_FIELD.c_str(), sDescription));
	record.add ( new ResultSetField (SQLService::USERS_FIELD.c_str(), vUsers.getXMLString(1)));
	record.add ( new ResultSetField (SQLService::ROLES_FIELD.c_str(), vRoles.getXMLString(1)));
	record.add ( new ResultSetField (SQLService::EXTENDEDATTRIBUTES_FIELD.c_str(), vExtendedAttributes.getXMLString(1)));
}

String Service::acGetWhere()
{
	StringBuffer sSql;

	sSql.append(SQLService::NAME_FIELD);
	sSql.append("=");
	sSql.append(StringUtils::returnQuoteAndTwice (sName) );

	return sSql.getData();
}

bool Service::parse(ResultSetField* field)
{
	if ( !strcmp(field->sName.c_str(), SQLService::NAME_FIELD.c_str()) )
	{
		sName = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLService::WORKFLOW_FIELD.c_str()) )
	{
		sWorkflowName = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLService::DESCRIPTION_FIELD.c_str()) )
	{
		sDescription = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLService::USERS_FIELD.c_str()) )
	{
		vUsers.init(field->sValue.getData());
	}
	else if ( !strcmp(field->sName.c_str(), SQLService::ROLES_FIELD.c_str()) )
	{
		vRoles.init(field->sValue.getData());
	}
	else if ( !strcmp(field->sName.c_str(), SQLService::EXTENDEDATTRIBUTES_FIELD.c_str()) )
	{
		vExtendedAttributes.init(field->sValue.getData());
	}
	else
		return false;

	return true;
}

bool Service::parse(bOS::SQL::ResultSetRecord* record)
{
	return SQLTable::parse (record);
}

