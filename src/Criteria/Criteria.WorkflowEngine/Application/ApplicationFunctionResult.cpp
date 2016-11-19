#include "CommonDefines.h"

#include "ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

using namespace bOS::XML;

#include "Tracer.h"

ApplicationFunctionResult::ApplicationFunctionResult() : XMLObject()
{
	this->init();
}

ApplicationFunctionResult::ApplicationFunctionResult(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

ApplicationFunctionResult::~ApplicationFunctionResult()
{
}

void ApplicationFunctionResult::init()
{
	lCode=0;
	sMessage="";

	vParameters.init();
}

bool ApplicationFunctionResult::init (XMLNode* node)
{
	return XMLObject::init(node);
}

bool ApplicationFunctionResult::init(const char* acXML)
{
	return XMLObject::init(acXML);
}

bool ApplicationFunctionResult::parse(XMLAttribute* attribute)
{
	CM_CODEBLOCK(parse)

	if ( !strcmp(attribute->getName(),XMLApplicationFunctionResult::CODE_ATTRIBUTE.c_str()) )
	{
		lCode = attribute->getLongValue();
	}
	else
		return false;

	return true;
}


bool ApplicationFunctionResult::parse(XMLNode* root)
{
	if ( !strcmp(root->getName(),Common::XMLFormalParameters::MAIN_NODE.c_str()) )
    {
		return vParameters.init(root);
    }
	else if ( !strcmp(root->getName(),XMLApplicationFunctionResult::MESSAGE_NODE.c_str()) )
    {
		sMessage = root->getValue();
    }
	else 
		return false;

	return true;
}

XMLNode* ApplicationFunctionResult::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode( XMLApplicationFunctionResult::MAIN_NODE.c_str(), "" );
	root->addAttribute( new XMLAttribute(XMLApplicationFunctionResult::CODE_ATTRIBUTE.c_str(), lCode ));

	root->addNode ( vParameters.getXMLNode(iHow) );
	root->addNode ( new XMLNode(XMLApplicationFunctionResult::MESSAGE_NODE.c_str(), sMessage ));

	return root;
}
