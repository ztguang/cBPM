#include "CommonDefines.h"

#include "WorkflowProcess.h"
using namespace DataManager::Panorama::WorkflowProcesses;

#include "bOSDateTime.h"

using namespace bOS::SQL;

using namespace DataManager::Panorama::Common;

WorkflowProcess::WorkflowProcess() : bOS::XML::Data::XMLFile(), SQLTable(true), ProcessComponent()
{
	this->init();
}

WorkflowProcess::WorkflowProcess( bOS::XML::XMLNode* node ) : bOS::XML::Data::XMLFile(node), SQLTable(true), ProcessComponent()
{
	XMLFile::init(node);
}

WorkflowProcess::~WorkflowProcess()
{
	CM_CODEBLOCK(~WorkflowProcess)
}

void WorkflowProcess::init()
{
	sName="";
    sDescription="";
    sStatus="";
	parentProcess = "";
	sExit2Manage = "NO";

	//remember to update setProcessId method.
	vTables.clear();
	vTables.push_back (&vAttributes);
	vTables.push_back (&vActivities);
	vTables.push_back (&vReports);

	vAttributes.init();
	vActivities.init();
	vTransitions.init();
	vMessages.init();
	vReports.init();
}

bool WorkflowProcess::init(bOS::XML::XMLNode* node)
{
	return XMLFile::init(node);
}

bool WorkflowProcess::init (const char* acFile)
{
	return XMLFile::init(acFile);
}

bool WorkflowProcess::parse(bOS::XML::XMLAttribute* attribute)
{
	if ( ProcessComponent::parse (attribute) )
		return true;

	else if ( strcmp(attribute->getName(),XMLWorkflowProcess::NAME_ATTRIBUTE.c_str() ) == 0 )
		sName = attribute->getValue();

	else
		return false;

	return true;
}

bool WorkflowProcess::parse (bOS::XML::XMLNode* node)
{
	if ( ProcessComponent::parse (node) )
		return true;

	else if ( strcmp(node->getName(),XMLWorkflowProcess::DESCRIPTION_NODE.c_str()) == 0 )
		sDescription = node->getValue();

	else if ( strcmp(node->getName(),XMLWorkflowProcess::STATUS_NODE.c_str()) == 0 )
		sStatus = node->getValue();

	else if ( strcmp(node->getName(),XMLWorkflowProcess::PARENT_PROCESS_NODE.c_str()) == 0 )
		parentProcess = node->getValue();

	else if ( strcmp(node->getName(), XMLWorkflowProcess::ACTIVITY_PARENT_PROCESS_NODE.c_str()) == 0 )
		taskParentProcess = node->getValue();

	else if ( strcmp(node->getName(), XMLWorkflowProcess::EXIT2MANAGE_NODE.c_str()) == 0 )
		sExit2Manage= node->getValue();

	else if ( strcmp(node->getName(),XMLActivities::MAIN_NODE.c_str()) == 0 )
        vActivities.init(node);   

	else if ( strcmp(node->getName(),XMLTransitions::MAIN_NODE.c_str()) == 0 )
        vTransitions.init(node);   

	else if ( strcmp(node->getName(),XMLMessages::MAIN_NODE.c_str()) == 0 )
        vMessages.init(node);   


	else if ( strcmp(node->getName(),XMLAttributes::MAIN_NODE.c_str()) == 0 )
		vAttributes.init(node);

	else if ( strcmp(node->getName(), XMLReports::MAIN_NODE.c_str()) == 0 )
		vReports.init(node);

	else
		return false;

	return true;
}

