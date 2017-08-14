#include "CommonDefines.h"

#include "Script.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

Script::Script() : XMLObject()
{
	this->init();
}

Script::Script( XMLNode* root ) : XMLObject()
{
	XMLObject::init(root);
}

Script::~Script()
{
}

bool Script::init(XMLNode* node)
{
	bool bRet = XMLObject::init(node);

	if ( sCommand.length() == 0 )
	{
		sCommand = node->getValue();
	}

	return bRet;
}

void Script::init()
{
	sDataType="";
	sType = XMLScript::NONE_TYPE;
	sCommand="";
}

bool Script::parse (XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName() ,XMLScript::TYPE_ATTRIBUTE.c_str() ) == 0 )
	{
		sType = attribute->getValue();
	}
	else if ( strcmp(attribute->getName() ,XMLScript::DATATYPE_ATTRIBUTE.c_str() ) == 0 )
	{
		sDataType = attribute->getValue();
	}
	else
		return false;
	
	return true;
}

bool Script::parse (XMLNode* node)
{
	if ( strcmp(node->getName(), "Function") == 0 )
	{
		sCommand = node->getXMLText();
	}
	else
		return false;

	return true;
}

XMLNode* Script::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode( XMLScript::MAIN_NODE.c_str(), "" );

	root->addAttribute( new XMLAttribute( XMLScript::TYPE_ATTRIBUTE.c_str(), sType));
	root->addAttribute( new XMLAttribute( XMLScript::DATATYPE_ATTRIBUTE.c_str(), sDataType));

	root->setValue ( sCommand.c_str());

    return root;
}