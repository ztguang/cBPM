#include "CommonDefines.h"

#include "Transitions.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

Transitions::Transitions() : XMLObjectSet()
{
	this->init();
}

Transitions::Transitions(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Transitions::~Transitions()
{
}

void Transitions::init()
{
	XMLObjectSet::init();
}

bool Transitions::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool Transitions::init(const char* acXML)
{
	return XMLObjectSet::init(acXML);
}

bool Transitions::parse(XMLAttribute* attribute)
{
	return false;
}

bool Transitions::parse(XMLNode* node)
{
	if ( strcmp(node->getName(),XMLTransition::MAIN_NODE.c_str()) == 0 )
	{
		Transition* transition = new Transition(node);
		this->add( (CollectionEntry*)transition);
	}
	else
		return false;

	return true;
}

XMLNode* Transitions::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode(XMLTransitions::MAIN_NODE.c_str(), "" );
	unsigned int uiSize=this->size();
	Transition* transition=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		transition = (Transition*)(this->at(i));
		root->addNode( transition->getXMLNode(iHow) );
	}

    return root;
}

void Transitions::addTransitions(Transitions& vTransitions)
{
	int iSize = vTransitions.size();
	for ( int i=0; i<iSize; i++)
	{
		Transition* transition = (Transition*)vTransitions.at(i);

		XMLNode* node = transition->getXMLNode(0);
		Transition* newTrans = new Transition(node);
		delete node;
		
		add(newTrans);
	}
}