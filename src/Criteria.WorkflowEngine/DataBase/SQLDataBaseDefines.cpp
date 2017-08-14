#include "ExtendedAttributes.h"
#include "ExtendedAttribute.h"
#include "Grants.h"
#include "Grant.h"
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
#include "PoolManager.h"
#include "DataType.h"
#include "DataTypes.h"
#include "DataTypeValue.h"
#include "DataTypeValues.h"

using namespace DataManager::Panorama;

String WorkflowRelevantData::SQLAttribute::TABLE_NAME		= "SF_Attributes";
String WorkflowRelevantData::SQLAttribute::NAME_FIELD		= "NAME";
String WorkflowRelevantData::SQLAttribute::DIRECTION_FIELD	= "DIRECTION";
String WorkflowRelevantData::SQLAttribute::TYPE_FIELD		= "TYPE";
String WorkflowRelevantData::SQLAttribute::VALUE_FIELD		= "VALUE";

String WorkflowProcesses::SQLActivities::TABLE_NAME				= "SF_Activities";

String WorkflowProcesses::SQLActivity::TABLE_NAME				= "SF_Activities";
String WorkflowProcesses::SQLActivity::TYPE_FIELD				= "Type";
String WorkflowProcesses::SQLActivity::DESCRIPTION_FIELD		= "Description";
String WorkflowProcesses::SQLActivity::REFERENCE_ACTIVITY_FIELD	= "ReferenceActivity";
String WorkflowProcesses::SQLActivity::NAME_FIELD				= "Name";
String WorkflowProcesses::SQLActivity::STATUS_FIELD				= "Status";
String WorkflowProcesses::SQLActivity::OWNER_FIELD				= "Owner";

String WorkflowProcesses::SQLActivity::CATCH_TYPE_FIELD			= "CatchType";
String WorkflowProcesses::SQLActivity::NR_EXECUTED_FIELD		= "NR_EXECUTED";

String WorkflowProcesses::SQLActivity::GRANTS_FIELD				= "GRANTS";
String WorkflowProcesses::SQLActivity::BEHAVIOUR_FIELD			= "BEHAVIOUR";
String WorkflowProcesses::SQLActivity::LOG_FIELD				= "LOG";
String WorkflowProcesses::SQLActivity::LOGS_FIELD				= "LOGS";
String WorkflowProcesses::SQLActivity::REPORTS_FIELD			= "REPORTS";

String WorkflowProcesses::SQLActivityComponent::ACTIVITY_ID_FIELD	= "ACTIVITY_ID";
String WorkflowProcesses::SQLProcessComponent::PROCESS_ID_FIELD		= "PROCESS_ID";

String WorkflowProcesses::SQLReports::TABLE_NAME	= "SF_REPORTS";

String WorkflowProcesses::SQLReport::TABLE_NAME			= "SF_REPORTS";
String WorkflowProcesses::SQLReport::DATETIME_FIELD		= "DATE";
String WorkflowProcesses::SQLReport::DESCRIPTION_FIELD	= "DESCRIPTION";

String WorkflowProcesses::SQLWorkflowProcess::TABLE_NAME	= "SF_WorkflowProcesses";

String WorkflowProcesses::SQLWorkflowProcess::NAME_FIELD					= "Name";
String WorkflowProcesses::SQLWorkflowProcess::STATUS_FIELD					= "Status";
String WorkflowProcesses::SQLWorkflowProcess::DESCRIPTION_FIELD				= "Description";

String WorkflowProcesses::SQLWorkflowProcess::PARENT_PROCESS_FIELD			= "ParentProcess";
String WorkflowProcesses::SQLWorkflowProcess::ACTIVITY_PARENT_PROCESS_FIELD	= "ActivityParentProcess";
String WorkflowProcesses::SQLWorkflowProcess::EXIT2MANAGE_FIELD				= "Exit2Manage";

String WorkflowProcesses::SQLWorkflowProcess::TRANSITIONS_FIELD	= "Transitions";
String WorkflowProcesses::SQLWorkflowProcess::MESSAGES_FIELD	= "MessageFlows";

String WorkflowProcesses::SQLWorkflowProcess::COMPLETITIONDATE_FIELD = "Completed";
String WorkflowProcesses::SQLWorkflowProcess::CREATIONDATE_FIELD	= "Created";


String WorkflowProcesses::SQLMessages::TABLE_NAME				= "SF_MessageFlows";

String WorkflowProcesses::SQLMessage::TABLE_NAME				= "SF_MessageFlows";
String WorkflowProcesses::SQLMessage::ID_FIELD					= "ID";
String WorkflowProcesses::SQLMessage::FROM_FIELD				= "ObjectFrom";
String WorkflowProcesses::SQLMessage::TO_FIELD					= "ObjectTo";
String WorkflowProcesses::SQLMessage::ATTRIBUTES_FIELD			= "Attributes";


String WorkflowParticipantsData::SQLUser::TABLE_NAME			= "SF_Users";
String WorkflowParticipantsData::SQLUser::KEY_FIELD				= "UserKey";
String WorkflowParticipantsData::SQLUser::NAME_FIELD			= "Name";
String WorkflowParticipantsData::SQLUser::DESCRIPTION_FIELD		= "Description";
String WorkflowParticipantsData::SQLUser::PASSWORD_FIELD		= "UserPassword";
String WorkflowParticipantsData::SQLUser::DISPLAYNAME_FIELD		= "DisplayName";
String WorkflowParticipantsData::SQLUser::EMAIL_FIELD			= "Email";

String WorkflowParticipantsData::SQLRole::TABLE_NAME			= "SF_Roles";
String WorkflowParticipantsData::SQLRole::KEY_FIELD				= "RoleKey";
String WorkflowParticipantsData::SQLRole::NAME_FIELD			= "Name";
String WorkflowParticipantsData::SQLRole::DESCRIPTION_FIELD		= "Description";
String WorkflowParticipantsData::SQLRole::USERS_FIELD			= "Users";

String WorkflowDataTypes::SQLDataTypes::TABLE_NAME				= "SF_DataTypes";

String WorkflowDataTypes::SQLDataType::TABLE_NAME				= "SF_DataTypes";
String WorkflowDataTypes::SQLDataType::KEY_FIELD				= "DataTypeKey";
String WorkflowDataTypes::SQLDataType::TYPE_FIELD				= "Type";
String WorkflowDataTypes::SQLDataType::DESCRIPTION_FIELD		= "Description";
String WorkflowDataTypes::SQLDataType::VALUES_FIELD				= "Values";

String WorkflowServices::SQLService::TABLE_NAME					= "SF_Services";
String WorkflowServices::SQLService::NAME_FIELD					= "Name";
String WorkflowServices::SQLService::WORKFLOW_FIELD				= "Workflow";
String WorkflowServices::SQLService::DESCRIPTION_FIELD			= "Description";
String WorkflowServices::SQLService::USERS_FIELD				= "Users";
String WorkflowServices::SQLService::ROLES_FIELD				= "Roles";
String WorkflowServices::SQLService::EXTENDEDATTRIBUTES_FIELD	= "ExtendedAttributes";

String WorkflowServices::SQLServices::TABLE_NAME				= "SF_Services";
