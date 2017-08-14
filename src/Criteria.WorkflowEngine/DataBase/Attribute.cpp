#include "CommonDefines.h"

#include "Attribute.h"
using namespace DataManager::Panorama::WorkflowRelevantData;

using namespace bOS::SQL;

using namespace DataManager::Panorama::WorkflowProcesses;

Attribute::Attribute() : XMLObject(), SQLTable(true), ActivityComponent()
{
	this->init();
}

Attribute::Attribute( bOS::XML::XMLNode* root ) : XMLObject(), SQLTable(true), ActivityComponent()
{
	this->init(root);
}

Attribute::Attribute(const String& name, const String& type) : XMLObject(), SQLTable(true), ActivityComponent()
{
	this->init();

	sName = name;
	sType = type;
}

Attribute::Attribute(Attribute* attribute) : XMLObject(), SQLTable(true), ActivityComponent()
{
	this->init();

	sName = attribute->getName();
    sValue = attribute->getValue();
	sType = attribute->getType();
    sDirection = attribute->getDirection();
}

Attribute::~Attribute()
{
}

//
void Attribute::init()
{
    sName="";
    sValue="";
	sType="";

	sDirection = XMLAttribute::DIRECTION_NONE;

	bAlreadyCreated = false;

	ActivityComponent::init();
}

bool Attribute::init(bOS::XML::XMLNode*node)
{
	bool bRet = XMLObject::init (node);

	/*
	if ( strcmp(sType.c_str(), XMLAttribute::XML_TYPE.c_str() ) == 0 )
	{
		sValue = node->getInnerXML();

		if ( sValue.length() == 0 )
		{
			sValue = node->getValue();
		}
	}
	else
	{
		sValue = node->getValue();
	}
	*/

	return bRet;
}

bool Attribute::parse(bOS::XML::XMLAttribute* attribute)
{
	if ( ActivityComponent::parse (attribute) )
		return true;

	else if ( strcmp(attribute->getName(),XMLAttribute::NAME_ATTRIBUTE.c_str()) == 0 )
	{
		sName = attribute->getValue();
	}
	else if ( strcmp(attribute->getName(),XMLAttribute::TYPE_ATTRIBUTE.c_str()) == 0 )
	{
		sType= attribute->getValue();
	}
	else if ( strcmp(attribute->getName(),XMLAttribute::DIRECTION_ATTRIBUTE.c_str()) == 0 )
	{
		sDirection = attribute->getValue();
	}
	else
		return false;

	return true;
}

bool Attribute::parse(bOS::XML::XMLNode* node)
{
	if ( ActivityComponent::parse (node) )
	{
		return true;
	}
	else if ( strcmp(node->getName(), XMLAttribute::VALUE_NODE.c_str() ) == 0 )
	{
		if (strcmp(sType.c_str(), XMLAttribute::XML_TYPE.c_str() ) == 0 )
		{
			sValue = node->getInnerXML();
		
			if ( sValue.length() == 0 )
			{
				sValue = node->getValue();
			}
		}
		else
		{
			sValue = node->getValue();
		}
	}
	else
		return false;

	return true;
}

bOS::XML::XMLNode* Attribute::getXMLNode(unsigned int iHow)
{
    bOS::XML::XMLNode* root = new bOS::XML::XMLNode( XMLAttribute::MAIN_NODE.c_str(),"");

	//ActivityComponent::setXML ( root );

	root->addAttribute( new bOS::XML::XMLAttribute( XMLAttribute::NAME_ATTRIBUTE.c_str(), sName ) );
	root->addAttribute( new bOS::XML::XMLAttribute( XMLAttribute::TYPE_ATTRIBUTE.c_str(), sType ) );
	root->addAttribute( new bOS::XML::XMLAttribute( XMLAttribute::DIRECTION_ATTRIBUTE.c_str(), sDirection ) );

	root->addNode ( new bOS::XML::XMLNode ( XMLAttribute::VALUE_NODE.c_str(), sValue) );
    
    return root;
}

bool Attribute::isValid()
{
    if ( sName == "" )
        return false;

    return true;
}

//CollectionEntry
bool Attribute::equalTo(bOS::Collections::CollectionEntry* entry)
{
	Attribute* attribute = (Attribute*)entry;

	if ( strcmp(attribute->getName().c_str(), this->getName().c_str()) == 0 )
	{
		return true;
	}

	return false;
}

/*****************************************/
const char* Attribute::acGetTableName()
{
	return SQLAttribute::TABLE_NAME.c_str();
}

void Attribute::setRecord(ResultSetRecord& record)
{
	record.clear();

	record.add ( new ResultSetField (SQLAttribute::DIRECTION_FIELD.c_str(), sDirection));
	record.add ( new ResultSetField (SQLAttribute::NAME_FIELD.c_str(), sName));
	record.add ( new ResultSetField (SQLAttribute::TYPE_FIELD.c_str(), sType));
	record.add ( new ResultSetField (SQLAttribute::VALUE_FIELD.c_str(), sValue));

	ActivityComponent::setRecord ( record);
}

String Attribute::acGetWhere()
{
	StringBuffer sSql;

	sSql.append(ActivityComponent::acGetWhere());
	sSql.append(" AND ");
	sSql.append(SQLAttribute::NAME_FIELD);
	sSql.append("=");
	sSql.append(StringUtils::returnQuoteAndTwice (sName) );

	return sSql.getData();
}

bool Attribute::parse(ResultSetField* field)
{
	bool bRet = true;

	if ( !strcmp(field->sName.c_str(), SQLAttribute::DIRECTION_FIELD.c_str()) )
	{
		sDirection = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLAttribute::NAME_FIELD.c_str()) )
	{
		sName = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLAttribute::TYPE_FIELD.c_str()) )
	{
		sType = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLAttribute::VALUE_FIELD.c_str()) )
	{
		sValue = field->sValue.getData();
	}
	else 
		bRet = ActivityComponent::parse(field);

	return bRet;
}

bool Attribute::parse(bOS::SQL::ResultSetRecord* record)
{
	return SQLTable::parse (record);
}