#include "CommonDefines.h"

#include "Role.h"
using namespace DataManager::Panorama::WorkflowParticipantsData;

using namespace bOS::XML;
using namespace bOS::SQL;

Role::Role() : XMLObject(), SQLTable(true)
{
	this->init();
}

Role::Role( XMLNode* root ) : XMLObject(), SQLTable(true)
{
	XMLObject::init(root);
}

Role::Role(const char* acXML) : XMLObject(), SQLTable(true)
{
	XMLObject::init(acXML);
}

Role::~Role()
{
	;
}

void Role::init()
{
    sKey="";
    sDescription="";
	sName="";

	vUsers.init();
}

bool Role::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool Role::init(const char* acXML)
{
	return XMLObject::init(acXML);
}

bool Role::parse(XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(),XMLRole::KEY_ATTRIBUTE.c_str()) == 0 )
	{
        sKey = attribute->getValue();
	}
	else
	{
		return false;
	}

	return true;
}

bool Role::parse(XMLNode* node )
{
	if ( strcmp(node->getName(),XMLRole::NAME_NODE.c_str()) == 0 )
        sName = node->getValue();

	else if ( strcmp(node->getName(),XMLRole::DESCRIPTION_NODE.c_str()) == 0 )
        sDescription = node->getValue();

	else if ( strcmp(node->getName(), XMLUsers::MAIN_NODE.c_str()) == 0 )
	{
		vUsers.init (node);
	}
	else
		return false;

	return true;
}

XMLNode* Role::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLRole::MAIN_NODE.c_str(), "" );
	root->addAttribute( new XMLAttribute( XMLRole::KEY_ATTRIBUTE.c_str(), sKey.c_str() ) );

	switch ( iHow )
	{
	case 0:
		root->addNode( new XMLNode( XMLRole::NAME_NODE.c_str(), sName.c_str() ) );
		root->addNode( new XMLNode( XMLRole::DESCRIPTION_NODE.c_str(), sDescription.c_str() ) );
		root->addNode ( vUsers.getXMLNode(1));
		break;
	}

    return root;
}

bool Role::equalTo(bOS::Collections::CollectionEntry* entry)
{
	Role* role = (Role*)entry;
	if ( strcmp(role->getKey().c_str(), this->getKey().c_str()) == 0 )
	{
		return true;
	}
	return false;
}

/*****************************************/
const char* Role::acGetTableName()
{
	return SQLRole::TABLE_NAME.c_str();
}

void Role::setRecord(ResultSetRecord& record)
{
	record.clear();

	record.add ( new ResultSetField (SQLRole::KEY_FIELD.c_str(), sKey));
	record.add ( new ResultSetField (SQLRole::NAME_FIELD.c_str(), sName));
	record.add ( new ResultSetField (SQLRole::DESCRIPTION_FIELD.c_str(), sDescription));
	record.add ( new ResultSetField (SQLRole::USERS_FIELD.c_str(), vUsers.getXMLString(1)));

}

String Role::acGetWhere()
{
	StringBuffer sSql;

	sSql.append(SQLRole::KEY_FIELD);
	sSql.append("=");
	sSql.append(StringUtils::returnQuoteAndTwice (sKey) );

	return sSql.getData();
}

bool Role::parse(ResultSetField* field)
{
	if ( !strcmp(field->sName.c_str(), SQLRole::KEY_FIELD.c_str()) )
	{
		sKey = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLRole::NAME_FIELD.c_str()) )
	{
		sName = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLRole::DESCRIPTION_FIELD.c_str()) )
	{
		sDescription = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLRole::USERS_FIELD.c_str()) )
	{
		vUsers.init(field->sValue.getData());
	}
	else
		return false;

	return true;
}

bool Role::parse(bOS::SQL::ResultSetRecord* record)
{
	return SQLTable::parse (record);
}
