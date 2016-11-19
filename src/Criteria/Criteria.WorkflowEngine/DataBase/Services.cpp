#include "CommonDefines.h"

#include "Services.h"
using namespace DataManager::Panorama::WorkflowServices;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

Services::Services() : XMLObjectSet()
{
	this->init();
}

Services::Services(XMLNode* node ) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Services::~Services(void)
{
}

void Services::init()
{
	XMLObjectSet::init();
}

bool Services::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool Services::init(const char* acXML)
{
	return XMLObjectSet::init(acXML);
}

//bool Services::init(bOS::IO::File& file)     //ztg delete
bool Services::init(bOS::IO::File file)
{
	return XMLObjectSet::init(file);
}

bool Services::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLService::MAIN_NODE.c_str() ) )
    {
		Service* service = new Service(node);
		this->add((CollectionEntry*)service);
    }
	else
	{
		return false;
	}

	return true;
}

bool Services::parse(XMLAttribute* attribute)
{
	return true;
}

bool Services::isValid()
{
	return true;
}

XMLNode* Services::getXMLNode(unsigned int iHow)
{
    XMLNode* root= new XMLNode( XMLServices::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	Service* service=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		service = (Service*)(this->at(i));
		root->addNode( service->getXMLNode(iHow) );
	}

    return root;
}

bool Services::addService(const char* acService)
{
	Service* service2Add = new Service(acService);
	return this->add((CollectionEntry*)service2Add);
}

bool Services::deleteService(const char* acServiceName)
{
	Service service;
	service.setName(acServiceName);

	return  this->remove((CollectionEntry*)(&service));
}
