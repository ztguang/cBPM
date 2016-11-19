#include "bOS.h"

#include "ExtendedAttributes.h"
#include "ExtendedAttribute.h"
#include "Grants.h"
#include "Grant.h"
#include "FormalParameters.h"
#include "FormalParameter.h"
#include "Attribute.h"
#include "Attributes.h"
#include "Activities.h"
#include "Activity.h"
#include "ActivityComponent.h"
#include "ProcessComponent.h"
#include "Behaviour.h"
#include "BehaviourBase.h"
#include "BehaviourExecution.h"
#include "BehaviourFinish.h"
#include "BehaviourStart.h"
#include "Script.h"
#include "Log.h"
#include "Logs.h"
#include "Status.h"
#include "Report.h"
#include "Reports.h"
#include "Transition.h"
#include "Transitions.h"

#include "Message.h"
#include "Messages.h"

#include "WorkflowProcess.h"
#include "Role.h"
#include "Roles.h"
#include "User.h"
#include "Users.h"
#include "Service.h"
#include "Services.h"
#include "Connection.h"
#include "Connections.h"
#include "DataBase.h"
#include "FileSystemConnection.h"
#include "mySQLConnection.h"
#include "ODBCConnection.h"
#include "SQLiteConnection.h"
#include "PoolManager.h"
#include "DataBaseObjectManager.h"
#include "DataBaseObject.h"
#include "DataType.h"
#include "DataTypes.h"
#include "DataTypeValue.h"
#include "DataTypeValues.h"
using namespace DataManager::Panorama;

//Common
//XmlExtendedAttribute
String Common::XMLExtendedAttributes::MAIN_NODE				= "ExtendedAttributes";

//XmlExtendedAttribute
String Common::XMLExtendedAttribute::MAIN_NODE				= "ExtendedAttribute";
String Common::XMLExtendedAttribute::NAME_ATTRIBUTE			= "Name";
String Common::XMLExtendedAttribute::VALUE_ATTRIBUTE		= "Value";

//Grants
String Common::XMLGrants::MAIN_NODE							= "Grants";

//Grant
String Common::XMLGrant::MAIN_NODE							= "Grant";
String Common::XMLGrant::ENABLED_ATTRIBUTE					= "Enabled";
String Common::XMLGrant::TYPE_ATTRIBUTE						= "Type";

String Common::XMLGrant::YES_ENABLED						= "YES";
String Common::XMLGrant::NO_ENABLED							= "NO";

String Common::XMLGrant::EXECUTION_TYPE						= "EXECUTION";
String Common::XMLGrant::VISIBLE_TYPE						= "VISIBLE";

//XmlApplicationFunctionParameters
String Common::XMLFormalParameters::MAIN_NODE	= "Parameters";

//XmlApplicationFunctionParameter
String Common::XMLFormalParameter::MAIN_NODE				= "Parameter";
String Common::XMLFormalParameter::NAME_ATTRIBUTE			= "Name";
String Common::XMLFormalParameter::TYPE_ATTRIBUTE			= "Type";
String Common::XMLFormalParameter::MANDATORY_ATTRIBUTE		= "Mandatory";
String Common::XMLFormalParameter::BIND_NODE				= "Bind";
String Common::XMLFormalParameter::VALUE_NODE				= "Value";

String Common::XMLFormalParameter::NONE_TYPE		= "NONE";
String Common::XMLFormalParameter::NUMBER_TYPE		= "NUMBER";
String Common::XMLFormalParameter::STRING_TYPE		= "STRING";
String Common::XMLFormalParameter::XML_TYPE			= "XML";

//XMLAttributes
String WorkflowRelevantData::XMLAttributes::MAIN_NODE			= "Attributes";

//XMLAttribute
String WorkflowRelevantData::XMLAttribute::MAIN_NODE			= "Attribute";
String WorkflowRelevantData::XMLAttribute::TYPE_ATTRIBUTE		= "Type";
String WorkflowRelevantData::XMLAttribute::NAME_ATTRIBUTE		= "Name";
String WorkflowRelevantData::XMLAttribute::DIRECTION_ATTRIBUTE	= "Direction";
String WorkflowRelevantData::XMLAttribute::VALUE_NODE			= "Value";

