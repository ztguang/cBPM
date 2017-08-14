#include "CommonDefines.h"

#include "ExtendedAttribute.h"
using namespace DataManager::Panorama::Common;

using namespace bOS::XML;

ExtendedAttribute::ExtendedAttribute() : XMLObject()
{
	this->init();
}

ExtendedAttribute::ExtendedAttribute(XMLNode* root) : XMLObject()
{
	XMLObject::init(root);

	sInnerText = root->getInnerXML();
}

ExtendedAttribute::~ExtendedAttribute()
{
}

void ExtendedAttribute::init()
{
	sName="";
	sValue="";
	sInnerText="";
}

XMLNode* ExtendedAttribute::getXMLNode(unsigned int iHow)
{
    CM_CODEBLOCK(ExtendedAttribute::getXMLNode)
    
    XMLNode* root = new XMLNode( XMLExtendedAttribute::MAIN_NODE.c_str(), "" );
	root->addAttribute( new XMLAttribute( XMLExtendedAttribute::NAME_ATTRIBUTE.c_str(), sName.c_str()) );
	root->addAttribute( new XMLAttribute( XMLExtendedAttribute::VALUE_ATTRIBUTE.c_str(), sValue.c_str()) );

	if ( sInnerText.length() > 0 )
	{
		XMLNode* node = new XMLNode();
		node->setValue(sInnerText.c_str() );
		root->addNode( node );
	}

	return root;
}

bool ExtendedAttribute::isValid()
{
    if ( sName == "" )
        return false;

    return true;
}

bool ExtendedAttribute::parse(XMLAttribute* attribute)
{
    if ( strcmp(attribute->getName(),XMLExtendedAttribute::NAME_ATTRIBUTE.c_str() ) == 0 )
	{
        sName = attribute->getValue();
	}
    else if ( strcmp(attribute->getName(),XMLExtendedAttribute::VALUE_ATTRIBUTE.c_str()) == 0 )
	{
        sValue = attribute->getValue();
	}

	return true;
}

bool ExtendedAttribute::parse(XMLNode* node)
{
	return false;
}