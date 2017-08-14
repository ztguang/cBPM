#include "CommonDefines.h"

#include "Behaviour.h"
#include "BehaviourBase.h"
#include "BehaviourStart.h"
#include "BehaviourFinish.h"
#include "BehaviourExecution.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

Behaviour::Behaviour() : XMLObjectSet()
{
	this->init();
}

Behaviour::Behaviour(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Behaviour::~Behaviour()
{
}

void Behaviour::init()
{
	XMLObjectSet::init();
}

bool Behaviour::init(bOS::XML::XMLNode* node)
{
	return XMLObjectSet::init (node);
}

bool Behaviour::init(const char* acXML)
{
	return XMLObjectSet::init (acXML);
}


bool Behaviour::parse(XMLAttribute* attribute)
{
	return false;
}

bool Behaviour::parse(XMLNode* node)
{
	if ( strcmp(node->getName(),XMLBehaviourStart::MAIN_NODE.c_str()) == 0 )
	{
		BehaviourStart* behaviour = new BehaviourStart(node);
		this->add( (CollectionEntry*)behaviour);
	}
	else if ( strcmp(node->getName(),XMLBehaviourFinish::MAIN_NODE.c_str()) == 0 )
	{
		BehaviourFinish* behaviour = new BehaviourFinish(node);
		this->add( (CollectionEntry*)behaviour);
	}
	else if ( strcmp(node->getName(),XMLBehaviourExecution::MAIN_NODE.c_str()) == 0 )
	{
		BehaviourExecution* behaviour = new BehaviourExecution(node);
		this->add( (CollectionEntry*)behaviour);
	}
	else
		return false;

	return true;
}

XMLNode* Behaviour::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode(XMLBehaviour::MAIN_NODE.c_str(), "" );
	unsigned int uiSize=this->size();
	BehaviourBase* behaviour=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		behaviour = (BehaviourBase*)(this->at(i));
		root->addNode( behaviour->getXMLNode(iHow) );
	}

    return root;
}

BehaviourBase* Behaviour::getBehaviour(String& sKey)
{
	BehaviourBase behaviour(sKey);
	CollectionEntry* entry = ( CollectionEntry*)&behaviour;

	BehaviourBase* base = (BehaviourBase*) this->get(entry);

	return base;
}

bool Behaviour::isAutomaticExecution()
{
	BehaviourBase* behaviour = getBehaviour(XMLBehaviourExecution::MAIN_NODE);

	if ( behaviour == NULL )
		return false;

	return behaviour->isAutomatic ();
}

bool Behaviour::isToRexecuteStart()
{
	BehaviourStart* behaviour = (BehaviourStart*)getBehaviour(XMLBehaviourStart::MAIN_NODE);

	if ( behaviour == NULL )
		return false;

	return behaviour->isToRexecute();
}

void Behaviour::setNotToRexecuteStart()
{
	BehaviourStart* behaviour = (BehaviourStart*)getBehaviour(XMLBehaviourStart::MAIN_NODE);

	assert(behaviour != NULL );
	
	if ( behaviour != NULL )
	{
		behaviour->setOnlyOne();
	}
}

BehaviourStart* Behaviour::getBehaviourStart()
{
	return (BehaviourStart*)getBehaviour(XMLBehaviourStart::MAIN_NODE);
}

BehaviourFinish* Behaviour::getBehaviourFinish()
{
	return (BehaviourFinish*)getBehaviour(XMLBehaviourFinish::MAIN_NODE);
}

BehaviourExecution* Behaviour::getBehaviourExecution()
{
	return (BehaviourExecution*)getBehaviour(XMLBehaviourExecution::MAIN_NODE);
}

String Behaviour::getDataType()
{
	BehaviourExecution* behaviour = (BehaviourExecution*)getBehaviour(XMLBehaviourExecution::MAIN_NODE);

	assert(behaviour != NULL );
	
	return behaviour->getScript().getDataType();
}

String Behaviour::getScriptCommand()
{
	BehaviourExecution* behaviour = (BehaviourExecution*)getBehaviour(XMLBehaviourExecution::MAIN_NODE);

	assert(behaviour != NULL );
	
	return behaviour->getScript().getCommand();
}

String Behaviour::getScriptType()
{
	BehaviourExecution* behaviour = (BehaviourExecution*)getBehaviour(XMLBehaviourExecution::MAIN_NODE);

	assert(behaviour != NULL );
	
	return behaviour->getScript().getType();
}
