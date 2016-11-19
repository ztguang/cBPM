#include "CommonDefines.h"

#include "bOSDateTime.h"

#include "Activity.h"
using namespace DataManager::Panorama::WorkflowProcesses;

using namespace bOS::SQL;

#include "bOSXMLException.h"

using namespace DataManager::Panorama::Common;

Activity::Activity() : bOS::XML::Data::XMLObject(), SQLTable(true), ActivityComponent()
{
	this->init();
}

Activity::Activity( bOS::XML::XMLNode* root ) : bOS::XML::Data::XMLObject(), SQLTable(true), ActivityComponent()
{
	this->init(root);
}


Activity::~Activity()
{
}

void Activity::init()
{
	ActivityComponent::init();

    iType=ActivityType(NONE);
	sDescription="";
	sName="";
	sReferenceActivity="";
	catchType=CatchType(NEVER);
	iNrExecuted = 0;

	//Attributi strutturati
	behaviour.init();
	vReports.init();
	vAttributes.init();
	vLogs.init();
	log.init();
	vGrants.init();

	vTables.clear();
	//vTables.push_back(&vReports);
	vTables.push_back(&vAttributes);
}

bool Activity::init(bOS::XML::XMLNode* node)
{
	return XMLObject::init (node);
}

bool Activity::init (const char* acXML)
{
	return XMLObject::init (acXML);
}

bool Activity::parse(bOS::XML::XMLNode* node)
{
	if ( ActivityComponent::parse (node) )
		return true;

	else if ( strcmp(node->getName(), XMLActivity::DESCRIPTION_NODE.c_str() ) == 0 )
	{
		sDescription = node->getValue();
	}
	else if ( strcmp(node->getName(), XMLActivity::REFERENCE_ACTIVITY_NODE.c_str()) == 0 )
	{
		sReferenceActivity = node->getValue();
	}
	else if ( strcmp(node->getName(), XMLActivity::CATCH_TYPE_NODE.c_str() ) == 0 )
	{
		if ( !strcmp(node->getValue(), XMLActivity::NEVER_CATCH_TYPE.c_str()) ) 
		{
			catchType = CatchType(NEVER);
		}
		else if ( !strcmp(node->getValue(), XMLActivity::EVER_CATCH_TYPE.c_str()) ) 
		{
			catchType = CatchType(EVER);
		}
		else if ( !strcmp(node->getValue(), XMLActivity::ONLY_ONE_CATCH_TYPE.c_str()) )
		{
			catchType = CatchType(ONLY_ONE);
		}
	}
	else if ( strcmp(node->getName(), XMLActivity::NR_EXECUTED_NODE.c_str()) == 0 )
	{
		iNrExecuted = node->getUIntValue();
	}
	else if ( strcmp(node->getName(),XMLAttributes::MAIN_NODE.c_str() ) == 0 )
    {
		vAttributes.init(node);
    }
	else if ( strcmp(node->getName(),XMLBehaviour::MAIN_NODE.c_str())  == 0 )
    {
        behaviour.init(node);
    }
	else if ( strcmp(node->getName(),XMLReports::MAIN_NODE.c_str()) == 0 )
    {
        vReports.init(node);
    }
	else if ( strcmp(node->getName(),XMLLogs::MAIN_NODE.c_str()) == 0 )		
    {
		vLogs.init(node);
	}
	else if ( strcmp(node->getName(),XMLLog::MAIN_NODE.c_str()) == 0 )		
    {
		log.init(node);
	}
	else if ( strcmp(node->getName(),XMLGrants::MAIN_NODE.c_str()) == 0 )		
    {
		vGrants.init(node);
	}
	else
		return false;

	return true;
}

