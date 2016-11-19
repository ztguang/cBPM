#include "CommonDefines.h"

#include "Connections.h"
#include "SQLiteConnection.h"
#include "mySQLConnection.h"
#include "ODBCConnection.h"
#include "FileSystemConnection.h"
using namespace DataManager::Panorama::DataBase;

Connections::Connections() : XMLObjectSet()
{
	this->init();
}

Connections::Connections( XMLNode* node ) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Connections::~Connections()
{
}

void Connections::init()
{
	XMLObjectSet::init();
}

bool Connections::init (bOS::XML::XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool Connections::parse( XMLAttribute* attribute)
{
	return true;
}

bool Connections::parse( XMLNode* node)
{
	Connection* connection= NULL;

	if ( strcmp(node->getName(),XMLODBCConnection::MAIN_NODE.c_str()) == 0 )
	{
		/*connection = new ODBCConnection(node);
		this->add((bOS::Collections::CollectionEntry*)connection);
		*/
	}
	else if ( strcmp(node->getName(),XMLSQLiteConnection::MAIN_NODE.c_str()) == 0 )
	{
		connection = new SQLiteConnection(node);    
		this->add((bOS::Collections::CollectionEntry*)connection);
	}
	else if ( strcmp(node->getName(),XMLmySQLConnection::MAIN_NODE.c_str()) == 0 )
	{
		connection = new mySQLConnection(node);    
		this->add((bOS::Collections::CollectionEntry*)connection);
	}
	else if ( strcmp(node->getName(), XMLFileSystemConnection::MAIN_NODE.c_str() ) == 0 )
	{
		connection = new FileSystemConnection(node);
		this->add((bOS::Collections::CollectionEntry*)connection);
	}
	else
	{
		return false;
	}
        
	return true;
}

XMLNode* Connections::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(Connection::getXmlNode)
    
    XMLNode* node = new XMLNode( XMLConnections::MAIN_NODE.c_str(), "" );

	unsigned int uiSize= this->size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Connection* connection = (Connection*)this->at(i);
		node->addNode ( connection->getXMLNode(iHow) );
	}

	return node;
}

bool Connections::isValid()
{
	//TODO: PoolManager::isValid to developer.
    return true;
}

Connection* Connections::getPrimary()
{
	unsigned int uiSize = this->size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Connection* connection = (Connection*)this->at(i);

		if ( connection->isPrimary() )
			return connection;
	}

	return NULL;
}
