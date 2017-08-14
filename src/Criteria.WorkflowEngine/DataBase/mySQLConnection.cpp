#include "CommonDefines.h"

#include "mySQLConnection.h"
using namespace DataManager::Panorama::DataBase;

mySQLConnection::mySQLConnection() : Connection()
{
	this->init();
}

mySQLConnection::mySQLConnection( XMLNode* node ) : Connection(node)
{
	XMLObject::init(node);
}

mySQLConnection::~mySQLConnection()
{
}

void mySQLConnection::init()
{
	Connection::init();

	sHost="";
	uiPort=0;
	sUser="";
	sPassword="";
	sDataBase="";

	idType=1;
}

bool mySQLConnection::parse( XMLAttribute* attribute)
{
	if ( Connection::parse(attribute) )
	{
		return true;
	}

	return false;
}

bool mySQLConnection::parse( XMLNode* node)
{
	if ( Connection::parse(node) )
	{
		return true;
	}
	else if ( strcmp(node->getName(),XMLmySQLConnection::USER_NODE.c_str()) == 0 )
	{
        sUser = node->getValue();
	}
	else if ( strcmp(node->getName(),XMLmySQLConnection::DATABASE_NODE.c_str()) == 0 )
	{
        sDataBase = node->getValue();
	}
	else if ( strcmp(node->getName(),XMLmySQLConnection::PASSWORD_NODE.c_str()) == 0 )
	{
        sPassword = node->getValue();
	}
	else if ( strcmp(node->getName(),XMLmySQLConnection::HOST_NODE.c_str()) == 0 )
	{
        sHost = node->getValue();
	}
	else if ( strcmp(node->getName(),XMLmySQLConnection::PORT_NODE.c_str()) == 0 )
	{
        uiPort = node->getUIntValue();
	}
	else
	{
		return false;
	}
        
	return true;
}

XMLNode* mySQLConnection::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(Connection::getXmlNode)
    
    XMLNode* node = Connection::getXMLNode(iHow);
	node->setName ( XMLmySQLConnection::MAIN_NODE.c_str());

	node->addNode( new XMLNode(XMLmySQLConnection::HOST_NODE.c_str(), sHost) );
	node->addNode( new XMLNode(XMLmySQLConnection::PORT_NODE.c_str(), uiPort) );
	node->addNode( new XMLNode(XMLmySQLConnection::USER_NODE.c_str(), sUser) );
	node->addNode( new XMLNode(XMLmySQLConnection::PASSWORD_NODE.c_str(), sPassword) );
	node->addNode( new XMLNode(XMLmySQLConnection::DATABASE_NODE.c_str(), sDataBase) );

	return node;
}

bool mySQLConnection::isValid()
{
	//TODO: PoolManager::isValid to developer.
    return true;
}
