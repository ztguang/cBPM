#include "CommonDefines.h"

#include "Status.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

Status::Status() : XMLObject()
{
	this->init();
}

Status::Status( XMLNode* root ) : XMLObject()
{
	XMLObject::init(root);

	sStatus = root->getValue();
}

Status::~Status()
{
}

void Status::init()
{
    sStatus="";
	sDate="";
}

bool Status::parse(XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(),XMLStatus::DATE_ATTRIBUTE.c_str()) == 0 )
		sDate = attribute->getValue();
	else
		return false;

	return true;
}

bool Status::parse(XMLNode* node)
{
	return false;
}

XMLNode* Status::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode( XMLStatus::MAIN_NODE.c_str(), sStatus );
	root->addAttribute( new XMLAttribute( XMLStatus::DATE_ATTRIBUTE.c_str(), sDate) );
    return root;
}