#include "CommonDefines.h"

#include "Grant.h"
using namespace DataManager::Panorama::Common;

using namespace bOS::XML;

Grant::Grant() : XMLObject()
{
	this->init();
}

Grant::Grant( XMLNode* root ) : XMLObject()
{
	XMLObject::init(root);
}

Grant::~Grant()
{
}

void Grant::init()
{
	bEnabled=false;
}

bool Grant::parse (XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName() ,XMLGrant::ENABLED_ATTRIBUTE.c_str() ) == 0 )
	{
		bEnabled = !strcmp(attribute->getValue(),XMLGrant::YES_ENABLED.c_str()) ? true : false;
	}
	else if ( strcmp(attribute->getName() ,XMLGrant::TYPE_ATTRIBUTE.c_str() ) == 0 )
	{
		sType = attribute->getValue();
	}
	else
		return false;
	
	return true;
}

bool Grant::parse (XMLNode* node)
{
	if ( strcmp(node->getName(),XMLRoles::MAIN_NODE.c_str()) == 0 )
	{
        vRoles.init(node);
	}

	else if ( strcmp(node->getName(),XMLUsers::MAIN_NODE.c_str()) == 0 )
	{
        vUsers.init(node );
	}
	else
		return false;

	return true;
}

XMLNode* Grant::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode( XMLGrant::MAIN_NODE.c_str(), "" );

	root->addAttribute( new XMLAttribute( XMLGrant::ENABLED_ATTRIBUTE.c_str(), bEnabled ? XMLGrant::YES_ENABLED : XMLGrant::NO_ENABLED) );
	root->addAttribute( new XMLAttribute( XMLGrant::TYPE_ATTRIBUTE.c_str(), sType));

    root->addNode( vUsers.getXMLNode(1) );
	root->addNode( vRoles.getXMLNode(1) );

    return root;
}