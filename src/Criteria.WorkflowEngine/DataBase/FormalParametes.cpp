#include "CommonDefines.h"

#include "FormalParameters.h"
using namespace DataManager::Panorama::Common;

using namespace bOS::XML;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

#include "Tracer.h"

FormalParameters::FormalParameters() : XMLObjectSet()
{
	this->init();
}

FormalParameters::FormalParameters(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

FormalParameters::~FormalParameters(void)
{
}

void FormalParameters::init()
{
	XMLObjectSet::init();
}

bool FormalParameters::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool FormalParameters::parse(XMLNode* root)
{
	if ( !strcmp(root->getName(),XMLFormalParameter::MAIN_NODE.c_str()) )
    {
		FormalParameter* parameter = new FormalParameter(root);
		XMLObjectSet::add((CollectionEntry*)parameter);
    }
	else
		return false;

	return true;
}

XMLNode* FormalParameters::getXMLNode(unsigned int iHow)
{
	XMLNode* root= new XMLNode( XMLFormalParameters::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	FormalParameter* parameter=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		parameter = (FormalParameter*)(this->at(i));
		root->addNode( parameter->getXMLNode(iHow) );
	}
    
    return root;
}

void FormalParameters::addParameter (FormalParameter& _parameter)
{
	FormalParameter* parameter = new FormalParameter();
	parameter->setName (_parameter.getName() );
	parameter->setType (_parameter.getType() );
	parameter->setValue ( _parameter.getValue() );
	if ( _parameter.isMandatory() )
		parameter->setMandatory();
	else
		parameter->setNoMandatory();

	XMLObjectSet::add((CollectionEntry*)parameter);
}

void FormalParameters::addParameter (FormalParameters& vParameters)
{
	unsigned int uiSize = vParameters.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		FormalParameter* parameter = (FormalParameter*)vParameters.at(i);
		this->addParameter ( *parameter);
	}
}

FormalParameter* FormalParameters::get(const char* acParamName)
{
	FormalParameter parameter;
	parameter.setName (acParamName);

	CollectionEntry* entry = (CollectionEntry*)&parameter;

	FormalParameter* param2Ret = (FormalParameter*)XMLObjectSet::get(entry);

	return param2Ret;
}