String WorkflowRelevantData::XMLAttribute::DIRECTION_NONE		= "NONE";
String WorkflowRelevantData::XMLAttribute::DIRECTION_INPUT		= "INPUT";
String WorkflowRelevantData::XMLAttribute::DIRECTION_OUTPUT		= "OUTPUT";
String WorkflowRelevantData::XMLAttribute::DIRECTION_INPUTOUTPUT= "INPUTOUTPUT";
String WorkflowRelevantData::XMLAttribute::DIRECTION_CONSTANT	= "COSTANT";
String WorkflowRelevantData::XMLAttribute::DIRECTION_TASK		= "TASK";
String WorkflowRelevantData::XMLAttribute::DIRECTION_NOTMIGRATE	= "NOTMIGRATE";

String WorkflowRelevantData::XMLAttribute::XML_TYPE				= "XML";
String WorkflowRelevantData::XMLAttribute::STRING_TYPE			= "STRING";
String WorkflowRelevantData::XMLAttribute::NUMBER_TYPE			= "NUMBER";
			
String WorkflowProcesses::XMLActivityComponent::ID_ATTRIBUTE	= "Id";
String WorkflowProcesses::XMLProcessComponent::PROCESS_ID_NODE	= "ProcessId";

//XmlActivities
String WorkflowProcesses::XMLActivities::MAIN_NODE			= "Activities";

//XmlActivity
String WorkflowProcesses::XMLActivity::MAIN_NODE		= "Activity";

String WorkflowProcesses::XMLActivity::ID_ATTRIBUTE		= "Id";
String WorkflowProcesses::XMLActivity::TYPE_ATTRIBUTE	= "Type";
String WorkflowProcesses::XMLActivity::NAME_ATTRIBUTE	= "Name";

String WorkflowProcesses::XMLActivity::DESCRIPTION_NODE			= "Description";
String WorkflowProcesses::XMLActivity::REFERENCE_ACTIVITY_NODE	= "ReferenceActivity";
String WorkflowProcesses::XMLActivity::CATCH_TYPE_NODE			= "CatchType";
String WorkflowProcesses::XMLActivity::NR_EXECUTED_NODE			= "NrExecuted";

String WorkflowProcesses::XMLActivity::START_TYPE		= "START";
String WorkflowProcesses::XMLActivity::END_TYPE			= "END";
String WorkflowProcesses::XMLActivity::SUBFLOW_TYPE		= "SUBFLOW";
String WorkflowProcesses::XMLActivity::API_TYPE			= "API";
String WorkflowProcesses::XMLActivity::CONDITION_TYPE	= "CONDITION";
String WorkflowProcesses::XMLActivity::ITERATION_TYPE	= "ITERATION";
String WorkflowProcesses::XMLActivity::EMAIL_TYPE		= "EMAIL";
String WorkflowProcesses::XMLActivity::APPLICATION_TYPE	= "APPLICATION";
String WorkflowProcesses::XMLActivity::XML_TYPE			= "XML";
String WorkflowProcesses::XMLActivity::EXIT_TYPE		= "EXIT";
String WorkflowProcesses::XMLActivity::EVENT_TYPE		= "EVENT";
String WorkflowProcesses::XMLActivity::THROWER_TYPE		= "THROWER";
String WorkflowProcesses::XMLActivity::CATCHER_TYPE		= "CATCHER";

String WorkflowProcesses::XMLActivity::CREATED_STATUS	= "CREATED";
String WorkflowProcesses::XMLActivity::QUEUED_STATUS	= "QUEUED";
String WorkflowProcesses::XMLActivity::RUNNING_STATUS	= "RUNNING";
String WorkflowProcesses::XMLActivity::COMPLETED_STATUS	= "COMPLETED";
String WorkflowProcesses::XMLActivity::ERROR_STATUS		= "ERROR";
String WorkflowProcesses::XMLActivity::MANUAL_STATUS	= "MANUAL";
String WorkflowProcesses::XMLActivity::WAITINGFOR_STATUS="WAITINGEVENT";

