#include "CommonDefines.h"

#include "DataTypeValues.h"
using namespace DataManager::Panorama::WorkflowDataTypes;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

DataTypeValues::DataTypeValues() : XMLObjectSet()
{
	this->init();
}

DataTypeValues::DataTypeValues(XMLNode* node ) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

DataTypeValues::~DataTypeValues(void)
{
}

void DataTypeValues::init()
{
	XMLObjectSet::init();
}

bool DataTypeValues::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool DataTypeValues::init(const char* acXML)
{
	return XMLObjectSet::init(acXML);
}

bool DataTypeValues::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLDataTypeValue::MAIN_NODE.c_str() ) )
    {
		DataTypeValue* value = new DataTypeValue(node);
		this->add((CollectionEntry*)value);
    }
	else
	{
		return false;
	}

	return true;
}

bool DataTypeValues::parse(XMLAttribute* attribute)
{
	return false;
}

bool DataTypeValues::isValid()
{
	return true;
}

XMLNode* DataTypeValues::getXMLNode(unsigned int iHow)
{
    XMLNode* root= new XMLNode( XMLDataTypeValues::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	DataTypeValue* value=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		value = (DataTypeValue*)(this->at(i));
		root->addNode( value->getXMLNode(iHow) );
	}
    
    return root;
}

DataTypeValue* DataTypeValues::getValue(String sKey)
{
	DataTypeValue value;
	value.setKey ( sKey);

	return (DataTypeValue*)XMLObjectSet::get ( (CollectionEntry*) &value);
}