bool Activity::parse(bOS::XML::XMLAttribute* attribute)
{
	if ( ActivityComponent::parse (attribute) )
		return true;

	else if ( strcmp(attribute->getName(),XMLActivity::NAME_ATTRIBUTE.c_str() ) == 0 )
	{
		this->setName (attribute->getValue());
	}
	else if ( strcmp(attribute->getName(),XMLActivity::TYPE_ATTRIBUTE.c_str() ) == 0 )
	{
		if ( !strcmp(attribute->getValue(), XMLActivity::START_TYPE.c_str()) ) 
		{
			iType = ActivityType(START);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::END_TYPE.c_str()) ) 
		{
			iType = ActivityType(END);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::SUBFLOW_TYPE.c_str()) )
		{
			iType = ActivityType(SUBFLOW);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::API_TYPE.c_str()) ) 
		{
			iType = ActivityType(API);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::CONDITION_TYPE.c_str()) )
		{
			iType = ActivityType(CONDITION);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::ITERATION_TYPE.c_str()) )
		{
			iType = ActivityType(ITERATION);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::EMAIL_TYPE.c_str()) ) 
		{
			iType = ActivityType(EMAIL);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::APPLICATION_TYPE.c_str()) )
		{
			iType = ActivityType(APPLICATION);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::XML_TYPE.c_str()) ) 
		{
			iType = ActivityType(XML);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::EXIT_TYPE.c_str()) )
		{
			iType = ActivityType(EXIT);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::EVENT_TYPE.c_str()) )
		{
			iType = ActivityType(EVENT);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::THROWER_TYPE.c_str()) ) 
		{
			iType = ActivityType(THROWER);
		}
		else if ( !strcmp(attribute->getValue(), XMLActivity::CATCHER_TYPE.c_str()) )
		{
			iType = ActivityType(CATCHER);
		}
	}
	else 
		return false;

	return true;
}

bOS::XML::XMLNode* Activity::getXMLNode(unsigned int iHow)
{
    bOS::XML::XMLNode* root = new bOS::XML::XMLNode( XMLActivity::MAIN_NODE.c_str(), "");
	root->addAttribute( new bOS::XML::XMLAttribute( XMLActivity::NAME_ATTRIBUTE.c_str(), sName) );

	ActivityComponent::setXML ( root );

	String sType;
	switch ( iType )
	{
	case START:
		sType = XMLActivity::START_TYPE;
		break;
	case END:
		sType = XMLActivity::END_TYPE;
		break;
	case SUBFLOW:
		sType = XMLActivity::SUBFLOW_TYPE;
		break;
	case API:
		sType = XMLActivity::API_TYPE;
		break;
	case CONDITION:
		sType = XMLActivity::CONDITION_TYPE;
		break;
	case EMAIL:
		sType = XMLActivity::EMAIL_TYPE;
		break;
	case APPLICATION:
		sType = XMLActivity::APPLICATION_TYPE;
		break;
	case XML:
		sType = XMLActivity::XML_TYPE;
		break;
	case EXIT:
		sType = XMLActivity::EXIT_TYPE;
		break;
	case EVENT:
		sType = XMLActivity::EVENT_TYPE;
		break;
	case THROWER:
		sType = XMLActivity::THROWER_TYPE;
		break;
	case CATCHER:
		sType = XMLActivity::CATCHER_TYPE;
		break;
	}
	root->addAttribute( new bOS::XML::XMLAttribute( XMLActivity::TYPE_ATTRIBUTE.c_str(), sType ) );

	root->addNode( new bOS::XML::XMLNode( XMLActivity::DESCRIPTION_NODE.c_str(), sDescription) );
	root->addNode( new bOS::XML::XMLNode( XMLActivity::REFERENCE_ACTIVITY_NODE.c_str(), sReferenceActivity.c_str() ) );

	if ( iType == THROWER || iType == CATCHER ) 
	{
		switch ( catchType)
		{
		case CatchType(NEVER):
			root->addNode( new bOS::XML::XMLNode( XMLActivity::CATCH_TYPE_NODE.c_str(), XMLActivity::NEVER_CATCH_TYPE ) );
			break;
		case CatchType(EVER):
			root->addNode( new bOS::XML::XMLNode( XMLActivity::CATCH_TYPE_NODE.c_str(), XMLActivity::EVER_CATCH_TYPE ) );
			break;
		case CatchType(ONLY_ONE):
			root->addNode( new bOS::XML::XMLNode( XMLActivity::CATCH_TYPE_NODE.c_str(), XMLActivity::ONLY_ONE_CATCH_TYPE ) );
			break;
		}
	}
	root->addNode( new bOS::XML::XMLNode(XMLActivity::NR_EXECUTED_NODE.c_str(), this->iNrExecuted) );

    root->addNode(behaviour.getXMLNode(iHow) );
	root->addNode(vReports.getXMLNode(iHow) );
	root->addNode(vLogs.getXMLNode(iHow));
	root->addNode(log.getXMLNode(iHow));
	root->addNode(vGrants.getXMLNode(iHow));
    root->addNode(vAttributes.getXMLNode(iHow) );

    return root;
}

bool Activity::isError()
{ 
	return !(strcmp(log.getStatus().c_str(), XMLActivity::ERROR_STATUS.c_str()));
}

bool Activity::isCreated()
{ 
    return !(strcmp(log.getStatus().c_str(), XMLActivity::CREATED_STATUS.c_str()));
}

