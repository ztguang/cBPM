#include "CommonDefines.h"

#include "Reports.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSCollectionEntry.h"
using namespace bOS::Collections;

using namespace bOS::SQL;
using namespace bOS::XML;

Reports::Reports() : XMLObjectSet(), SQLTable(false), ProcessComponent()
{
	this->init();
}

Reports::Reports(XMLNode* node) : XMLObjectSet(), SQLTable(false), ProcessComponent()
{
	XMLObjectSet::init(node);
}

Reports::~Reports()
{
}

void Reports::init()
{
	XMLObjectSet::init();
}

bool Reports::init(XMLNode* node)
{
	return XMLObjectSet::init(node);
}

bool Reports::init(const char* acXML)
{
	return XMLObjectSet::init(acXML);
}

bool Reports::parse(XMLNode* node )
{
	if ( strcmp(node->getName(), XMLReport::MAIN_NODE.c_str() ) == 0)
	{
		Report* report = new Report(node);
		XMLObjectSet::add((CollectionEntry*)report);
	}
	else
		return false;

	return true;
}

XMLNode* Reports::getXMLNode(unsigned int iHow)
{
	bOS::XML::XMLNode* root= new bOS::XML::XMLNode( XMLReports::MAIN_NODE.c_str(), "" );

	unsigned int uiSize=this->size();
	Report* report=NULL;
	for ( unsigned int i=0; i<uiSize; i++)
	{
		report = (Report*)(this->at(i));
    	root->addNode( report->getXMLNode(iHow));
	}
    
    return root;
}

bool Reports::parse(bOS::SQL::ResultSetRecord* record)
{
	bool bRet = true;
	Report* report = new Report();

	if ( report->parse( record) )
	{
		XMLObjectSet::add( (CollectionEntry*) report);

	}
	else
	{
		delete report;
		bRet=false;
	}

	return bRet;
}

void Reports::addSQLCommands(SQLCommands& vCommands, int operation)
{
	if ( operation == SQLCommand::SELECT )
	{
		SQLTable::addSQLCommands (vCommands, operation);
	}
	else
	{
		unsigned int iSize = this->size();
		for ( unsigned int i=0; i<iSize;i++)
		{
			Report* report = (Report*)(this->at(i));

			report->addSQLCommands(vCommands, operation);
		}
	}
}

bool Reports::addReport(Report& report)
{
	Report* report2add= new Report( report.getXMLNode(0));
	bool bRet = bOS::Collections::Collection::add((CollectionEntry*)report2add);

	if ( !bRet )
	{
		delete report2add;
	}

	return bRet;
}