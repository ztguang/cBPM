#include "CommonDefines.h"

#include "DataTypes.h"
using namespace DataManager::Panorama::WorkflowDataTypes;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

DataTypes::DataTypes() : XMLObjectSet()
{
	this->init();
}

DataTypes::DataTypes(XMLNode* node ) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

DataTypes::~DataTypes(void)
{
}

void DataTypes::init()
{
	XMLObjectSet::init();
}

bool DataTypes::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

//bool DataTypes::init(bOS::IO::File& file)     //ztg delete
bool DataTypes::init(bOS::IO::File file)
{
	return XMLObjectSet::init(file);
}

bool DataTypes::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLDataType::MAIN_NODE.c_str() ) )
    {
		DataType* type = new DataType(node);
		this->add((CollectionEntry*)type);
    }
	else
	{
		return false;
	}

	return true;
}

bool DataTypes::parse(XMLAttribute* attribute)
{
	return true;
}

bool DataTypes::isValid()
{
	return true;
}

XMLNode* DataTypes::getXMLNode(unsigned int iHow)
{
    XMLNode* root= new XMLNode( XMLDataTypes::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	DataType* type=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		type = (DataType*)(this->at(i));
		root->addNode( type->getXMLNode(iHow) );
	}

    return root;
}

DataType* DataTypes::getDataType ( const String& sKey)
{
	DataType datatype;
	datatype.setKey ( sKey);

	DataType* datatype2ret = (DataType*)XMLObjectSet::get ( (CollectionEntry*) &datatype);

	return datatype2ret;
}
