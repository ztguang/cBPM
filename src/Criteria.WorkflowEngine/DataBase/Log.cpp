#include "CommonDefines.h"

#include "Log.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

Log::Log() : XMLObjectSet()
{
	this->init();
}

Log::Log(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Log::~Log()
{
}

void Log::init()
{
	sUserKey="";
	sResult="";

	status.init();

	XMLObjectSet::init();
}

bool Log::init(bOS::XML::XMLNode* node)
{
	return XMLObjectSet::init (node);
}

bool Log::init(const char* acXML)
{
	return XMLObjectSet::init (acXML);
}

bool Log::parse(XMLAttribute* attribute)
{
	if ( strcmp(attribute->getName(), XMLLog::OWNER_ATTRIBUTE.c_str()) == 0 )
		sUserKey = attribute->getValue();
	else if ( strcmp(attribute->getName(), XMLLog::RESULT_ATTRIBUTE.c_str()) == 0 )
		sResult = attribute->getValue();
	else if ( strcmp(attribute->getName(), XMLStatus::DATE_ATTRIBUTE.c_str()) == 0 )
		status.setDate ( attribute->getValue() );
	else if ( strcmp(attribute->getName(), XMLStatus::MAIN_NODE.c_str()) == 0 )
		status.setStatus ( attribute->getValue() );
	else
		return false;

	return true;
}

bool Log::parse(XMLNode* node)
{
	if ( strcmp(node->getName(),XMLStatus::MAIN_NODE.c_str()) == 0 )
	{
		Status* status = new Status(node);
		this->add( status);
	}
	else
		return false;

	return true;
}

XMLNode* Log::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode( XMLLog::MAIN_NODE.c_str() , "" );
	root->addAttribute( new XMLAttribute( XMLLog::OWNER_ATTRIBUTE.c_str(), sUserKey) );
	root->addAttribute( new XMLAttribute( XMLLog::RESULT_ATTRIBUTE.c_str(), sResult.c_str()) );
	root->addAttribute( new XMLAttribute( XMLStatus::MAIN_NODE.c_str(), status.getStatus()) );
	root->addAttribute( new XMLAttribute( XMLStatus::DATE_ATTRIBUTE.c_str(), status.getDate()) );

	unsigned int uiSize=this->size();
	Status* status=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		status = (Status*)(this->at(i));
		root->addNode( status->getXMLNode(iHow) );
	}

	return root;
}

void Log::setStatus(const String& Value)
{
	if ( status.getStatus() != "" )
	{
		Status* oldStatus = new Status();

		oldStatus->setDate ( status.getDate() );
		oldStatus->setStatus (status.getStatus() );

		//TODO: Costruttore di copia.....oppure vStatus farla diventare una classe.
		this->add(oldStatus);
	}

	status.setStatus(Value);
}


bool Log::isValid()
{
    if ( sUserKey == "" )
        return false;

    return true;
}

bool Log::checkStatus(const char* acStatus, bool bNotSkipCuurentStatus)
{
	String sStatus;
	
	if ( bNotSkipCuurentStatus) 
	{
		sStatus= status.getStatus();

		if ( !strcmp(sStatus.c_str(), acStatus) )
		{
			return true;
		}
	}

	int iSize = this->size();
	for ( int i=0; i<iSize;i++)
	{
		Status* oldStatus = (Status*)(this->at(i));

		sStatus = oldStatus->getStatus();

		if ( !strcmp(sStatus.c_str(), acStatus) )
		{
			return true;
		}
	}

	return false;
}

void Log::add(Status& _status)
{
	XMLNode* node = _status.getXMLNode(0) ;
	Status* newStatus = new Status(node);
	delete node;

	this->add (newStatus);
}

void Log::add (Status* _status)
{
	bOS::Collections::Collection::add ( (CollectionEntry*)_status);
}