String WorkflowProcesses::XMLActivity::NEVER_CATCH_TYPE		= "NEVER";
String WorkflowProcesses::XMLActivity::EVER_CATCH_TYPE		= "EVER";
String WorkflowProcesses::XMLActivity::ONLY_ONE_CATCH_TYPE	= "ONLYONE";

String WorkflowProcesses::XMLActivity::MARKER_FEATURE		= "WFMS_FEATURE";
String WorkflowProcesses::XMLActivity::MARKER_NOTIFY_FEATURE= "NOTIFY";
String WorkflowProcesses::XMLActivity::MARKER_ASSIGN_TO		= "WFMS_ASSIGN_TO";

//Subflow
String WorkflowProcesses::XMLActivity::MARKER_OCCURENCY			= "Occurency";
String WorkflowProcesses::XMLActivity::MARKER_PROCESSNAME		= "ProcessName";
String WorkflowProcesses::XMLActivity::MARKER_EXECUTION			= "Execution";

String WorkflowProcesses::XMLActivity::MARKER_SEQUENCE_EXECUTION= "SEQUENCE";

String WorkflowProcesses::XMLBehaviour::MAIN_NODE			= "Behaviour";

String WorkflowProcesses::XMLBehaviourBase::MODE_ATTRIBUTE	= "Mode";
String WorkflowProcesses::XMLBehaviourBase::AUTOMATIC_MODE	= "AUTOMATIC";
String WorkflowProcesses::XMLBehaviourBase::MANUAL_MODE		= "MANUAL";

String WorkflowProcesses::XMLBehaviourExecution::MAIN_NODE	= "Execution";
String WorkflowProcesses::XMLBehaviourExecution::TYPE_ATTRIBUTE	= "Type";

String WorkflowProcesses::XMLBehaviourExecution::ROUTE_TYPE				= "ROUTE";
String WorkflowProcesses::XMLBehaviourExecution::IMPLEMENTATION_TYPE	= "IMPLEMENTATION";
String WorkflowProcesses::XMLBehaviourExecution::BLOCKACTIVITY_TYPE		= "BLOCKACTIVITY";

String WorkflowProcesses::XMLBehaviourFinish::MAIN_NODE	= "Finish";

String WorkflowProcesses::XMLBehaviourStart::MAIN_NODE	= "Start";
String WorkflowProcesses::XMLBehaviourStart::ONLYONE_ATTRIBUTE = "OnlyOne";
String WorkflowProcesses::XMLBehaviourStart::YES_ONLYONE	= "YES";
String WorkflowProcesses::XMLBehaviourStart::NO_ONLYONE		= "NO";

String WorkflowProcesses::XMLScript::MAIN_NODE	= "Script";
String WorkflowProcesses::XMLScript::DATATYPE_ATTRIBUTE	= "DataType";

String WorkflowProcesses::XMLScript::TYPE_ATTRIBUTE	= "Type";

String WorkflowProcesses::XMLScript::NONE_TYPE				= "NONE";
String WorkflowProcesses::XMLScript::SUBFLOW_SYNCH_TYPE		= "SUBFLOW_SYNCH";
String WorkflowProcesses::XMLScript::SUBFLOW_ASYNC_TYPE		= "SUBFLOW_ASYNC";
String WorkflowProcesses::XMLScript::SUBFLOW_SPECIAL_TYPE	= "SUBFLOW_SPECIAL";

String WorkflowProcesses::XMLScript::API_SYNCH_TYPE			= "API_SYNCH";
String WorkflowProcesses::XMLScript::API_ASYNC_TYPE			= "API_ASYNC";
String WorkflowProcesses::XMLScript::EMAIL_SMTP_TYPE		= "EMAIL";
String WorkflowProcesses::XMLScript::APPLICATION_API_TYPE	= "APPLICATION";
String WorkflowProcesses::XMLScript::XML_XSLT_TYPE			= "XSLT";
String WorkflowProcesses::XMLScript::XML_FILE_READ_TYPE		= "XML_FILE_READ";
String WorkflowProcesses::XMLScript::XML_FILE_WRITE_TYPE	= "XML_FILE_WRITE";
String WorkflowProcesses::XMLScript::EVENT_MAKER_TYPE		= "EVENT_MAKER";
String WorkflowProcesses::XMLScript::EVENT_CONSUMER_TYPE	= "EVENT_CONSUMER";
String WorkflowProcesses::XMLScript::EVAL_EXPRESSION_TYPE	= "EVAL_EXPRESSION";
String WorkflowProcesses::XMLScript::LOOP_COUNTER_TYPE		= "LOOP_COUNTER";
String WorkflowProcesses::XMLScript::LOOP_EXPRESSION_TYPE	= "LOOP_EXPRESSION";

