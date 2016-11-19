#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringBuffer.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSFileSystem.h"
using namespace bOS::IO;

#include "bOSFileSystemException.h"
using namespace bOS::Exception;

#include "bOSXMLHelper.h"
#include "bOSXMLNode.h"
using namespace bOS::XML;

#include "bOSXMLFile.h"
#include "bOSXMLDirectory.h"
using namespace bOS::XML::Data;

String XMLTable::MAIN_NODE		= "Table";
String XMLTable::SEQUENCE_NODE	= "Sequence";

String XMLDirectory::FILENAME	= "Table.xml";

XMLTable::XMLTable() : XMLFile()
{
}

XMLTable::XMLTable(bOS::XML::XMLNode* node) : XMLFile()
{
	XMLObject::init(node);
}

XMLTable::~XMLTable()
{
}

void XMLTable::init()
{
	XMLFile::init();
}

bool XMLTable::parse(XMLAttribute* attribute)
{
	return true;
}

bool XMLTable::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(), XMLTable::SEQUENCE_NODE.c_str()) )
	{
		lSequence = atol(node->getValue());
	}

	return true;
}

XMLNode* XMLTable::getXMLNode(unsigned int iHow)
{
	XMLNode* node = new XMLNode( XMLTable::MAIN_NODE.c_str(), "");
	//node->addNode( new XMLNode( XMLTable::SEQUENCE_NODE.c_str(), lSequence) );		//ztg delete
	node->addNode( new XMLNode( XMLTable::SEQUENCE_NODE.c_str(), (int)lSequence) );
	return node;
}

bool XMLTable::isValid()
{
	return true;
}

XMLDirectory::XMLDirectory()
{
}

XMLDirectory::XMLDirectory(const char* acPath, bool readBefore)
{
	this->init(acPath, readBefore);
}

XMLDirectory::~XMLDirectory()
{
}

void XMLDirectory::init(const char* acPath, bool readBefore)
{
	//
	sPath = acPath;
	String sTableFile = sPath;
	sTableFile+=SLASH;
	sTableFile+=FILENAME;

	bReadBefore = readBefore;

	xmlTable.load(sTableFile.c_str());
}

long XMLDirectory::increment()
{
	//TODO: locking table file where loading.

	Mutex::Lock locker(mtxIncrement);

	if ( bReadBefore )
	{
		xmlTable.reload();

	}

	long lSequence = xmlTable.getSequence();
	lSequence++;
	xmlTable.setSequence ( lSequence);

	StringBuffer sFile;
	sFile.append (sPath);
	sFile.append (SLASH);
	sFile.append (XMLDirectory::FILENAME);
	xmlTable.write2File(sFile.getData());

	return lSequence;
}

long XMLDirectory::insert(XMLFile* obj, bool bAutoIncrement)
{
	long lIdSequence=0;

	if ( bAutoIncrement )
	{
		lIdSequence = this->increment();
		obj->setSequence(lIdSequence);
	}
	else
	{
		lIdSequence = obj->getSequence();
	}

	obj->write ( sPath.c_str() );

	return lIdSequence;
}

long XMLDirectory::insert(XMLFile* obj, const String& sFileName, bool bAutoIncrement)
{
	long lIdSequence=0;

	if ( bAutoIncrement )
	{
		lIdSequence = this->increment();
		obj->setSequence(lIdSequence);
	}
	else
	{
		lIdSequence = obj->getSequence();
	}

	StringBuffer sFile;
	sFile.append(sPath);
	sFile.append(SLASH);
	sFile.append(sFileName);
	sFile.append(".xml");

	obj->write2File(sFile.getData());

	return lIdSequence;
}

bool XMLDirectory::update(XMLFile* obj)
{
	StringBuffer sFile;
	sFile.append(sPath);
	sFile.append(SLASH);
	sFile.append(obj->getFileName());
	sFile.append(".xml");

	obj->write2File(sFile.getData());

	return true;
}

bool XMLDirectory::erase(XMLFile* obj)
{
	StringBuffer sFile;
	sFile.append(sPath);
	sFile.append(SLASH);
	sFile.append(obj->getFileName());
	sFile.append(".xml");

	try
	{
		FileSystem::deleteFile (sFile.getData());
	}
	catch ( FileSystemException&)
	{
		return false;
	}

	return true;
}

void XMLDirectory::get(XMLFile* obj)
{
	StringBuffer sFile;
	sFile.append(sPath);
	sFile.append(SLASH);
	sFile.append(obj->getFileName());
	sFile.append(".xml");

	obj->load(sFile.getData());
}

void XMLDirectory::get(XMLFile* obj, const String& sFileName)
{
	String sFile=sPath;
	sFile+="\\";
	sFile+=sFileName;

	//if ( sFileName.find(".xml") == - 1)       //ztg delete
	if ( (int)sFileName.find(".xml") == - 1)
	{
		sFile+=".xml";
	}

	obj->load(sFile.c_str());
}

FilesList XMLDirectory::list()
{
	FilesList files;

	FileSystem::ls(this->sPath, files,".xml");

	FilesList::iterator i=files.begin();
	for ( ; i<=files.end(); i++)
	{
		String sFile = *i;

		if ( strcmp( sFile.c_str(), "table.xml") == 0 )
		{
			files.erase (i);
		}
	}

	return files;
}