bOS::XML::XMLNode* WorkflowProcess::getXMLNode(unsigned int iHow)
{
    bOS::XML::XMLNode* root = new bOS::XML::XMLNode( XMLWorkflowProcess::MAIN_NODE.c_str(), "" );
	
	ProcessComponent::setXML ( root );

	root->addAttribute( new bOS::XML::XMLAttribute( XMLWorkflowProcess::NAME_ATTRIBUTE.c_str(), sName.c_str() ) );
	root->addNode( new bOS::XML::XMLNode( XMLWorkflowProcess::DESCRIPTION_NODE.c_str(), sDescription.c_str() ) );
	root->addNode( new bOS::XML::XMLNode( XMLWorkflowProcess::STATUS_NODE.c_str(), sStatus.c_str() ) );
	
	if ( parentProcess.compare("") )
	{
		root->addNode( new bOS::XML::XMLNode(XMLWorkflowProcess::PARENT_PROCESS_NODE.c_str(), parentProcess) );
		root->addNode( new bOS::XML::XMLNode(XMLWorkflowProcess::ACTIVITY_PARENT_PROCESS_NODE.c_str(), taskParentProcess) );
		root->addNode( new bOS::XML::XMLNode(XMLWorkflowProcess::EXIT2MANAGE_NODE.c_str(), sExit2Manage) );
	}

	root->addNode( vAttributes.getXMLNode(iHow) );
	root->addNode( vTransitions.getXMLNode(iHow) );
	root->addNode( vMessages.getXMLNode(iHow) );
	root->addNode( vActivities.getXMLNode(iHow) );
	root->addNode(vReports.getXMLNode(iHow));

    return root;
}

String WorkflowProcess::getFileName()
{
	return getProcessId();
}

bool WorkflowProcess::isCreated()
{
	return !(strcmp(sStatus.c_str(), XMLWorkflowProcess::CREATED_STATUS.c_str()));
}

bool WorkflowProcess::isQueued()
{
    return !(strcmp(sStatus.c_str(), XMLWorkflowProcess::QUEUED_STATUS.c_str()));
}

bool WorkflowProcess::isRunning()
{ 
    return !(strcmp(sStatus.c_str(), XMLWorkflowProcess::RUNNING_STATUS.c_str()));
}

bool WorkflowProcess::isCompleted()
{ 
    return !(strcmp(sStatus.c_str(), XMLWorkflowProcess::COMPLETED_STATUS.c_str()));
}

bool WorkflowProcess::isError()
{ 
    return !(strcmp(sStatus.c_str(), XMLWorkflowProcess::ERROR_STATUS.c_str()));
}

void WorkflowProcess::setCreated()
{
	setStatus(XMLWorkflowProcess::CREATED_STATUS);
	this->sCreated = bOS::Utils::DateTime::getCurrentDateTime().toString();
}

void WorkflowProcess::setQueued()
{ 
	setStatus(XMLWorkflowProcess::QUEUED_STATUS);
}

void WorkflowProcess::setRunning()
{
	setStatus(XMLWorkflowProcess::RUNNING_STATUS);
}

void WorkflowProcess::setCompleted()
{
	setStatus(XMLWorkflowProcess::COMPLETED_STATUS);
	this->sCompleted = bOS::Utils::DateTime::getCurrentDateTime().toString();
}

void WorkflowProcess::setError()
{ 
	setStatus(XMLWorkflowProcess::ERROR_STATUS);
}

ActivitiesList WorkflowProcess::getNextActivityList(String sActivity)
{
    CM_CODEBLOCK(getNextActivityList)

	Activity* activity = vActivities.get(sActivity);
	ActivitiesList vNextActivities;

    if ( activity != (Activity*)NULL ) 
    {
		unsigned int uiSize = vTransitions.size();
	    for (unsigned int i=0; i < uiSize; i++)
	    {
			Transition* transition = (Transition*)vTransitions.at(i);
            if ( strcmp(transition->getFromActivity().c_str(), activity->getActivityName().c_str() ) == 0 )
            {
				vNextActivities.push_back(transition->getToActivity());
            }
	    }
    }

    return vNextActivities;
}

/*****************************************/
const char* WorkflowProcess::acGetTableName()
{
	return SQLWorkflowProcess::TABLE_NAME.c_str();
}

