#include "CommonDefines.h"

#include "BehaviourExecution.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

BehaviourExecution::BehaviourExecution() : BehaviourBase(XMLBehaviourExecution::MAIN_NODE)
{
	this->init();
}

BehaviourExecution::BehaviourExecution( XMLNode* node ) : BehaviourBase(XMLBehaviourExecution::MAIN_NODE)
{
	XMLObject::init(node);
}

BehaviourExecution::~BehaviourExecution()
{
}

void BehaviourExecution::init()
{
	sType = XMLBehaviourExecution::ROUTE_TYPE;
	script.init();
}

bool BehaviourExecution::parse (XMLAttribute* attribute)
{
	if ( strcmp( attribute->getName(), XMLBehaviourExecution::TYPE_ATTRIBUTE.c_str()) == 0 )
	{
		sType = attribute->getValue();
	}
	else
		return BehaviourBase::parse(attribute);

	return true;
}

bool BehaviourExecution::parse (XMLNode* node)
{
	if ( !strcmp(node->getName(),  XMLScript::MAIN_NODE.c_str()) )
	{
		script.init (node);
	}
	else
		return BehaviourBase::parse(node);

	return true;
}

XMLNode* BehaviourExecution::getXMLNode(unsigned int iHow)
{
	XMLNode* root = BehaviourBase::getXMLNode(iHow);
	root->setName ( XMLBehaviourExecution::MAIN_NODE.c_str() );

	root->addAttribute ( new XMLAttribute (XMLBehaviourExecution::TYPE_ATTRIBUTE.c_str(), sType) );
	root->addNode ( script.getXMLNode (iHow) );

    return root;
}