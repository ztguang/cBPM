#include "CommonDefines.h"

#include "ProcessComponent.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::XML;

using namespace bOS::SQL;

#include "bOSUniqueID.h"

ProcessComponent::ProcessComponent()
{
	this->init();
}

ProcessComponent::~ProcessComponent()
{
}

void ProcessComponent::init()
{
	processId = "";
}

bool ProcessComponent::parse(XMLNode* node)
{
	bool bRet = true;

	if ( strcmp(node->getName(),XMLProcessComponent::PROCESS_ID_NODE.c_str() ) == 0 )		
	{
		this->setProcessId ( node->getValue() );
	}
	else
	{
		bRet = false;
	}

	return bRet;
}

void ProcessComponent::setXML(bOS::XML::XMLNode* node)
{
	node->addNode ( new XMLNode(XMLProcessComponent::PROCESS_ID_NODE.c_str(), processId) );
}

//SQL
ResultSetField* ProcessComponent::setRecord(ResultSetRecord& record)
{
	bOS::SQL::ResultSetField* field = new ResultSetField(SQLProcessComponent::PROCESS_ID_FIELD.c_str(), processId);
	record.add (field);

	return field;
}

String ProcessComponent::acGetWhere()
{
	if ( processId.compare("") )
	{
		StringBuffer sSql;
		sSql.append (SQLProcessComponent::PROCESS_ID_FIELD);
		sSql.append("='");
		sSql.append(processId);
		sSql.append("'");

		return (char*)sSql.getData();
	}
	else
		return "";
}

bool ProcessComponent::parse(ResultSetField* field)
{
	if ( !strcmp(field->sName.c_str(),  SQLProcessComponent::PROCESS_ID_FIELD.c_str()) )
	{
		processId = field->sValue.getData();
	}
	else
	{
		return false;
	}

	return true;
}