#include "CommonDefines.h"

#include "DataBase.h"
using namespace DataManager::Panorama::DataBase;

DataBase::DataBase() : XMLFile()
{
	this->init();
}

DataBase::~DataBase()
{
}

void DataBase::init()
{
	vConnections.init();
}

bool DataBase::parse( bOS::XML::XMLAttribute* attribute)
{
	return true;
}

bool DataBase::parse( bOS::XML::XMLNode* node)
{
	if ( strcmp(node->getName(),XMLConnections::MAIN_NODE.c_str()) == 0 )
	{
		return vConnections.init(node);
	}
	else
	{
		return false;
	}
        
	return true;
}

XMLNode* DataBase::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(DataBase::getXMLNode)
    
    bOS::XML::XMLNode* node = new bOS::XML::XMLNode( XMLDataBase::MAIN_NODE.c_str(), "" );
	node->addNode ( vConnections.getXMLNode(iHow));

	return node;
}

bool DataBase::isValid()
{
	//TODO: PoolManager::isValid to developer.
    return true;
}

