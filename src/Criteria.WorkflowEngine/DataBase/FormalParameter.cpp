#include "CommonDefines.h"

#include "FormalParameter.h"
using namespace DataManager::Panorama::Common;

using namespace bOS::XML;

#include "Tracer.h"

FormalParameter::FormalParameter() : XMLObject()
{
	this->init();
}

FormalParameter::FormalParameter( XMLNode* node ) : XMLObject()
{
	bool bRet = XMLObject::init(node);

	/*sValue = node->getValue();

	if ( sValue.length() == 0 )
	{
		sValue=node->getInnerXML();
	}*/
}

FormalParameter::FormalParameter(const String& sNameValue, const String& sValueValue) : XMLObject()
{
	XMLObject::init();

	sName = sNameValue;
	sValue = sValueValue;
}

FormalParameter::~FormalParameter()
{
}

void FormalParameter::init()
{
	sName="";
	sValue="";
	sType=XMLFormalParameter::STRING_TYPE;
	bMandatory=false;
	sBind="";
}

bool FormalParameter::parse(XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(),XMLFormalParameter::NAME_ATTRIBUTE.c_str()) )
	{
		sName = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLFormalParameter::TYPE_ATTRIBUTE.c_str()) )
	{
		sType = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLFormalParameter::MANDATORY_ATTRIBUTE.c_str()) )
	{
		bMandatory = !strcmp(attribute->getValue(), "YES") ? true : false;
	}
	else 
		return false;

	return true;

}

bool FormalParameter::parse(XMLNode* root)
{
	if ( !strcmp(root->getName(), XMLFormalParameter::BIND_NODE.c_str()) )
	{
		sBind = root->getValue();
	}
	else if ( strcmp(root->getName(), XMLFormalParameter::VALUE_NODE.c_str() ) == 0 )
	{
		if (strcmp(sType.c_str(), XMLFormalParameter::XML_TYPE.c_str() ) == 0 )
		{
			sValue = root->getInnerXML();
		
			if ( sValue.length() == 0 )
			{
				sValue = root->getValue();
			}
		}
		else
		{
			sValue = root->getValue();
		}
	}
	else
		return false;

	return true;
}

XMLNode* FormalParameter::getXMLNode(unsigned int iHow)
{
	XMLNode* nd = new XMLNode( XMLFormalParameter::MAIN_NODE.c_str(), "");
	nd->addAttribute ( new XMLAttribute(XMLFormalParameter::NAME_ATTRIBUTE.c_str(), sName) );
	nd->addAttribute ( new XMLAttribute(XMLFormalParameter::TYPE_ATTRIBUTE.c_str(), sType) );
	nd->addAttribute ( new XMLAttribute(XMLFormalParameter::MANDATORY_ATTRIBUTE.c_str(), bMandatory ? "YES" : "NO") );

	if ( iHow == 0 )
		nd->addNode( new XMLNode( XMLFormalParameter::BIND_NODE.c_str(), sBind ) );

	int iPos = sValue.find ("<");

	if ( iPos != -1) 
	{
		sValue = "<![CDATA[" + sValue + "]]>";
	}

	nd->addNode ( new XMLNode(XMLFormalParameter::VALUE_NODE.c_str(), sValue) );

    return nd;
}

void FormalParameter::setXMLType()
{
	this->sType = XMLFormalParameter::XML_TYPE;
}

bool FormalParameter::equalTo(bOS::Collections::CollectionEntry* entry)
{
	FormalParameter* parameter = (FormalParameter*)entry;

	if ( !strcmp(parameter->getName().c_str(), this->getName().c_str()) )
	{
		return true;
	}

	return false;
}
