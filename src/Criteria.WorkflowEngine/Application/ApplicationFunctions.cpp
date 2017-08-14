#include "CommonDefines.h"

#include "ApplicationFunctions.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

#include "Tracer.h"

ApplicationFunctions::ApplicationFunctions() : XMLObjectSet()
{
	this->init();
}

ApplicationFunctions::ApplicationFunctions(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

ApplicationFunctions::~ApplicationFunctions()
{
}

void ApplicationFunctions::init()
{
	XMLObjectSet::init();
}

bool ApplicationFunctions::init (XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool ApplicationFunctions::parse(XMLNode* root)
{
    if ( !strcmp(root->getName(),XMLApplicationFunction::MAIN_NODE.c_str()) )
    {
		ApplicationFunction* function = new ApplicationFunction(root);
		XMLObjectSet::add((CollectionEntry*)function);
    }
	else
		return false;

	return true;
}

XMLNode* ApplicationFunctions::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode( XMLApplicationFunctions::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	ApplicationFunction* function=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		function = (ApplicationFunction*)(this->at(i));
		root->addNode( function->getXMLNode(iHow) );
	}
    
    return root;
}


ApplicationFunction* ApplicationFunctions::get(const char* acName)
{
	ApplicationFunction function;
	function.setName ( acName);

	CollectionEntry* entry = (CollectionEntry*)&function;

	ApplicationFunction* function2Ret = (ApplicationFunction*)XMLObjectSet::get(entry);

	return function2Ret;
}