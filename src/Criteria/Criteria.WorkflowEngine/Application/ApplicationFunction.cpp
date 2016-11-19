#include "CommonDefines.h"

#include "ApplicationFunction.h"
#include "Application.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

using namespace bOS::XML;

#include "Tracer.h"

ApplicationFunction::ApplicationFunction() : XMLObject()
{
	this->init();
}

ApplicationFunction::ApplicationFunction(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

ApplicationFunction::~ApplicationFunction()
{
}

void ApplicationFunction::init()
{
	sName="";
	sType="";

	vParameters.init();
	result.init();
}

bool ApplicationFunction::init(bOS::XML::XMLNode* node)
{
	return XMLObject::init (node);
}

bool ApplicationFunction::init(const char* acXML)
{
	return XMLObject::init(acXML);
}

bool ApplicationFunction::parse(XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLApplicationFunction::NAME_ATTRIBUTE.c_str() ) )
	{
		sName = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLApplicationFunction::TYPE_ATTRIBUTE.c_str() ) )
	{
		sType = attribute->getValue();
	}
	else
		return false;

	return true;
}

bool ApplicationFunction::parse(XMLNode* root)
{
	if ( !strcmp(root->getName(),Common::XMLFormalParameters::MAIN_NODE.c_str()) )
    {
		return vParameters.init(root);
    }
	else if ( !strcmp(root->getName(),XMLApplication::MAIN_NODE.c_str()) )
	{
		sApplication = root->getValue();
	}
	else if ( !strcmp(root->getName(), XMLApplicationFunctionResult::MAIN_NODE.c_str()) )
	{
		return result.init(root);
	}
	else
		return false;

	return true;
}

XMLNode* ApplicationFunction::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode( XMLApplicationFunction::MAIN_NODE.c_str(), "" );

	root->addAttribute ( new XMLAttribute(XMLApplicationFunction::NAME_ATTRIBUTE.c_str(), sName.c_str()) );
	root->addAttribute ( new XMLAttribute(XMLApplicationFunction::TYPE_ATTRIBUTE.c_str(), sType.c_str()) );

	root->addNode( new XMLNode( XMLApplication::MAIN_NODE.c_str(), sApplication.c_str() ) );

	root->addNode ( vParameters.getXMLNode(iHow) );
	root->addNode ( result.getXMLNode(iHow) );
    
    return root;
}

bool ApplicationFunction::equalTo(bOS::Collections::CollectionEntry* entry)
{
	ApplicationFunction* function = (ApplicationFunction*)entry;

	if ( strcmp(function->getName().c_str(), this->getName().c_str() ) == 0 )
		return true;

	return false;
}

bool ApplicationFunction::isScriptable()
{
	if ( strcmp(sType.c_str(), XMLApplicationFunction::SCRIPT_TYPE.c_str()) == 0 )
	{
		return true;
	}

	return false;
}