String WorkflowProcesses::XMLLog::MAIN_NODE			= "Log";
String WorkflowProcesses::XMLLog::OWNER_ATTRIBUTE	= "Owner";
String WorkflowProcesses::XMLLog::RESULT_ATTRIBUTE	= "Result";

String WorkflowProcesses::XMLLogs::MAIN_NODE	= "Logs";

String WorkflowProcesses::XMLStatus::MAIN_NODE		= "Status";
String WorkflowProcesses::XMLStatus::DATE_ATTRIBUTE	= "Date";

String WorkflowProcesses::XMLReport::MAIN_NODE	= "Report";
String WorkflowProcesses::XMLReport::DATETIME_ATTRIBUTE	= "Date";

String WorkflowProcesses::XMLReport::DATE_TIME_VARIABLE			= "DateTime";
String WorkflowProcesses::XMLReport::PROCESS_ID_VARIABLE		= "WorkflowProcess.Id";
String WorkflowProcesses::XMLReport::WORKFLOW_NAME_VARIABLE		= "WorkflowProcess.Name";
String WorkflowProcesses::XMLReport::WORKFLOW_LEVEL_VARIABLE	= "Workflow.Level";
String WorkflowProcesses::XMLReport::ACTIVITY_NAME_VARIABLE		= "Activity.Name";

String WorkflowProcesses::XMLReports::MAIN_NODE	= "Reports";

String WorkflowProcesses::XMLTransition::MAIN_NODE		= "Transition";
String WorkflowProcesses::XMLTransition::ID_ATTRIBUTE	= "Id";
String WorkflowProcesses::XMLTransition::FROM_ATTRIBUTE	= "From";
String WorkflowProcesses::XMLTransition::TO_ATTRIBUTE	= "To";

String WorkflowProcesses::XMLTransition::RESULT_NODE	= "Result";
String WorkflowProcesses::XMLTransition::REEXEC_NODE	= "ReExec";
String WorkflowProcesses::XMLTransition::OPERATOR_NODE	= "Operator";

String WorkflowProcesses::XMLTransition::NOTEQUAL_OPERATOR			= "NotEqual";
String WorkflowProcesses::XMLTransition::EQUAL_OPERATOR				= "Equal";
String WorkflowProcesses::XMLTransition::LESS_THAN_OPERATOR			= "LessThan";
String WorkflowProcesses::XMLTransition::MORE_THAN_OPERATOR			= "GreatThan";
String WorkflowProcesses::XMLTransition::LESS_EQUAL_THAN_OPERATOR	= "LessEqualThan";
String WorkflowProcesses::XMLTransition::MORE_EQUAL_THAN_OPERATOR	= "GreatEqualThan";
String WorkflowProcesses::XMLTransition::ALWAYS_OPERATOR			= "Always";

String WorkflowProcesses::XMLTransition::YES_REEXEC		= "YES";
String WorkflowProcesses::XMLTransition::NO_REEXEC		= "NO";

String WorkflowProcesses::XMLTransitions::MAIN_NODE		= "Transitions";

//*******************************************************************
String WorkflowProcesses::XMLMessage::MAIN_NODE		= "MessageFlow";
String WorkflowProcesses::XMLMessage::ID_ATTRIBUTE	= "Id";
String WorkflowProcesses::XMLMessage::FROM_ATTRIBUTE= "From";
String WorkflowProcesses::XMLMessage::TO_ATTRIBUTE	= "To";

String WorkflowProcesses::XMLMessages::MAIN_NODE		= "MessageFlows";


