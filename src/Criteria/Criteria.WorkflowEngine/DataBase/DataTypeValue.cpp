#include "CommonDefines.h"

#include "DataTypeValue.h"
using namespace DataManager::Panorama::WorkflowDataTypes;

using namespace bOS::XML;

DataTypeValue::DataTypeValue() : XMLObject()
{
	this->init();
}

DataTypeValue::DataTypeValue( bOS::XML::XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
	sValue = node->getValue();
}

DataTypeValue::DataTypeValue(const char* acXML) : XMLObject()
{
	XMLObject::init(acXML);
}

DataTypeValue::~DataTypeValue()
{
}

void DataTypeValue::init()
{
    sValue = "";
    sKey = "";
}

bool DataTypeValue::parse( XMLAttribute* attribute )
{
	if ( strcmp(attribute->getName(),XMLDataTypeValue::KEY_ATTRIBUTE.c_str()) == 0 )
	{
        sKey = attribute->getValue();
	}
	else
	{
		return false;
	}

	return true;
}

bool DataTypeValue::parse( XMLNode* node )
{
	return false;
}

XMLNode* DataTypeValue::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLDataTypeValue::MAIN_NODE.c_str(), sValue);
	root->addAttribute( new XMLAttribute( XMLDataTypeValue::KEY_ATTRIBUTE.c_str(), sKey.c_str() ) );

	return root;
}

bool DataTypeValue::isValid()
{
    if ( sKey == "" )
        return false;

    return true;
}

bool DataTypeValue::equalTo(bOS::Collections::CollectionEntry* entry)
{
	DataTypeValue* value = (DataTypeValue*)entry;
	if ( strcmp(value->getKey().c_str(), this->getKey().c_str()) == 0 )
	{
		return true;
	}

	return false;
}
