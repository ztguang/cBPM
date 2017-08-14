#include "CommonDefines.h"

#include "SQLiteConnection.h"
using namespace DataManager::Panorama::DataBase;

#include "bOSSystem.h"

SQLiteConnection::SQLiteConnection() : Connection()
{
	this->init();
}

SQLiteConnection::SQLiteConnection( XMLNode* node ) : Connection(node)
{
	XMLObject::init(node);
}

SQLiteConnection::~SQLiteConnection()
{
}

void SQLiteConnection::init()
{
	Connection::init();

	sPath="";
	sDataBase="";

	idType=3;
}

bool SQLiteConnection::parse( XMLAttribute* attribute)
{
	if ( Connection::parse(attribute) )
	{
		return true;
	}

	return false;
}

bool SQLiteConnection::parse( XMLNode* node)
{
	if ( Connection::parse(node) )
	{
		return true;
	}
	else if ( strcmp(node->getName(),XMLSQLiteConnection::DATABASE_NODE.c_str()) == 0 )
	{
        sDataBase = node->getValue();
	}
	else if ( strcmp(node->getName(),XMLSQLiteConnection::PATH_NODE.c_str()) == 0 )
	{
        sPath = bOS::CoreSystem::System::expandEnvironmentStrings(node->getValue());
	}
	else
	{
		return false;
	}
        
	return true;
}

XMLNode* SQLiteConnection::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(SQLiteConnection::getXmlNode)
    
    XMLNode* node = Connection::getXMLNode(iHow);
	node->setName ( XMLSQLiteConnection::MAIN_NODE.c_str());

	node->addNode( new XMLNode(XMLSQLiteConnection::PATH_NODE.c_str(), sPath) );
	node->addNode( new XMLNode(XMLSQLiteConnection::DATABASE_NODE.c_str(), sDataBase) );

	return node;
}

bool SQLiteConnection::isValid()
{
	//TODO: PoolManager::isValid to developer.
    return true;
}
