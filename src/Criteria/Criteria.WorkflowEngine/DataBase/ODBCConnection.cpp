#include "CommonDefines.h"

#include "ODBCConnection.h"
using namespace DataManager::Panorama::DataBase;

ODBCConnection::ODBCConnection() : Connection()
{
	this->init();
}

ODBCConnection::ODBCConnection( XMLNode* node ) : Connection(node)
{
	XMLObject::init(node);
}

ODBCConnection::~ODBCConnection()
{
}

void ODBCConnection::init()
{
	Connection::init();

	sUser="";
	sPassword="";
	sDsn="";

	idType=2;
}

bool ODBCConnection::parse( XMLAttribute* attribute)
{
	if ( Connection::parse(attribute) )
	{
		return true;
	}

	return false;
}

bool ODBCConnection::parse( XMLNode* node)
{
	if ( Connection::parse(node) )
	{
		return true;
	}
	else if ( strcmp(node->getName(),XMLODBCConnection::USER_NODE.c_str()) == 0 )
	{
        sUser = node->getValue();
	}
	else if ( strcmp(node->getName(),XMLODBCConnection::DSN_NODE.c_str()) == 0 )
	{
        sDsn = node->getValue();
	}
	else if ( strcmp(node->getName(),XMLODBCConnection::PASSWORD_NODE.c_str()) == 0 )
	{
        sPassword = node->getValue();
	}
	else
	{
		return false;
	}
        
	return true;
}

XMLNode* ODBCConnection::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(Connection::getXmlNode)
    
    XMLNode* node = Connection::getXMLNode(iHow);
	node->setName ( XMLODBCConnection::MAIN_NODE.c_str());

	node->addNode( new XMLNode(XMLODBCConnection::USER_NODE.c_str(), sUser) );
	node->addNode( new XMLNode(XMLODBCConnection::PASSWORD_NODE.c_str(), sPassword) );
	node->addNode( new XMLNode(XMLODBCConnection::DSN_NODE.c_str(), sDsn) );

	return node;
}

bool ODBCConnection::isValid()
{
	//TODO: PoolManager::isValid to developer.
    return true;
}