void WorkflowProcess::setRecord(ResultSetRecord& record)
{
	record.clear();

	record.add ( new ResultSetField ( SQLWorkflowProcess::NAME_FIELD.c_str(), sName));
	record.add ( new ResultSetField ( SQLWorkflowProcess::DESCRIPTION_FIELD.c_str(), sDescription) );
	record.add ( new ResultSetField ( SQLWorkflowProcess::STATUS_FIELD.c_str(), sStatus) );
	
	record.add ( new ResultSetField ( SQLWorkflowProcess::PARENT_PROCESS_FIELD.c_str(), parentProcess) );
	record.add ( new ResultSetField ( SQLWorkflowProcess::ACTIVITY_PARENT_PROCESS_FIELD.c_str(), taskParentProcess) );
	record.add ( new ResultSetField ( SQLWorkflowProcess::EXIT2MANAGE_FIELD.c_str(), sExit2Manage) );
	record.add ( new ResultSetField (SQLWorkflowProcess::CREATIONDATE_FIELD.c_str(), this->sCreated));
	record.add ( new ResultSetField (SQLWorkflowProcess::COMPLETITIONDATE_FIELD.c_str(), this->sCompleted));

	//
	record.add( new ResultSetField (SQLWorkflowProcess::TRANSITIONS_FIELD.c_str(), vTransitions.getXMLString(0) ));
	record.add( new ResultSetField (SQLWorkflowProcess::MESSAGES_FIELD.c_str(), vMessages.getXMLString(0) ));


	ProcessComponent::setRecord ( record);

}

String WorkflowProcess::acGetWhere()
{
	return ProcessComponent::acGetWhere();
}

bool WorkflowProcess::parse(ResultSetField* field)
{
	bool bRet=true;

	if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::NAME_FIELD.c_str() ) )
	{
		sName = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::DESCRIPTION_FIELD.c_str() ) )
	{
		sDescription = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::STATUS_FIELD.c_str() ) )
	{
		sStatus = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::PARENT_PROCESS_FIELD.c_str() ) )
	{
		parentProcess = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::ACTIVITY_PARENT_PROCESS_FIELD.c_str() ) )
	{
		taskParentProcess = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::EXIT2MANAGE_FIELD.c_str() ) )
	{
		sExit2Manage = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::CREATIONDATE_FIELD.c_str() ) )
	{
		this->sCreated= field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::COMPLETITIONDATE_FIELD.c_str() ) )
	{
		this->sCompleted = field->sValue.getData();
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::TRANSITIONS_FIELD.c_str() ) )
	{
		vTransitions.init(field->sValue.getData());
	}
	else if ( !strcmp(field->sName.c_str(),SQLWorkflowProcess::MESSAGES_FIELD.c_str() ) )
	{
		vMessages.init(field->sValue.getData());
	}
	else
		bRet = ProcessComponent::parse(field);

	return bRet;
}

//SQL
SQLTablesList WorkflowProcess::getSQLTables()
{
	//TODO: Generalizzare.
	vAttributes.setProcessId( this->getProcessId());

	//TODO: Generalizzare.
	vActivities.setProcessId( this->getProcessId());

	vReports.setProcessId(this->getProcessId());
	
	return SQLTable::getSQLTables();
}

void WorkflowProcess::setProcessId(const char* _ProcessId)
{
	ProcessComponent::setProcessId(_ProcessId);
	//XMLFile::setSequence(_ProcessId);

	vActivities.setProcessId( _ProcessId);
	vReports.setProcessId(_ProcessId);
	vAttributes.setProcessId(_ProcessId);
}

void WorkflowProcess::setSequence(long _Sequence)
{
	return;
	//XMLFile::setSequence(_Sequence);
	//this->setProcessId(_Sequence);
}

void WorkflowProcess::setAutoIncrementField(long _ProcessId)
{
	return;
	//this->setProcessId(_ProcessId);
}

DataManager::Panorama::WorkflowRelevantData::Attributes& WorkflowProcess::getAttributes()
{
	vAttributes.setProcessId( this->getProcessId() );
	return vAttributes;
}

bool WorkflowProcess::parse(bOS::SQL::ResultSetRecord* record)
{
	return SQLTable::parse (record);
}