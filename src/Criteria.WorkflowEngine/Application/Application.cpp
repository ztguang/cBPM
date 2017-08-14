#include "CommonDefines.h"

#include "Application.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

using namespace bOS::XML;

#include "Tracer.h"

Application::Application() : XMLObject()
{
	this->init();
}

Application::Application(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

Application::~Application()
{
}

void Application::init()
{
	sName="";
	sHost="";
	iPort=0;
	sType = XMLApplication::EXECUTABLE_TYPE;
	sLibrary="";

	vFunctions.init();
	vExtendedAttributes.init();
}

bool Application::init (bOS::XML::XMLNode* node)
{
	return XMLObject::init (node);
}

bool Application::init(bOS::IO::File& file)
{
	return XMLObject::init(file);
}

bool Application::parse(XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLApplication::NAME_ATTRIBUTE.c_str()) )
	{
		sName = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLApplication::TYPE_ATTRIBUTE.c_str() ) )
	{
		sType = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLApplication::DLL_ATTRIBUTE.c_str()) )
	{
		sLibrary = attribute->getValue();
	}
	else
		return false;

	return true;
}

bool Application::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLApplicationFunctions::MAIN_NODE.c_str()) )
    {
		return vFunctions.init(node);
    }
	else if ( !strcmp(node->getName(),XMLApplication::HOST_NODE.c_str()) )
    {
		sHost = node->getValue();
    }
	else if ( !strcmp(node->getName(),XMLApplication::PORT_NODE.c_str()) )
    {
		iPort = node->getIntValue();
    }
	else if ( !strcmp(node->getName(), DataManager::Panorama::Common::XMLExtendedAttributes::MAIN_NODE.c_str() ) )
	{
		return vExtendedAttributes.init(node);
	}
	else
		return false;

	return true;
}

XMLNode* Application::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode( XMLApplication::MAIN_NODE.c_str(), "" );
	root->addAttribute ( new XMLAttribute(XMLApplication::NAME_ATTRIBUTE.c_str(), sName) );
	root->addAttribute ( new XMLAttribute(XMLApplication::TYPE_ATTRIBUTE.c_str(), sType ));
	root->addAttribute ( new XMLAttribute(XMLApplication::DLL_ATTRIBUTE.c_str(), sLibrary ));

	
	root->addNode ( vFunctions.getXMLNode(iHow));

	if ( strcmp(sType.c_str(), XMLApplication::LIBRARY_TYPE.c_str() ) )
	{
		root->addNode ( new XMLNode(XMLApplication::HOST_NODE.c_str(),sHost));
		root->addNode ( new XMLNode(XMLApplication::PORT_NODE.c_str(),iPort));
	}

	root->addNode ( vExtendedAttributes.getXMLNode(iHow));
    
    return root;
}

bool Application::equalTo(bOS::Collections::CollectionEntry* entry)
{
	CM_CODEBLOCK(Application::equalTo)

	Application* application = (Application*)entry;

	CM_TRACE_DEBUG("Check [" << application->getName() << "] [" << this->getName() << "]")
	if ( strcmp(application->getName().c_str(), this->getName().c_str()) ==  0 )
		return true;

	return false;
}