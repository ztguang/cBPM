#include "ScenarioEventAction.h"
using namespace DataManager::Panorama::WorkflowEvents;

using namespace bOS::XML;

#include "Tracer.h"

ScenarioEventAction::ScenarioEventAction() : XMLObject()
{
	this->init();
}

ScenarioEventAction::ScenarioEventAction(XMLNode* node) : XMLObject()
{
	XMLObject::init(node);
}

ScenarioEventAction::~ScenarioEventAction(void)
{
}

void ScenarioEventAction::init()
{
	sType = "";
	sValue = "";
}

bool ScenarioEventAction::init (bOS::XML::XMLNode* node )
{
	bool bRet = XMLObject::init(node);

	sValue = node->getValue();
	if ( sValue.length() == 0 )
	{
		sValue = node->getInnerXML();
	}

	return bRet;
}	

bool ScenarioEventAction::parse(XMLAttribute* attribute)
{
	if ( !strcmp(attribute->getName(), XMLScenarioEventAction::TYPE_ATTRIBUTE.c_str()) )
	{
		sType = attribute->getValue();
	}
	else if ( !strcmp(attribute->getName(), XMLScenarioEventAction::ID_ATTRIBUTE.c_str()) )
	{
		sId = attribute->getValue();
	}
	else
		return false;	

	return true;
}

bool ScenarioEventAction::parse(XMLNode* root)
{
	return false;
}

XMLNode* ScenarioEventAction::getXMLNode(unsigned int iHow)
{
	XMLNode* nd = new XMLNode( XMLScenarioEventAction::MAIN_NODE.c_str(), sValue );
	nd->addAttribute ( new XMLAttribute(XMLScenarioEventAction::TYPE_ATTRIBUTE.c_str(), sType) );
	nd->addAttribute ( new XMLAttribute(XMLScenarioEventAction::ID_ATTRIBUTE.c_str(), sId) );

    return nd;
}

bool ScenarioEventAction::isValid()
{
	return true;
}

void ScenarioEventAction::setType(const String& sTypeValue)
{
	sType = sTypeValue;
}

String& ScenarioEventAction::getType()
{
	return sType;
}

void ScenarioEventAction::setValue(const String& sValueValue)
{
	sValue = sValueValue;
}

String& ScenarioEventAction::getValue()
{
	return sValue;
}

void ScenarioEventAction::setId(const String& sValue)
{
	sId = sValue;
}

String& ScenarioEventAction::getId()
{
	return sId;
}

bool ScenarioEventAction::isProcessExecuteType()
{
	return !strcmp(sType.c_str(), XMLScenarioEventAction::PROCESSEXECUTE_TYPE.c_str());
}

bool ScenarioEventAction::equalTo(CollectionEntry* entry)
{
	ScenarioEventAction* action = (ScenarioEventAction*)entry;

	if ( strcmp(this->getId().c_str(), action->getId().c_str()) == 0 )
	{
		return true;
	}

	return false;
}

