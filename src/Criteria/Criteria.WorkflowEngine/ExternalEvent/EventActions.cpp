#include "CommonDefines.h"

#include "EventActions.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

#include "Tracer.h"

EventActions::EventActions() : XMLObjectSet()
{
	this->init();
}

EventActions::EventActions(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

EventActions::~EventActions()
{
}

void EventActions::init()
{
	XMLObjectSet::init();
}

bool EventActions::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool EventActions::parse(XMLNode* root)
{
	if ( !strcmp(root->getName(),XMLScenarioEventAction::MAIN_NODE.c_str()) )
    {
		ScenarioEventAction* action = new ScenarioEventAction(root);
		XMLObjectSet::add((CollectionEntry*)action);
    }
	else
		return false;

	return true;
}

XMLNode* EventActions::getXMLNode(unsigned int iHow)
{
	XMLNode* root= new XMLNode( XMLEventActions::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	ScenarioEventAction* action=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		action = (ScenarioEventAction*)(this->at(i));
		root->addNode( action->getXMLNode(iHow) );
	}
    
    return root;
}