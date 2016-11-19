#include "CommonDefines.h"

#include "DataBaseObjectManager.h"
#include "DataBaseObject.h"
using namespace DataManager::Panorama::DataBase;

DataBaseObjectManager::DataBaseObjectManager() : XMLObjectSet()
{
	this->init();
}

DataBaseObjectManager::DataBaseObjectManager( XMLNode* node ) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

DataBaseObjectManager::~DataBaseObjectManager()
{
}

void DataBaseObjectManager::init()
{
}

bool DataBaseObjectManager::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool DataBaseObjectManager::parse( XMLAttribute* attribute)
{
	return false;
}

bool DataBaseObjectManager::parse( XMLNode* node)
{
	if ( strcmp(node->getName(),XMLDataBaseObject::MAIN_NODE.c_str()) == 0 )
	{
		DataBaseObject* object = new DataBaseObject();
		object->init(node);

		this->add((bOS::Collections::CollectionEntry*)object);
	}
	else
	{
		return false;
	}
        
	return true;
}

XMLNode* DataBaseObjectManager::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(getXMLNode)
    
    XMLNode* node = new XMLNode( XMLDataBaseObjectManager::MAIN_NODE.c_str(), "" );

	unsigned int uiSize= this->size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		DataBaseObject* object = (DataBaseObject*)this->at(i);
		node->addNode ( object->getXMLNode(iHow) );
	}

	return node;
}

bool DataBaseObjectManager::isValid()
{
	//TODO: ObjectManager::isValid to developer.
    return true;
}
