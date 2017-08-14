#include "CommonDefines.h"

#include "Logs.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::XML;

Logs::Logs() : XMLObjectSet()
{
	this->init();
}

Logs::Logs(XMLNode* node) : XMLObjectSet()
{
	XMLObjectSet::init(node);
}

Logs::~Logs()
{
}

void Logs::init()
{
	XMLObjectSet::init();
}

bool Logs::init(bOS::XML::XMLNode* node)
{
	return XMLObjectSet::init (node);
}

bool Logs::init(const char* acXML)
{
	return XMLObjectSet::init (acXML);
}

void Logs::add( Log& _log)
{
	Log* log = new Log();

	//TODO: Construttore di copia.
	log->setDate ( _log.getDate());
	log->setResult ( _log.getResult());
	log->setStatus ( _log.getStatus());
	log->setUserKey ( _log.getUserKey());

	unsigned int uiSize = _log.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		Status* status2Insert = (Status*)_log.at(i);
		log->add ( *status2Insert );
	}

	bOS::Collections::Collection::add((CollectionEntry*) log );
}

bool Logs::parse(XMLAttribute* attribute)
{
	return false;
}

bool Logs::parse(XMLNode* node)
{
	if ( strcmp(node->getName(),XMLLog::MAIN_NODE.c_str()) == 0 )
	{
		Log* log = new Log(node);
		bOS::Collections::Collection::add( (CollectionEntry*)log);
	}
	else
		return false;

	return true;
}

XMLNode* Logs::getXMLNode(unsigned int iHow)
{
	XMLNode* root = new XMLNode(XMLLogs::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	Log* log=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		log = (Log*)(this->at(i));
		root->addNode( log->getXMLNode(iHow) );
	}

	return root;
}

bool Logs::checkStatus(const char* acStatus)
{
	int iSize = this->size();
	for ( int i=0; i<iSize; i++)
	{
		Log* log = (Log*)(this->at(i));

		if ( log->checkStatus(acStatus, true) ) 
		{
			return true;
		}
	}

	return false;
}