String WorkflowProcesses::XMLWorkflowProcesses::MAIN_NODE	= "WorkflowProcesses";

String WorkflowProcesses::XMLWorkflowProcess::MAIN_NODE	= "WorkflowProcess";

String WorkflowProcesses::XMLWorkflowProcess::NAME_ATTRIBUTE				= "Name";
String WorkflowProcesses::XMLWorkflowProcess::STATUS_NODE					= "Status";
String WorkflowProcesses::XMLWorkflowProcess::DESCRIPTION_NODE				= "Description";
String WorkflowProcesses::XMLWorkflowProcess::PARENT_PROCESS_NODE			= "ParentProcess";
String WorkflowProcesses::XMLWorkflowProcess::ACTIVITY_PARENT_PROCESS_NODE	= "ActivityParentProcess";
String WorkflowProcesses::XMLWorkflowProcess::EXIT2MANAGE_NODE				= "Exit2Manage";

String WorkflowProcesses::XMLWorkflowProcess::CREATED_STATUS	= "CREATED";
String WorkflowProcesses::XMLWorkflowProcess::QUEUED_STATUS		= "QUEUED";
String WorkflowProcesses::XMLWorkflowProcess::RUNNING_STATUS	= "RUNNING";
String WorkflowProcesses::XMLWorkflowProcess::COMPLETED_STATUS	= "COMPLETED";
String WorkflowProcesses::XMLWorkflowProcess::ERROR_STATUS		= "ERROR";

//XmlUsers
String WorkflowParticipantsData::XMLUsers::MAIN_NODE			= "Users";

//XmlUser
String WorkflowParticipantsData::XMLUser::MAIN_NODE				= "User";
String WorkflowParticipantsData::XMLUser::KEY_ATTRIBUTE			= "Key";
String WorkflowParticipantsData::XMLUser::NAME_NODE				= "Name";
String WorkflowParticipantsData::XMLUser::DESCRIPTION_NODE		= "Description";
String WorkflowParticipantsData::XMLUser::PASSWORD_NODE			= "Password";
String WorkflowParticipantsData::XMLUser::DISPLAYNAME_NODE		= "DisplayName";
String WorkflowParticipantsData::XMLUser::EMAIL_NODE			= "Email";

//XmlRoles
String WorkflowParticipantsData::XMLRoles::MAIN_NODE	= "Roles";

//XmlRole
String WorkflowParticipantsData::XMLRole::MAIN_NODE				= "Role";
String WorkflowParticipantsData::XMLRole::KEY_ATTRIBUTE			= "Key";
String WorkflowParticipantsData::XMLRole::NAME_NODE				= "Name";
String WorkflowParticipantsData::XMLRole::DESCRIPTION_NODE		= "Description";

//XmlServices
String WorkflowServices::XMLServices::MAIN_NODE					= "Services";

//XmlService
String WorkflowServices::XMLService::MAIN_NODE					= "Service";
String WorkflowServices::XMLService::NAME_ATTRIBUTE				= "Name";
String WorkflowServices::XMLService::WORKFLOW_NODE				= "Workflow";
String WorkflowServices::XMLService::DESCRIPTION_NODE			= "Description";

//XmlDataBase
String DataBase::XMLDataBase::MAIN_NODE	= "DataBaseManager";

String DataBase::XMLConnections::MAIN_NODE	= "Connections";

String DataBase::XMLConnection::ID_ATTRIBUTE	= "Id";
String DataBase::XMLConnection::TYPE_ATTRIBUTE	= "Type";

String DataBase::XMLConnection::PRIMARY_TYPE	= "Primary";

String DataBase::XMLDataBaseObjectManager::MAIN_NODE	= "ObjectManager";

//
String DataBase::XMLDataBaseObject::MAIN_NODE			= "Object";
String DataBase::XMLDataBaseObject::TYPE_ATTRIBUTE		= "Type";

