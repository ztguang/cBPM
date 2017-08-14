#include "CommonDefines.h"

#include "User.h"
using namespace DataManager::Panorama::WorkflowParticipantsData;

using namespace bOS::XML;
using namespace bOS::SQL;

User::User() : XMLObject(), SQLTable(true)
{
	this->init();
}

User::User( bOS::XML::XMLNode* root) : XMLObject(), SQLTable(true)
{
	XMLObject::init(root);
}

User::User(const char* acXML) : XMLObject(), SQLTable(true)
{
	XMLObject::init(acXML);
}

User::~User()
{
}

void User::init()
{
    sName = "";
    sKey = "";
    sDescription="";
	sPassword="";
	sDisplayName="";
	sEmail="";
}

bool User::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool User::init(const char* acXML)
{
	return XMLObject::init (acXML);
}

bool User::parse( XMLAttribute* attribute )
{
	if ( strcmp(attribute->getName(),XMLUser::KEY_ATTRIBUTE.c_str()) == 0 )
	{
        sKey = attribute->getValue();
	}
	else
	{
		return false;
	}

	return true;
}

bool User::parse( XMLNode* node )
{
	if ( strcmp(node->getName(),XMLUser::NAME_NODE.c_str()) == 0 )
        sName = node->getValue();
	else if ( strcmp(node->getName(),XMLUser::DESCRIPTION_NODE.c_str()) == 0 )
        sDescription = node->getValue();

	else if ( strcmp(node->getName(),XMLUser::PASSWORD_NODE.c_str()) == 0 )
        sPassword = node->getValue();

	else if ( strcmp(node->getName(),XMLUser::DISPLAYNAME_NODE.c_str()) == 0 )
        sDisplayName = node->getValue();

	else if ( strcmp(node->getName(),XMLUser::EMAIL_NODE.c_str()) == 0 )
        sEmail= node->getValue();
	else
		return false;
        
	return true;
}

XMLNode* User::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLUser::MAIN_NODE.c_str(), "" );
	root->addAttribute( new XMLAttribute( XMLUser::KEY_ATTRIBUTE.c_str(), sKey.c_str() ) );

	switch ( iHow )
	{
	case 0:
		root->addNode( new XMLNode( XMLUser::NAME_NODE.c_str(), sName.c_str() ) );
		root->addNode( new XMLNode( XMLUser::DESCRIPTION_NODE.c_str(), sDescription.c_str() ) );
		root->addNode( new XMLNode( XMLUser::PASSWORD_NODE.c_str(), sPassword.c_str() ) );
		root->addNode( new XMLNode( XMLUser::DISPLAYNAME_NODE.c_str(), sDisplayName.c_str() ) );
		root->addNode( new XMLNode( XMLUser::EMAIL_NODE.c_str(), sEmail.c_str() ) );
		break;
	}

	return root;
}

bool User::isValid()
{
    if ( sKey == "" )
        return false;

    return true;
}

bool User::equalTo(bOS::Collections::CollectionEntry* entry)
{
	User* user = (User*)entry;
	if ( strcmp(user->getKey().c_str(), this->getKey().c_str()) == 0 )
	{
		return true;
	}

	return false;
}

/*****************************************/
const char* User::acGetTableName()
{
	return SQLUser::TABLE_NAME.c_str();
}

void User::setRecord(ResultSetRecord& record)
{
	record.clear();

	record.add ( new ResultSetField (SQLUser::KEY_FIELD.c_str(), sKey));
	record.add ( new ResultSetField (SQLUser::NAME_FIELD.c_str(), sName));
	record.add ( new ResultSetField (SQLUser::DESCRIPTION_FIELD.c_str(), sDescription));
	record.add ( new ResultSetField (SQLUser::PASSWORD_FIELD.c_str(), sPassword));
	record.add ( new ResultSetField (SQLUser::DISPLAYNAME_FIELD.c_str(), sDisplayName));
	record.add ( new ResultSetField (SQLUser::EMAIL_FIELD.c_str(), sEmail));
}

String User::acGetWhere()
{
	StringBuffer sSql;

	sSql.append(SQLUser::KEY_FIELD);
	sSql.append("=");
	sSql.append(StringUtils::returnQuoteAndTwice (sKey) );

	return sSql.getData();
}

bool User::parse(ResultSetField* field)
{
	if ( !strcmp(field->sName.c_str(), SQLUser::KEY_FIELD.c_str()) )
	{
		sKey = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLUser::NAME_FIELD.c_str()) )
	{
		sName = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLUser::DESCRIPTION_FIELD.c_str()) )
	{
		sDescription = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLUser::PASSWORD_FIELD.c_str()) )
	{
		sPassword = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLUser::DISPLAYNAME_FIELD.c_str()) )
	{
		sDisplayName = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLUser::EMAIL_FIELD.c_str()) )
	{
		sEmail = field->sValue.getData();
	}
	else
		return false;

	return true;
}

bool User::parse(bOS::SQL::ResultSetRecord* record)
{
	return SQLTable::parse (record);
}