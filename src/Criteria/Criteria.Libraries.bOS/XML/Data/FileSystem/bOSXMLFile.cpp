#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

#include "bOSXMLHelper.h"
#include "bOSXMLNode.h"
#include "bOSXMLException.h"
using namespace bOS::XML;

#include "bOSXMLFile.h"
using namespace bOS::XML::Data;

XMLFile::XMLFile() : XMLObject()
{
}

XMLFile::XMLFile(bOS::XML::XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

XMLFile::~XMLFile()
{
	this->close();
}

void XMLFile::init()
{
	sFileName="";
}

bool XMLFile::init(bOS::XML::XMLNode* node)
{
	return XMLObject::init(node);
}

bool XMLFile::init(const char* acXML)
{
	return XMLObject::init(acXML);
}

void XMLFile::load(const char* acFileName)
{
	XMLNode* root = NULL;
	try
	{
		root = XMLHelper::parseFromFile(acFileName);
	}
	catch( XMLException& xe)
	{
		throw xe;
	}
	
	this->init(root);
	sFileName = acFileName;
	delete root;
}

void XMLFile::reload()
{
	if ( sFileName != "" )
	{
		this->load(sFileName.c_str());
	}
}

void XMLFile::close()
{
}

void XMLFile::write(const char* acPath)
{
	XMLNode* root = this->getXMLNode(0);

	StringBuffer sFile;
	if ( acPath != NULL )
	{
		sFile.append (acPath);
		sFile.append (SLASH);
	}
	sFile.append (this->getFileName());
	sFile.append (".xml");

	XMLHelper::saveToFile ( sFile.getData(), root);

	delete root;
}

void XMLFile::write2File(const char* acFileName)
{
	XMLNode* root = this->getXMLNode(0);

	XMLHelper::saveToFile ( acFileName, root);

	delete root;
}

void XMLFile::loadAndInit(const char* acFileName, XMLObject* xmlObject)
{
	XMLNode* root = NULL;
	try
	{
		root = XMLHelper::parseFromFile(acFileName);
	}
	catch( XMLException& xe)
	{
		throw xe;
	}

	xmlObject->init(root);

	delete root;
}

