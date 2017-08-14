#include "CommonDefines.h"

#include "Applications.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

using namespace bOS::XML;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

#include "Tracer.h"

Applications::Applications() : XMLObjectSet()
{
	this->init();
}

Applications::Applications(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Applications::~Applications()
{
}

void Applications::init ()
{
	XMLObjectSet::init();
}

bool Applications::init(XMLNode* root)
{
	return XMLObjectSet::init(root);
}

//bool Applications::init(bOS::IO::File& file)     //ztg delete
bool Applications::init(bOS::IO::File file)
{
	return XMLObjectSet::init(file);
}

bool Applications::parse(XMLNode* node)
{
	if ( strcmp(node->getName(),XMLApplication::MAIN_NODE.c_str()) == 0 )
    {
		Application* application = new Application(node);
		XMLObjectSet::add((CollectionEntry*)application);
    }
	else
		return false;

	return true;
}

bOS::XML::XMLNode* Applications::getXMLNode(unsigned int iHow)
{
	bOS::XML::XMLNode* root= new bOS::XML::XMLNode( XMLApplications::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	Application* application=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		application = (Application*)(this->at(i));
		root->addNode( application->getXMLNode(iHow) );
	}

    return root;
}

Application* Applications::get(const char* acApplicationName)
{
	Application application;
	application.setName ( acApplicationName);

	CollectionEntry* entry = (CollectionEntry*)&application;

	Application* application2Ret = (Application*)XMLObjectSet::get(entry);

	return application2Ret;
}

