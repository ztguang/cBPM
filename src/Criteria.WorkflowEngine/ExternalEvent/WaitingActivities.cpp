#include "CommonDefines.h"

#include "WaitingActivities.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

WaitingActivities::WaitingActivities() : XMLObjectSet()
{
	this->init();
}

WaitingActivities::WaitingActivities(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

WaitingActivities::~WaitingActivities()
{
}

void WaitingActivities::init()
{
}

bool WaitingActivities::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool WaitingActivities::parse(XMLAttribute* attribute)
{
	return false;
}

bool WaitingActivities::parse(XMLNode* node)
{
	if ( !strcmp(node->getName(),XMLWaitingActivity::MAIN_NODE.c_str()) )
    {
		WaitingActivity* activity = new WaitingActivity(node);
		bOS::Collections::Collection::add((bOS::Collections::CollectionEntry*)activity);
    }

	return true;
}

XMLNode* WaitingActivities::getXMLNode(unsigned int uiHow)
{
	XMLNode* root = new XMLNode( XMLWaitingActivities::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	WaitingActivity* activity=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		activity = (WaitingActivity*)(this->at(i));
		root->addNode( activity->getXMLNode(uiHow) );
	}
    
    return root;
}

bool WaitingActivities::isValid()
{
	return true;
}