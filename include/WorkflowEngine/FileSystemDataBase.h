#ifndef _FILE_SYSTEM_DATA_BASE_H_
#define _FILE_SYSTEM_DATA_BASE_H_

#include "CommonDefines.h"

#include "FileSystemConnection.h"

//Participants
#include "User.h"
#include "Users.h"
#include "Role.h"
#include "Roles.h"

//DataTypes
#include "DataTypes.h"

//
#include "Applications.h"

#include "WorkflowProcessInstanceRepository.h"

//ApplicationDataModel
#include "Applications.h"

#include "DataBaseTemplate.h"


namespace DataManager
{
	namespace DataBase
	{
		namespace FileSystem
		{
			class FileSystemDataBase : public DataManager::DataBase::DataBaseTemplate
			{
			public:
				FileSystemDataBase();
				~FileSystemDataBase();

				void open(DataManager::Panorama::DataBase::FileSystemConnection*);
				void close();

				int ExececuteSQLCommand(const char* acSQL) {;}

				//Users
				void getUser(DataManager::Panorama::WorkflowParticipantsData::User&);
				void getUsers(DataManager::Panorama::WorkflowParticipantsData::Users&);
				void addUser(const char* acUser);
				void updateUser(const char* acUser);
				void deleteUser(const char* acUserKey);

				//Roles
				void getRoles(DataManager::Panorama::WorkflowParticipantsData::Roles&);
				void getRole(DataManager::Panorama::WorkflowParticipantsData::Role&);
				void addRole(const char* acRole);
				void updateRole(const char* acRole);
				void deleteRole(const char* acRoleKey);
				void addUserToRole(const char* acUser, const char* acRoleKey);
				void deleteUserFromRole(const char* acUserKey, const char* acRoleKey);
				void getRolesByUser(const char* acUserKey, DataManager::Panorama::WorkflowParticipantsData::Roles&);

				//DataTypes
				void getDataTypes(DataManager::Panorama::WorkflowDataTypes::DataTypes&);
				void getDataType(DataManager::Panorama::WorkflowDataTypes::DataType&);

				//Services
				void getServices(DataManager::Panorama::WorkflowServices::Services&);
				void getServicesForUser(const char* acUser, DataManager::Panorama::WorkflowServices::Services& vServices);
				void addService (const char* acService);
				void deleteService(const char* acServiceName);

				//Applications
				void getApplications(DataManager::Panorama::WorkflowApplicationsData::Applications&);


				//Activities
				void getActivities(DataManager::Panorama::WorkflowProcesses::Activities&, String sStatus, String sOwner, bool bOnlyMine);
				void getAllActivities(DataManager::Panorama::WorkflowProcesses::Activities&, String sStatus, String sOwner, bool bNotMine);
				void getAllMyActivities(DataManager::Panorama::WorkflowProcesses::Activities&, String sStatus, String sOwner);
				void getNotifies(WorkflowProcesses::Activities&, String sOwner);
				void getActivityRunningNotifies(WorkflowProcesses::Activities&, String sOwner);
				void updateActivity(DataManager::Panorama::WorkflowProcesses::Activity* activity, bool bRecursive);
				void getActivity(DataManager::Panorama::WorkflowProcesses::Activity&);
				void updateActivityCheckStatus(DataManager::Panorama::WorkflowProcesses::Activity* activity, string sStatus2Check);
				void updateActivityNoOwner(DataManager::Panorama::WorkflowProcesses::Activity* activity);

				//
				void insertProcess(String& lProcessId, DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process,bool b2Prepared = false);
				void getProcessInstance(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process);
				void getProcessHeader(DataManager::Panorama::WorkflowProcesses::WorkflowProcess& process);
				void updateProcess(DataManager::Panorama::WorkflowProcesses::WorkflowProcess*);
				void insertReport(WorkflowProcesses::Report& report);
				void getReports (WorkflowProcesses::Reports& vReports);
				void getProcesses(WorkflowProcesses::Processes& vProcesses);

				//Attributes
				void updateAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes);
				void getAttributes(DataManager::Panorama::WorkflowRelevantData::Attributes& vAttributes);
				void getProcessAttribute(const char* processId, WorkflowRelevantData::Attribute& attributes);

				void saveMessageFlow(WorkflowProcesses::Message* message);

				bOS::IO::FilesList getWorkflowList();
				bOS::IO::FilesList getFormsList();
				bOS::CoreString::String getForm(const char* acFormName);
				void setForm(const char* acFormName, const char* acJsContent);
				WorkflowProcesses::WorkflowProcess* getProcessTemplate(const char* acWorkflowName);

				void addWorkflow(WorkflowProcesses::WorkflowProcess*);

				String getCheckListFolder();

			private:

				DataManager::Panorama::DataBase::FileSystemConnection fsConnection;

				//
				DataManager::Panorama::WorkflowParticipantsData::Users vUsers;
				DataManager::Panorama::WorkflowParticipantsData::Roles vRoles;
				
				//
				DataManager::Panorama::WorkflowDataTypes::DataTypes vDataTypes;
				
				//
				DataManager::Panorama::WorkflowApplicationsData::Applications vApplications;

				//
				WorkflowProcessInstanceRepository vProcesses;
			};
		}
	}
}

#endif //_FILE_SYSTEM_DATA_BASE_H_