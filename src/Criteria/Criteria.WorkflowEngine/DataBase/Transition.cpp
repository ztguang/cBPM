#include "CommonDefines.h"

#include "Transition.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

Transition::Transition() : XMLObject()
{
	this->init();
}

Transition::Transition(XMLNode* root) : XMLObject()
{
	XMLObject::init(root);
}

Transition::~Transition()
{
}

void Transition::init()
{
	sId="";
	sFromActivity="";
	sToActivity="";
	sResult="";
	sOperator=XMLTransition::NOTEQUAL_OPERATOR;
	bReExec=false;
}

bool Transition::parse (XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName() ,XMLTransition::ID_ATTRIBUTE.c_str() ) == 0 )
	{
		sId=attribute->getValue();
	}
	else if ( strcmp(attribute->getName() ,XMLTransition::FROM_ATTRIBUTE.c_str() ) == 0 )
	{
		sFromActivity = attribute->getValue();
	}
	else if ( strcmp(attribute->getName() ,XMLTransition::TO_ATTRIBUTE.c_str() ) == 0 )
	{
		sToActivity = attribute->getValue();
	}
	else
		return false;
	
	return true;
}

bool Transition::parse(XMLNode* node )
{
	if ( strcmp(node->getName(),XMLTransition::RESULT_NODE.c_str()) == 0 ) 
        sResult = node->getValue();
    
	else if ( strcmp(node->getName(),XMLTransition::OPERATOR_NODE.c_str()) == 0 )
	{
        sOperator = node->getValue();
	}
	else if ( strcmp(node->getName(),XMLTransition::REEXEC_NODE.c_str() ) == 0 ) 
		bReExec = !strcmp(node->getValue(),XMLTransition::YES_REEXEC.c_str()) ? true : false;

	else
		return false;

	return true;
}

XMLNode* Transition::getXMLNode(unsigned int iHow)
{
    XMLNode* root = new XMLNode( XMLTransition::MAIN_NODE.c_str(), "" );

	root->addAttribute ( new XMLAttribute ( XMLTransition::ID_ATTRIBUTE.c_str(), sId) );
	root->addAttribute ( new XMLAttribute ( XMLTransition::FROM_ATTRIBUTE.c_str(), sFromActivity) );
	root->addAttribute ( new XMLAttribute ( XMLTransition::TO_ATTRIBUTE.c_str(), sToActivity) );
	
	root->addNode( new XMLNode( XMLTransition::RESULT_NODE.c_str(), sResult ) );
	root->addNode( new XMLNode( XMLTransition::OPERATOR_NODE.c_str(), sOperator ) );
	root->addNode( new XMLNode( XMLTransition::REEXEC_NODE.c_str(), bReExec ? XMLTransition::YES_REEXEC : XMLTransition::NO_REEXEC ));

    return root;
}

bool Transition::isValid()
{
    if ( sFromActivity.length()  == 0 )
        return false;
        
    if ( sFromActivity .length() ==  0 )
        return false;
        
    return true;
}


bool Transition::isNoReExecuteWay()
{
	return !bReExec;
}