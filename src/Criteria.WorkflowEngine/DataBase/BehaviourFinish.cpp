#include "CommonDefines.h"

#include "BehaviourFinish.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

BehaviourFinish::BehaviourFinish() : BehaviourBase(XMLBehaviourFinish::MAIN_NODE)
{
	this->init();
}

BehaviourFinish::BehaviourFinish( XMLNode* node ) : BehaviourBase(XMLBehaviourFinish::MAIN_NODE)
{
	XMLObject::init(node);
}

BehaviourFinish::~BehaviourFinish()
{
}

void BehaviourFinish::init()
{
}

bool BehaviourFinish::parse (XMLAttribute* attribute)
{
	return BehaviourBase::parse(attribute);
}

bool BehaviourFinish::parse (XMLNode* node)
{
	return BehaviourBase::parse(node);
}

XMLNode* BehaviourFinish::getXMLNode(unsigned int iHow)
{
	XMLNode* root = BehaviourBase::getXMLNode(iHow);
	root->setName ( XMLBehaviourFinish::MAIN_NODE.c_str() );

    return root;
}