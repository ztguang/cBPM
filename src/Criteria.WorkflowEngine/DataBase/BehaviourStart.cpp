#include "CommonDefines.h"

#include "BehaviourStart.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

BehaviourStart::BehaviourStart() : BehaviourBase(XMLBehaviourStart::MAIN_NODE)
{
	this->init();
}

BehaviourStart::BehaviourStart( XMLNode* node ) : BehaviourBase(XMLBehaviourStart::MAIN_NODE)
{
	XMLObject::init(node);
}

BehaviourStart::~BehaviourStart()
{
}

void BehaviourStart::init()
{
}

bool BehaviourStart::parse (XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName() ,XMLBehaviourStart::ONLYONE_ATTRIBUTE.c_str() ) == 0 )
	{
		bOnlyOne = !strcmp(attribute->getValue(),XMLBehaviourStart::YES_ONLYONE.c_str()) ? true : false;
	}
	else 
	{
		return BehaviourBase::parse(attribute);
	}
	
	return true;
}

bool BehaviourStart::parse (XMLNode* node)
{
	return BehaviourBase::parse(node);
}

XMLNode* BehaviourStart::getXMLNode(unsigned int iHow)
{
	XMLNode* root = BehaviourBase::getXMLNode(iHow);
	root->setName ( XMLBehaviourStart::MAIN_NODE.c_str() );

	root->addAttribute( new XMLAttribute( XMLBehaviourStart::ONLYONE_ATTRIBUTE.c_str(), bOnlyOne ? XMLBehaviourStart::YES_ONLYONE : XMLBehaviourStart::NO_ONLYONE) );

    return root;
}

bool BehaviourStart::isToRexecute()
{
	return !bOnlyOne;
}