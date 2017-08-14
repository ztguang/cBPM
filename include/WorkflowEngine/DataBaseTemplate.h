#ifndef _DATABASE_TEMPLATE_H_
#define _DATABASE_TEMPLATE_H_

#include "CommonDefines.h"

#include "bOSSQLConnectionManager.h"
#include "bOSSQLConnectionData.h"
#include "bOSSQLTable.h"
#include "bOSSQLCommand.h"
#include "bOSFileSystem.h"


#include "PoolManager.h"
#include "FileSystemConnection.h"


#include "WorkflowProcess.h"
#include "Activities.h"
#include "Activity.h"

//Participants
#include "User.h"
#include "Users.h"
#include "Role.h"
#include "Roles.h"

//DataTypes
#include "DataTypes.h"

//Services
#include "Services.h"

//ApplicationDataModel
#include "Applications.h"

#include "Connection.h"

namespace DataManager
{
	namespace DataBase
	{
		class DataBaseTemplate
		{
		public:
			//invoked only by FileSystemDataBase
			DataBaseTemplate();
			DataBaseTemplate(bOS::SQL::SQLConnectionManager::DataBaseType dbType);
			virtual ~DataBaseTemplate();

			//only for FileSystemDataBase.
			virtual void open(DataManager::Panorama::DataBase::FileSystemConnection*) {;}

			void open(bOS::SQL::SQLConnectionData*, DataManager::Panorama::DataBase::PoolManager);
			
			virtual void close();

			void setXMLConnection(DataManager::Panorama::DataBase::Connection* connection);
			DataManager::Panorama::DataBase::Connection& getXMLConnection() { return xmlConnection;}

			virtual int ExecuteSQLCommand(const char* acSQL);

			//Users
			virtual void getUser(DataManager::Panorama::WorkflowParticipantsData::User&);
			virtual void getUsers(DataManager::Panorama::WorkflowParticipantsData::Users&);
			virtual void addUser(const char* acUser);
			virtual void updateUser(const char* acUser);
			virtual void deleteUser(const char* acUserKey);

			//Roles
			virtual void getRoles(DataManager::Panorama::WorkflowParticipantsData::Roles&);
			virtual void getRole(DataManager::Panorama::WorkflowParticipantsData::Role&);
			virtual void addRole(const char* acRole);
			virtual void updateRole(const char* acRole);
			virtual void deleteRole(const char* acRoleKey);
			virtual void addUserToRole(const char* acUser, const char* acRoleKey);
			virtual void deleteUserFromRole(const char* acUserKey, const char* acRoleKey);
			virtual void getRolesByUser(const char* acUserKey, DataManager::Panorama::WorkflowParticipantsData::Roles&);

			//DataTypes
			virtual void getDataTypes(DataManager::Panorama::WorkflowDataTypes::DataTypes&);
			virtual void getDataType(DataManager::Panorama::WorkflowDataTypes::DataType&);

			//Services
			virtual void getServices(DataManager::Panorama::WorkflowServices::Services&);
			virtual void getServicesForUser(const char* acUser, DataManager::Panorama::WorkflowServices::Services& vServices);
			virtual void addService (const char* acService);
			virtual void deleteService(const char* acServiceName);

			//Applications
			virtual void getApplications(DataManager::Panorama::WorkflowApplicationsData::Applications&) {;}

			//
			virtual void getActivities(DataManager::Panorama::WorkflowProcesses::Activities&, String sStatus, String sOwner, bool bOnlyMine);
			virtual void getAllActivities(DataManager::Panorama::WorkflowProcesses::Activities&, String sOwner, bool bNotMine);
			virtual void getAllMyActivities(DataManager::Panorama::WorkflowProcesses::Activities&, String sOwner);
			virtual void getNotifies(WorkflowProcesses::Activities&, String sOwner);
			virtual void getActivityRunningNotifies(WorkflowProcesses::Activities& vActivities, String sOwner);
			virtual void updateActivity(DataManager::Panorama::WorkflowProcesses::Activity* activity, bool bRecursive);
			virtual void getActivity(DataManager::Panorama::WorkflowProcesses::Activity&);
			virtual void updateActivityCheckStatus(DataManager::Panorama::WorkflowProcesses::Activity* activity, string sStatus2Check);
			virtual void updateActivityNoOwner(DataManager::Panorama::WorkflowProcesses::Activity* activity);

			

			//
			virtual void insertProcess(String& lProcessId, DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process, bool b2Prepared = false);
			virtual void getProcessInstance(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process);
			virtual void getProcessHeader(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process);
			void getNewProcessHeader(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process);
			bOS::CoreString::String getProcessStatus(const char* processId);
			virtual void updateProcess(DataManager::Panorama::WorkflowProcesses::WorkflowProcess*);
			void getProcesses(WorkflowProcesses::Processes& vProcesses);

			virtual void insertReport(WorkflowProcesses::Report& report);
			virtual void getReports (WorkflowProcesses::Reports& vReports);

			//Attributes
			virtual void updateAttributes(WorkflowRelevantData::Attributes& vAttributes);
			/*
			virtual void updateAttributes(DataManager::Panorama::WorkflowProcesses::Activity& activity);
			virtual void updateAttributes(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process);
			*/

			virtual void getProcessAttribute(const char* processId, WorkflowRelevantData::Attribute& attribute);
			virtual void getAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes);

			bool CheckGrant(DataManager::Panorama::Common::Grants& vGrants, const char* acUser, const char* acGrantType);

			virtual bOS::IO::FilesList getWorkflowList();
			virtual DataManager::Panorama::WorkflowProcesses::WorkflowProcess* getProcessTemplate(const char* acWorkflowName);
			virtual void addWorkflow(WorkflowProcesses::WorkflowProcess*);
			
			virtual String getCheckListFolder();


			void saveMessageFlow(WorkflowProcesses::Message* message);


			virtual bOS::IO::FilesList getFormsList();
			virtual bOS::CoreString::String getForm(const char* acFormName);
			virtual void setForm(const char* acFormName, const char* acJsContent);

			bOS::SQL::SQLConnectionManager& getManager() { return manager;}

		private:

			DataManager::Panorama::DataBase::Connection xmlConnection;

			int executeSQL(bOS::SQL::SQLConnection* connection, bOS::SQL::SQLTable* table, bOS::SQL::SQLCommand::SQLOperation iOperation, const char* acSQL, bool bMainTable);
			void executeRecursiveSQLCommands(bOS::SQL::SQLConnection* connection, bOS::SQL::SQLTable* sqlTable, bOS::SQL::SQLCommand::SQLOperation operation, const char* acWhere, bool bMainTable);
			int executeSQLCommands(bOS::SQL::SQLConnection* connection, bOS::SQL::SQLTable* table, bOS::SQL::SQLCommand::SQLOperation iOperation, const char* acWhere, bool bMainTable);
			int executePrepareSQLCommands(bOS::SQL::SQLConnection* connection, bOS::SQL::SQLTable* table, bOS::SQL::SQLCommand::SQLOperation iOperation, const char* acWhere, bool bMainTable);
			

			bOS::SQL::SQLConnectionManager manager;
			
			unsigned int iRetry;
			unsigned int iDelay;

			String sDBPath;
		};
	}
}

#endif //_DATABASE_TEMPLATE_H_