String DataBase::XMLDataBaseObject::PROCESSESINSTANCE_TYPE	= "ProcessInstance";
String DataBase::XMLDataBaseObject::PROCESSESTEMPLATE_TYPE	= "ProcessTemplate";
String DataBase::XMLDataBaseObject::DATATYPES_TYPE		= "DataTypes";
String DataBase::XMLDataBaseObject::SERVICES_TYPE		= "Services";
String DataBase::XMLDataBaseObject::USERS_TYPE			= "Users";
String DataBase::XMLDataBaseObject::ROLES_TYPE			= "Roles";
String DataBase::XMLDataBaseObject::APPLICATIONS_TYPE	= "Applications";
String DataBase::XMLDataBaseObject::APPLICATIONS_DATABASE_TYPE	= "ApplicationsDataBase";
String DataBase::XMLDataBaseObject::EVENTS_TYPE			= "Events";
String DataBase::XMLDataBaseObject::OCCURREDEVENTS_TYPE	= "OccurredEvents";
String DataBase::XMLDataBaseObject::WAITINGEVENTS_TYPE	= "WaitingEvents";
String DataBase::XMLDataBaseObject::REPORTS_TYPE		= "Reports";
String DataBase::XMLDataBaseObject::CHECKLIST_TYPE		= "CheckList";
String DataBase::XMLDataBaseObject::FORMS_TYPE			= "FormTemplate";

String DataBase::XMLDataBaseObject::MANAGED_ATTRIBUTE	= "Managed";
String DataBase::XMLDataBaseObject::YES_MANAGED			= "Yes";
String DataBase::XMLDataBaseObject::NO_MANAGED			= "No";

String DataBase::XMLDataBaseObject::REPOSITORY_ATTRIBUTE = "Repository";
String DataBase::XMLDataBaseObject::FOLDER_REPOSITORY		= "Folder";
String DataBase::XMLDataBaseObject::FILE_REPOSITORY			= "File";

//FileSystem Connection
String DataBase::XMLFileSystemConnection::MAIN_NODE					= "CriteriaFileSystem";

//MySQL
String DataBase::XMLmySQLConnection::MAIN_NODE		= "MySQL";
String DataBase::XMLmySQLConnection::HOST_NODE		= "Host";
String DataBase::XMLmySQLConnection::PORT_NODE		= "Port";
String DataBase::XMLmySQLConnection::USER_NODE		= "User";
String DataBase::XMLmySQLConnection::PASSWORD_NODE	= "Password";
String DataBase::XMLmySQLConnection::DATABASE_NODE	= "DataBase";

//ODBC
String DataBase::XMLODBCConnection::MAIN_NODE		= "ODBC";
String DataBase::XMLODBCConnection::USER_NODE		= "User";
String DataBase::XMLODBCConnection::PASSWORD_NODE	= "Password";
String DataBase::XMLODBCConnection::DSN_NODE		= "Dsn";

//SQLite
String DataBase::XMLSQLiteConnection::MAIN_NODE		= "SQLite";
String DataBase::XMLSQLiteConnection::PATH_NODE		= "Path";
String DataBase::XMLSQLiteConnection::DATABASE_NODE	= "DataBase";

//XMLPoolManager
String DataBase::XMLPoolManager::MAIN_NODE		= "PoolManager";
String DataBase::XMLPoolManager::MIN_ATTRIBUTE	= "Min";
String DataBase::XMLPoolManager::MAX_ATTRIBUTE	= "Max";
String DataBase::XMLPoolManager::RETRY_NODE		= "Retry";
String DataBase::XMLPoolManager::DELAY_NODE		= "Delay";

String WorkflowDataTypes::XMLDataType::MAIN_NODE		= "DataType";
String WorkflowDataTypes::XMLDataType::KEY_ATTRIBUTE	= "Key";
String WorkflowDataTypes::XMLDataType::TYPE_ATTRIBUTE	= "Type";
String WorkflowDataTypes::XMLDataType::DESCRIPTION_NODE	= "Description";


String WorkflowDataTypes::XMLDataTypes::MAIN_NODE	= "DataTypes";

String WorkflowDataTypes::XMLDataTypeValue::MAIN_NODE		= "Value";
String WorkflowDataTypes::XMLDataTypeValue::KEY_ATTRIBUTE	= "Key";

String WorkflowDataTypes::XMLDataTypeValues::MAIN_NODE		= "EnumerationValues";
