#ifndef _DATABASE_HELPER_H_
#define _DATABASE_HELPER_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

//Participants
#include "User.h"
#include "Users.h"
#include "Role.h"
#include "Roles.h"

#include "DataTypes.h"

#include "Services.h"

#include "WorkflowProcess.h"

//ApplicationDataModel
#include "Applications.h"

#include "bOSFileSystem.h"

#include "bOSSQLConnectionManager.h"

#include "ProcessesHandler.h"

#include "Event.h"
#include "OccurredEvent.h"
#include "WaitingActivity.h"
#include "WaitingActivities.h"
using namespace DataManager::Panorama;

namespace DataManager
{
	namespace DataBase
	{
		class DataBaseTemplate;
		typedef vector<DataBaseTemplate*> dbList;

		class ENGINE_API DataBaseHelper
		{
		public:

			static DataBaseHelper* instance();
			static void deinstance();

			void open(String sConfigurationFile);
			void close();

			int ExecuteSQLCommand(const char* acSQL);

			//Users
			void getUser(WorkflowParticipantsData::User&);
			void getUsers(WorkflowParticipantsData::Users&);
			void addUser(const char* acUser);
			void updateUser(const char* acUser);
			void deleteUser(const char* acUserKey);

			//Roles
			void getRoles(WorkflowParticipantsData::Roles&);
			void getRole(WorkflowParticipantsData::Role&);
			void addRole(const char* acRole);
			void updateRole(const char* acRole);
			void deleteRole(const char* acRoleKey);
			void addUserToRole(const char* acUser, const char* acRoleKey);
			void deleteUserFromRole(const char* acUserKey, const char* acRoleKey);
			void getRolesByUser(const char* acUserKey, WorkflowParticipantsData::Roles&);

			//DataTypes
			void getDataTypes(WorkflowDataTypes::DataTypes&);
			void getDataType(WorkflowDataTypes::DataType&);
			string GetValueFromDataType(const string& sDataType, const String& sValueKey);

			//Services
			void getServices(WorkflowServices::Services&);
			void getServicesForUser(const char* acUser, WorkflowServices::Services&);
			void addService (const char* acService);
			void deleteService(const char* acServiceName);

			//
			bOS::IO::FilesList getWorkflowList();
			String createProcess(const char* acWorkflowName, WorkflowProcesses::WorkflowProcess& process, bool b2Prepared = false);
			WorkflowProcesses::WorkflowProcess* getProcessInstance(const char* lProcessId);
			WorkflowProcesses::WorkflowProcess* LoadProcessInstance(const char* lProcessId);
			WorkflowProcesses::WorkflowProcess* getProcessHeader(const char* getProcessHeader);
			WorkflowProcesses::WorkflowProcess* getNewProcessHeader(const char* getProcessHeader);
			bOS::CoreString::String getProcessStatus(const char* lProcessId);
			void releaseProcess(WorkflowProcesses::WorkflowProcess* process);
			WorkflowProcesses::WorkflowProcess* addUsersToProcess(WorkflowProcesses::WorkflowProcess*);
			void updateProcess(WorkflowProcesses::WorkflowProcess*);
			void getProcesses(WorkflowProcesses::Processes& vProcesses);

			//Forms
			bOS::IO::FilesList getFormsList();
			bOS::CoreString::String getForm(const char* acFormName);
			void setForm(const char* acFormName, const char* acJsContent);

			//Attributes
			void updateAttributes(WorkflowRelevantData::Attributes& vAttributes);
			void SetAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes);
			/*
			void updateAttributes(DataManager::Panorama::WorkflowProcesses::Activity& activity);
			void updateAttributes(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process);
			*/

			void getProcessAttribute(const char* processId, WorkflowRelevantData::Attribute& attributes);
			void getAttributes(WorkflowRelevantData::Attributes& vAttributes);


			//Activities
			//if bOnlyMine is setted to true getActivites retrieve only Activity which owner = sOwner
			//otherwise alla activity "locked" by sOwner
			void getNotifies(WorkflowProcesses::Activities& vActivities, String sOwner);
			void getActivityRunningNotifies(WorkflowProcesses::Activities& vActivities, String sOwner);
			void getActivities(WorkflowProcesses::Activities&, String sStatus, String sOwner, bool bOnlyMine);
			void getAllActivities(WorkflowProcesses::Activities&, String sOwner, bool bNotMine);
			void getAllMyActivities(WorkflowProcesses::Activities& , String sOwner);
			void getActivity(WorkflowProcesses::Activity&);
			
			void updateActivity(WorkflowProcesses::Activity* activity, bool bRecursive);
			void updateActivityCheckStatus(DataManager::Panorama::WorkflowProcesses::Activity* activity, string sStatus2Check);
			void updateActivityNoOwner(DataManager::Panorama::WorkflowProcesses::Activity* activity);

			//Applications
			void getApplications(WorkflowApplicationsData::Applications&);
			void getApplication(WorkflowApplicationsData::Application&);

			//Reports
			void insertReport(WorkflowProcesses::Report& report);
			void getReports (WorkflowProcesses::Reports& vReports);

			//Events
			WorkflowEvents::Event* getEventDefinition(const String& sEventId);
			void addOccurredEvent(WorkflowEvents::OccurredEvent* event);
			void addWaitingActivity(WorkflowEvents::Event* event, WorkflowEvents::WaitingActivity* activity);
			WorkflowEvents::WaitingActivities* getWaitingForActivities(const String& sEventId);
			WorkflowEvents::OccurredEvent* getUnmanagedEvent(bool bManaging);
			void updateOccurredEvent(WorkflowEvents::OccurredEvent* event);
			void updateWaitingActivity(WorkflowEvents::WaitingActivity* activity);

			//Messages
			void saveMessageFlow(WorkflowProcesses::Message* message);

			//Workflow
			void addWorkflow(const char* acWorkflow);

			//
			bOS::SQL::SQLConnectionManager& getManager();

			//
			static String DATABASE_TAG_DIRECTORY;

			bool CheckGrant(DataManager::Panorama::Common::Grants& vGrants, const char* acUser, const char* acGrantType);

			String getCheckListFolder();

		private:

			static DataBaseHelper* _instance;

			DataBaseHelper();
			virtual ~DataBaseHelper();

			//
			dbList vDataBases;

			static String WORKFLOW_EXTENSION;

			ProcessesHandler processesHandler;

			bool bOpened;
		};
	}
}


#endif //_DATABASE_HELPER_H_