bool Activity::isQueued()
{ 
    return !(strcmp(log.getStatus().c_str(), XMLActivity::QUEUED_STATUS.c_str()));
}

bool Activity::isRunning()
{ 
    return !(strcmp(log.getStatus().c_str(), XMLActivity::RUNNING_STATUS.c_str()));
}

bool Activity::isCompleted()
{ 
    return !(strcmp(log.getStatus().c_str(), XMLActivity::COMPLETED_STATUS.c_str()));
}

bool Activity::isManual()
{ 
    return !(strcmp(log.getStatus().c_str(), XMLActivity::MANUAL_STATUS.c_str()));
}

bool Activity::isWaitingForEvent()
{ 
    return !(strcmp(log.getStatus().c_str(), XMLActivity::WAITINGFOR_STATUS.c_str()));
}

bool Activity::isAlreadyExecuted()
{
	if ( log.checkStatus(XMLActivity::COMPLETED_STATUS.c_str(), false) )
	{
		return true;
	}

	return vLogs.checkStatus (XMLActivity::COMPLETED_STATUS.c_str());
}

void Activity::setCreated()
{
	setStatus(XMLActivity::CREATED_STATUS);
}

void Activity::setQueued()
{
	setStatus(XMLActivity::QUEUED_STATUS);
}

void Activity::setRunning()
{
	setStatus(XMLActivity::RUNNING_STATUS);
}

void Activity::setCompleted()
{
	setStatus(XMLActivity::COMPLETED_STATUS);
}

void Activity::setError()
{
	setStatus(XMLActivity::ERROR_STATUS);
}

void Activity::setManual()
{
	setStatus(XMLActivity::MANUAL_STATUS);
}

void Activity::setWaitingForEvent()
{
	setStatus(XMLActivity::WAITINGFOR_STATUS);
}

bool Activity::isAutomatic()
{
    return behaviour.isAutomaticExecution();
}

bool Activity::isToRexecute()
{
	return behaviour.isToRexecuteStart();
}

void Activity::setNotToRexecute()
{
    behaviour.setNotToRexecuteStart();
}

bool Activity::isStartType()
{
    return (iType == ActivityType(START));
}

bool Activity::isEndType()
{
	return (iType == ActivityType(END));
}

bool Activity::isExitType()
{
	return (iType == ActivityType(EXIT));
}

bool Activity::isCatcherType()
{
	return (iType == ActivityType(CATCHER));
}

void Activity::setOwner (const String& Value)
{
	if ( (log.getUserKey() != "") && (log.getUserKey() != Value ) )
	{
		String sOldStatus = log.getStatus();
		vLogs.add (log);
		log.init();
		log.setStatus ( sOldStatus.c_str());
		log.setDate ( bOS::Utils::DateTime::getCurrentDateTime().toString());
	}

	log.setUserKey ( Value);
	
}

void Activity::setStatus(const String& Value)
{
	log.setStatus(Value);
	log.setDate (bOS::Utils::DateTime::getCurrentDateTime().toString());
}

void Activity::setResult(const String& sValue)
{
	log.setResult(sValue);
}

//CollectionEntry
bool Activity::equalTo(bOS::Collections::CollectionEntry* entry)
{
	Activity* activity = (Activity*)entry;

	CM_CODEBLOCK(Activity::equalTo) 
	CM_TRACE_CODEPATH("Activity ProcessId [" << activity->getProcessId() << "]")
	CM_TRACE_CODEPATH("this ProcessId [" << this->getProcessId() << "]")

	CM_TRACE_CODEPATH("Activity activityname [" << activity->getActivityName() << "]")
	CM_TRACE_CODEPATH("this activityname [" << this->getActivityName() << "]")

	if ( ( strcmp(activity->getProcessId(),"") == 0 ) || (strcmp(this->getProcessId(),"") == 0 ) ||
		 ( strcmp(activity->getProcessId(),this->getProcessId()) == 0  ) )
	{
		if ( strcmp(activity->getActivityName().c_str(), this->getActivityName().c_str()) == 0 )
		{
			return true;
		}
	}

	return false;
}

/***************************************************************/
const char* Activity::acGetTableName()
{
	return SQLActivity::TABLE_NAME.c_str();
}

