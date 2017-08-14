#include "CommonDefines.h"

#include "BehaviourBase.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

BehaviourBase::BehaviourBase(String _Key) : XMLObject()
{
	this->init();

	sKey = _Key;
}

BehaviourBase::~BehaviourBase()
{
}

void BehaviourBase::init ()
{
	sMode = XMLBehaviourBase::AUTOMATIC_MODE;
	report.init();
}

bool BehaviourBase::parse(XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(), XMLBehaviourBase::MODE_ATTRIBUTE.c_str()) == 0 )
		sMode = attribute->getValue();
	else
		return false;

	return true;
}

bool BehaviourBase::parse(XMLNode* node)
{
	if ( strcmp(node->getName(), XMLReport::MAIN_NODE.c_str()) == 0 ) 
	{
		report.init(node);
	}
	else
		return false;

	return true;
}

XMLNode* BehaviourBase::getXMLNode(unsigned int iHow)
{
	XMLNode* node = new XMLNode("", "");

	node->addAttribute ( new XMLAttribute(XMLBehaviourBase::MODE_ATTRIBUTE.c_str(), sMode) );
	node->addNode ( report.getXMLNode(iHow) );

	return node;
}

bool BehaviourBase::equalTo(bOS::Collections::CollectionEntry* entry)
{
	BehaviourBase* behaviour = (BehaviourBase*)entry;

	if ( strcmp(behaviour->getKey().c_str(), this->sKey.c_str()) == 0 ) 
		return true;

	return false;
}

bool BehaviourBase::isAutomatic ()
{
	if ( strcmp(sMode.c_str(), XMLBehaviourBase::AUTOMATIC_MODE.c_str() ) == 0 )
		return true;

	return false;
}