#include "CommonDefines.h"

#include "ExtendedAttributes.h"
using namespace DataManager::Panorama::Common;

using namespace bOS::XML;
using namespace bOS::XML::Data;

ExtendedAttributes::ExtendedAttributes() : XMLObjectSet()
{
	this->init();
}

ExtendedAttributes::ExtendedAttributes( XMLNode* root) : XMLObjectSet()
{
	XMLObjectSet::init(root);
}

ExtendedAttributes::~ExtendedAttributes()
{
}

bool ExtendedAttributes::parse(XMLAttribute* attribute)
{
	return true;
}

bool ExtendedAttributes::parse(XMLNode* node)
{
	if ( strcmp(node->getName(),XMLExtendedAttribute::MAIN_NODE.c_str()) == 0 )
	{
		this->add(new ExtendedAttribute(node));
	}

	return true;
}

XMLNode* ExtendedAttributes::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLExtendedAttributes::MAIN_NODE.c_str(), "" );
	unsigned int uiSize = this->size();
	ExtendedAttribute* attribute=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		attribute = (ExtendedAttribute*)(this->at(i));
		root->addNode( attribute->getXMLNode(iHow) );
	}

    return root;
}

ExtendedAttribute* ExtendedAttributes::get(const String& sName, const String& sValue)
{
	unsigned int uiSize = this->size();
	ExtendedAttribute* attribute=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		attribute = (ExtendedAttribute*)(this->at(i));
		if ( (attribute->getName() == sName) && ( attribute->getValue() == sValue) )
		{
			return attribute;
		}
	}

	return NULL;
}