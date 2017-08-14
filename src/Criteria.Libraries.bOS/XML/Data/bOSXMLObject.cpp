#include "CommonDefines.h"

#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSCollection.h"
using namespace bOS::Collections;

#include "bOSXMLHelper.h"
#include "bOSXMLException.h"
using namespace bOS::XML;

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

XMLObject::XMLObject()
{
	this->init();
}

XMLObject::XMLObject(XMLNode* node)
{
	this->init(node);
}

XMLObject::XMLObject(const char* acXML)
{
	this->init(acXML);
}

XMLObject::~XMLObject()
{
}

void XMLObject::init()
{
	;
}

bool XMLObject::init(const char* acXML)
{
	XMLNode* node = NULL;
	try
	{
		node = XMLHelper::parseFromString(acXML);
	}
	catch ( bOS::XML::XMLException& xmlErr) 
	{
		cerr << "Impossible to parse[" << acXML << "].Err[" << xmlErr.getMessage() << "]" << endl;
		throw;
	}

	bool bRet = this->init(node);
	delete node;

	return bRet;
}

bool XMLObject::init(XMLNode* root)
{
	this->init();

	bool bRet = true;

	Collection& vAttributes = root->getAttributes();
	unsigned int uiSize = vAttributes.size();
	XMLAttribute* attribute=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		attribute = (XMLAttribute*)vAttributes[i];

		if ( this->parse(attribute) )
		{
		}
		else
		{
			bRet = false;
		}
	}

	Collection& vNodes = root->getNodes();
	uiSize = vNodes.size();
	XMLNode* node=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		node = (XMLNode*)vNodes[i];

		if ( this->parse(node) )
		{
		}
		else
		{
			bRet = false;
		}
	}

	return bRet;
}

bool XMLObject::init (bOS::IO::File& file)
{
	XMLNode* root = XMLHelper::parseFromFile ( file.getFileName() );
	bool bRet = true;

	Collection& vAttributes = root->getAttributes();
	unsigned int uiSize = vAttributes.size();
	XMLAttribute* attribute=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		attribute = (XMLAttribute*)vAttributes[i];

		if ( this->parse(attribute) )
		{
		}
		else
		{
			bRet = false;
		}
	}

	Collection& vNodes = root->getNodes();
	uiSize = vNodes.size();
	XMLNode* node=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		node = (XMLNode*)vNodes[i];

		if ( this->parse(node) )
		{
		}
		else
		{
			bRet = false;
		}
	}

	delete root;

	return bRet;
}

String XMLObject::getXMLString(unsigned int iHow)
{
	XMLNode* node=NULL;
	try
	{
		node = this->getXMLNode(iHow);
	}
	catch( XMLException& xpe )
	{
		throw xpe;
	}

	String sXML = node->getXMLText();
	delete node;

	return sXML;
}