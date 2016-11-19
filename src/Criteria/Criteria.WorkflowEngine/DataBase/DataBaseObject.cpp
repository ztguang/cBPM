#include "CommonDefines.h"

#include "DataBaseObject.h"
using namespace DataManager::Panorama::DataBase;

#include "bOSSystem.h"

DataBaseObject::DataBaseObject() : XMLObject()
{
	this->init();
}

DataBaseObject::DataBaseObject( XMLNode* node ) : XMLObject()
{
	XMLObject::init(node);
}

DataBaseObject::~DataBaseObject()
{
}

void DataBaseObject::init()
{
	sType="";
	sManaged="";
}

bool DataBaseObject::init(XMLNode*node)
{
	bool bRet = XMLObject::init(node);

	//only file
	sValue = bOS::CoreSystem::System::expandEnvironmentStrings(node->getValue());

	return bRet;
}

bool DataBaseObject::parse( XMLAttribute* attribute)
{
	//CM_CODEBLOCK(DataBaseObject::parse)

	if ( strcmp(attribute->getName(), XMLDataBaseObject::MANAGED_ATTRIBUTE.c_str() ) == 0 )
	{
		sManaged = attribute->getValue();
	}
	else if ( strcmp(attribute->getName(), XMLDataBaseObject::TYPE_ATTRIBUTE.c_str() ) == 0 )
	{
		sType = attribute->getValue();
	}
	else if ( strcmp(attribute->getName(), XMLDataBaseObject::REPOSITORY_ATTRIBUTE.c_str() ) == 0 )
	{
		sRepository = attribute->getValue();
	}
	else
	{
		return false;
	}

	return true;
}

bool DataBaseObject::parse( XMLNode* node)
{
	return false;
}

XMLNode* DataBaseObject::getXMLNode(unsigned int iHow)
{
    //CM_CODEBLOCK(DataBaseObject::getXmlNode)
    
	XMLNode* node = new XMLNode( XMLDataBaseObject::MAIN_NODE.c_str(), sValue );

	node->addAttribute ( new XMLAttribute(XMLDataBaseObject::MANAGED_ATTRIBUTE.c_str(), sManaged) );
	node->addAttribute ( new XMLAttribute(XMLDataBaseObject::TYPE_ATTRIBUTE.c_str(), sType) );
	node->addAttribute ( new XMLAttribute(XMLDataBaseObject::REPOSITORY_ATTRIBUTE.c_str(), sRepository) );
	return node;
}

bool DataBaseObject::isValid()
{
	//TODO: DataBaseObject::isValid to developer.
    return true;
}

bool DataBaseObject::equalTo(bOS::Collections::CollectionEntry* entry)
{
	DataBaseObject* object = (DataBaseObject*)entry;

	if ( strcmp(this->getType().c_str(), object->getType().c_str() ) == 0 )
	{
		return true;
	}

	return false;
}

bool DataBaseObject::isManaged()
{
	if ( strcmp(this->sManaged.c_str(), XMLDataBaseObject::YES_MANAGED.c_str()) == 0 )
		return true;

	return false;
}

bool DataBaseObject::isFileRepository()
{
	if ( strcmp(this->sRepository.c_str(), XMLDataBaseObject::FILE_REPOSITORY.c_str()) == 0 )
		return true;

	return false;
}
