#include "CommonDefines.h"

#include "PoolManager.h"
using namespace DataManager::Panorama::DataBase;

PoolManager::PoolManager() : XMLObject()
{
	this->init();
}

PoolManager::PoolManager( XMLNode* node ) : XMLObject()
{
	XMLObject::init(node);
}

PoolManager::~PoolManager()
{
}

void PoolManager::init()
{
	uiMin = 1;
	uiMax = 1;
	uiRetry = 10;
	uiDelay = 1000;
}

bool PoolManager::init(XMLNode* node)
{
	return XMLObject::init(node);
}

bool PoolManager::parse( XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(), XMLPoolManager::MIN_ATTRIBUTE.c_str() ) == 0 )
	{
		uiMin = attribute->getUIntValue();
	}
	else if ( strcmp(attribute->getName(), XMLPoolManager::MAX_ATTRIBUTE.c_str() ) == 0 )
	{
		uiMax = attribute->getUIntValue();
	}
	else if ( strcmp(attribute->getName(),XMLPoolManager::RETRY_NODE.c_str()) == 0 )
	{
        uiRetry = attribute->getUIntValue();
	}
	else if ( strcmp(attribute->getName(),XMLPoolManager::DELAY_NODE.c_str() ) == 0 )
	{
        uiDelay = attribute->getUIntValue();
	}

	return true;
}

bool PoolManager::parse( XMLNode* node)
{
	return true;
}

XMLNode* PoolManager::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(createXmlNode)
    
    XMLNode* node = new XMLNode( XMLPoolManager::MAIN_NODE.c_str(), "" );

	node->addAttribute ( new XMLAttribute(XMLPoolManager::MIN_ATTRIBUTE.c_str(), uiMin) );
	node->addAttribute ( new XMLAttribute(XMLPoolManager::MAX_ATTRIBUTE.c_str(), uiMax) );
	node->addAttribute ( new XMLAttribute(XMLPoolManager::RETRY_NODE.c_str(), uiRetry) );
	node->addAttribute ( new XMLAttribute(XMLPoolManager::DELAY_NODE.c_str(), uiDelay) );

	return node;
}

bool PoolManager::isValid()
{
	//TODO: PoolManager::isValid to developer.
    return true;
}
