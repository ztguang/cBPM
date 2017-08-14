#include "CommonDefines.h"

#include "DataType.h"
using namespace DataManager::Panorama::WorkflowDataTypes;

using namespace bOS::XML;
using namespace bOS::SQL;

DataType::DataType() : XMLObject(), SQLTable(true)
{
	this->init();
}

DataType::DataType( bOS::XML::XMLNode* node) : XMLObject(), SQLTable(true)
{
	XMLObject::init(node);
}

DataType::DataType(const char* acXML) : XMLObject(), SQLTable(true)
{
	XMLObject::init(acXML);
}

DataType::~DataType()
{
}

void DataType::init()
{
    sType = "";
    sKey = "";
    sDescription="";

	vValues.init();
}

bool DataType::init(bOS::XML::XMLNode* node)
{
	return XMLObject::init(node);
}

bool DataType::parse( XMLAttribute* attribute )
{
	if ( strcmp(attribute->getName(),XMLDataType::KEY_ATTRIBUTE.c_str()) == 0 )
	{
        sKey = attribute->getValue();
	}
	else if ( strcmp(attribute->getName(),XMLDataType::TYPE_ATTRIBUTE.c_str()) == 0 )
	{
        sType = attribute->getValue();
	}
	else
	{
		return false;
	}

	return true;
}

bool DataType::parse( XMLNode* node )
{
	if ( strcmp(node->getName(),XMLDataType::DESCRIPTION_NODE.c_str()) == 0 )
        sDescription = node->getValue();
	else if (strcmp(node->getName(), XMLDataTypeValues::MAIN_NODE.c_str()) == 0 )
		return vValues.init(node);
	else
		return false;
        
	return true;
}

XMLNode* DataType::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLDataType::MAIN_NODE.c_str(), "" );
	root->addAttribute( new XMLAttribute( XMLDataType::KEY_ATTRIBUTE.c_str(), sKey ) );
	root->addAttribute( new XMLAttribute( XMLDataType::TYPE_ATTRIBUTE.c_str(), sType ) );

	switch ( iHow )
	{
	case 0:
		root->addNode( new XMLNode( XMLDataType::DESCRIPTION_NODE.c_str(), sDescription.c_str() ) );
		root->addNode (vValues.getXMLNode (0) );
		break;
	}

	return root;
}

bool DataType::isValid()
{
    if ( sKey == "" )
        return false;

    return true;
}

bool DataType::equalTo(bOS::Collections::CollectionEntry* entry)
{
	DataType* type = (DataType*)entry;
	if ( strcmp(type->getKey().c_str(), this->getKey().c_str()) == 0 )
	{
		return true;
	}

	return false;
}
/*****************************************/
const char* DataType::acGetTableName()
{
	return SQLDataType::TABLE_NAME.c_str();
}

void DataType::setRecord(ResultSetRecord& record)
{
	record.clear();

	record.add ( new ResultSetField (SQLDataType::KEY_FIELD.c_str(), sKey));
	record.add ( new ResultSetField (SQLDataType::TYPE_FIELD.c_str(), sType));
	record.add ( new ResultSetField (SQLDataType::DESCRIPTION_FIELD.c_str(), sDescription));
	record.add ( new ResultSetField (SQLDataType::VALUES_FIELD.c_str(), vValues.getXMLString(0)));

}

String DataType::acGetWhere()
{
	StringBuffer sSql;

	sSql.append(SQLDataType::KEY_FIELD);
	sSql.append("=");
	sSql.append(StringUtils::returnQuoteAndTwice (sKey) );

	return sSql.getData();
}

bool DataType::parse(ResultSetField* field)
{
	if ( !strcmp(field->sName.c_str(), SQLDataType::KEY_FIELD.c_str()) )
	{
		sKey = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLDataType::TYPE_FIELD.c_str()) )
	{
		sType = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLDataType::DESCRIPTION_FIELD.c_str()) )
	{
		sDescription = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(), SQLDataType::VALUES_FIELD.c_str()) )
	{
		vValues.init(field->sValue.getData());
	}
	else
		return false;

	return true;
}

bool DataType::parse(bOS::SQL::ResultSetRecord* record)
{
	return SQLTable::parse (record);
}
