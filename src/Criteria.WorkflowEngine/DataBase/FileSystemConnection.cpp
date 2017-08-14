#include "CommonDefines.h"

#include "FileSystemConnection.h"
using namespace DataManager::Panorama::DataBase;

FileSystemConnection::FileSystemConnection() : Connection()
{
	this->init();
}

FileSystemConnection::FileSystemConnection( XMLNode* node ) : Connection(node)
{
	XMLObject::init(node);
}

FileSystemConnection::~FileSystemConnection()
{
}

void FileSystemConnection::init()
{
	Connection::init();

	idType=4;
}

bool FileSystemConnection::init (XMLNode* node)
{
	CM_CODEBLOCK(FileSystemConnection::init)
	return Connection::init(node);
}

bool FileSystemConnection::parse( XMLAttribute* attribute)
{
	if ( Connection::parse(attribute) )
	{
		return true;
	}

	return false;
}

bool FileSystemConnection::parse( XMLNode* node)
{
	if ( Connection::parse(node) )
	{
		return true;
	}
	else
	{
		return false;
	}
        
	return true;
}

XMLNode* FileSystemConnection::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(Connection::getXmlNode)
    
    XMLNode* node = Connection::getXMLNode(iHow);
	node->setName ( XMLFileSystemConnection::MAIN_NODE.c_str());

	return node;
}

bool FileSystemConnection::isValid()
{
	//TODO: PoolManager::isValid to developer.
    return true;
}