void Activity::setRecord(ResultSetRecord& record)
{
	record.clear();

	//TODO: Sostituire con il valore string anzich?numerico.
	record.add ( new ResultSetField(SQLActivity::TYPE_FIELD.c_str(), iType));
	record.add ( new ResultSetField(SQLActivity::NAME_FIELD.c_str(), sName));

	record.add ( new ResultSetField(SQLActivity::DESCRIPTION_FIELD.c_str(), sDescription));;
	record.add ( new ResultSetField(SQLActivity::REFERENCE_ACTIVITY_FIELD.c_str(), sReferenceActivity));

	record.add ( new ResultSetField(SQLActivity::STATUS_FIELD.c_str(), this->getStatus()));
	record.add ( new ResultSetField(SQLActivity::OWNER_FIELD.c_str(), this->getOwner()));

	//TODO: Sostituire con il valore string anzich?numerico.
	record.add ( new ResultSetField(SQLActivity::CATCH_TYPE_FIELD.c_str(), catchType));;
	record.add ( new ResultSetField(SQLActivity::NR_EXECUTED_FIELD.c_str(), iNrExecuted));;

	//
	record.add( new ResultSetField (SQLActivity::GRANTS_FIELD.c_str(), vGrants.getXMLString(0) ));
	record.add( new ResultSetField (SQLActivity::BEHAVIOUR_FIELD.c_str(), behaviour.getXMLString(0) ));
	record.add( new ResultSetField (SQLActivity::LOG_FIELD.c_str(), log.getXMLString(0) ));
	record.add( new ResultSetField (SQLActivity::LOGS_FIELD.c_str(), vLogs.getXMLString(0) ));
	record.add( new ResultSetField (SQLActivity::REPORTS_FIELD.c_str(), vReports.getXMLString(0) ));

	ActivityComponent::setRecord ( record);
}

String Activity::acGetWhere()
{
	return ActivityComponent::acGetWhere();
}

bool Activity::parse(bOS::SQL::ResultSetRecord* record)
{
	CM_CODEBLOCK(Activity::parse_record)

	if ( SQLTable::parse (record) )
	{
		return true;
	}
	else
	{
		CM_TRACE_ERROR("Impossible to parse[" << this->getActivityName() << "]")
		return false;
	}
}

bool Activity::parse(ResultSetField* field)
{
	bool bRet = true;

	try
	{
		if ( !strcmp(field->sName.c_str(), SQLActivity::TYPE_FIELD.c_str()) )
		{
			iType = (ActivityType)atoi(field->sValue.getData());
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::NAME_FIELD.c_str()) )
		{
			this->setName (field->sValue.getData());
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::DESCRIPTION_FIELD.c_str()) )
		{
			sDescription = field->sValue.getData();
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::REFERENCE_ACTIVITY_FIELD.c_str()) )
		{
			sReferenceActivity = field->sValue.getData();
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::CATCH_TYPE_FIELD.c_str()) )
		{
			catchType=(CatchType)atoi(field->sValue.getData());
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::NR_EXECUTED_FIELD.c_str()) )
		{
			iNrExecuted= atoi(field->sValue.getData());
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::GRANTS_FIELD.c_str()) )
		{
			bRet = vGrants.init(field->sValue.getData());
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::BEHAVIOUR_FIELD.c_str()) )
		{
			bRet = behaviour.init(field->sValue.getData());
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::LOG_FIELD.c_str()) )
		{
			bRet = log.init(field->sValue.getData());
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::STATUS_FIELD.c_str()) )
		{
			//status is setted by log Tag.
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::OWNER_FIELD.c_str()) )
		{
			//owner is setted by log Tag.
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::LOGS_FIELD.c_str()) )
		{
			bRet = vLogs.init(field->sValue.getData());
		}
		else if ( !strcmp(field->sName.c_str(), SQLActivity::REPORTS_FIELD.c_str()) )
		{
			bRet = vReports.init(field->sValue.getData());
		}
		else 
			bRet = ActivityComponent::parse(field);
	}
	catch ( bOS::XML::XMLException&)
	{
		bRet = false;
	}
	return bRet;
}

SQLTablesList Activity::getSQLTables()
{
	//TODO: Generalizzare.
	vAttributes.setActivityId ( this->getActivityId().c_str() );
	vAttributes.setProcessId( this->getProcessId());
	
	return SQLTable::getSQLTables();
}

void Activity::setProcessId(const char* _ProcessId)
{
	ActivityComponent::setProcessId (_ProcessId);
	vAttributes.setProcessId(_ProcessId);
}

void Activity::setActivityId(const char* acId)
{
	ActivityComponent::setActivityId(acId);
	vAttributes.setActivityId(acId);
}

void Activity::setName(const char* acValue)
{
	sName = acValue;
	ActivityComponent::setActivityId (sName.c_str());
	vAttributes.setActivityId (sName.c_str());
}

Attributes&	Activity::getAttributes()
{
	vAttributes.setActivityId ( this->getActivityId().c_str() );
	return vAttributes;
}