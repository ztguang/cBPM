#ifndef _WORKFLOW_PROCESS_H_
#define _WORKFLOW_PROCESS_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLFile.h"

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "CriteriaCommonDefines.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLTable.h"

#include "bOSDateTime.h"

#include "Attributes.h"
#include "Transitions.h"
#include "Messages.h"
#include "Activities.h"
#include "Reports.h"

#include "ProcessComponent.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class WorkflowProcess;

			typedef vector<WorkflowProcess*> Processes;
			class ENGINE_API WorkflowProcess :	public bOS::XML::Data::XMLFile,
													public bOS::SQL::SQLTable,
													public ProcessComponent
			{
			public:

				WorkflowProcess();
				WorkflowProcess(bOS::XML::XMLNode* node);
				virtual ~WorkflowProcess();

				//XMLFile
				void init();
				bool init(bOS::XML::XMLNode*);
				bool init(const char*);
				bool parse(bOS::XML::XMLAttribute*);
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				String getFileName();

				//SQLTable
				const char* acGetTableName();
				void setRecord(bOS::SQL::ResultSetRecord&);
				String acGetWhere();
				bool parse(bOS::SQL::ResultSetField*);
				bool parse(bOS::SQL::ResultSetRecord*);
				bOS::SQL::SQLTablesList getSQLTables();

				bool haveAutoIncrementField() { return false;}
				void setAutoIncrementField(long );

				//Attributi strutturati
				WorkflowRelevantData::Attributes& getAttributes();
				Activities& getActivities() {return vActivities;}
				Reports& getReports() {return vReports;}
				Transitions& getTransitions() {return vTransitions;}
				Messages& getMessages() {return vMessages;}

				ActivitiesList getNextActivityList(String sActivity);

				String&	getName() {return sName;}
				String&	getDescription() {return sDescription;}
				String& getStatus() {return sStatus;}

				void setName (const String& Value) {sName=Value;}
				void setDescription (const String& Value) {sDescription=Value;}
				void setStatus (const String& Value) {sStatus=Value;}

				//ParentProcess and ActivityParentProcess are relative to Process caller.
				//both are setted only if workfloss is invoked as subflow.
				void setParentProcess(const char* Value )		{ parentProcess = Value;}
				const char* getParentProcess()							{ return parentProcess.c_str();}
				const char* getTaskParentProcess()					{ return taskParentProcess.c_str();}
				void setTaskParentProcess(const char* Value)	{ taskParentProcess = Value;}

				//sExit2Manage tells if process, invoked as subflow, is terminated by exit activity.
				void setExit2Manage()	{ sExit2Manage = "YES";}
				void setExitManaged()	{ sExit2Manage = "NO";}
				bool exit2Manage()		{ return sExit2Manage == "YES";}

				//Status management method
				//////////////////////////////////////////////////////////////////////////////////////
				bool isCreated();
				bool isQueued();
				bool isRunning();
				bool isCompleted();
				bool isError();

				void setCreated();
				void setQueued();
				void setRunning();
				void setCompleted();
				void setError();
				///////////////////////////////////////////////////////////////

				//
				void setProcessId(const char* _ProcessId);
				void setSequence(long _Sequence);



				private:

					String	sCreated;
					String	sCompleted;
					String     sName;
					String     sDescription;
					String     sStatus;

					//ParentProcess
					String parentProcess;
					String taskParentProcess;
					String sExit2Manage;

					Activities vActivities;
					Transitions vTransitions;
					Messages vMessages;
					DataManager::Panorama::WorkflowRelevantData::Attributes vAttributes;
					Reports vReports;
			};

			//TODO: WorkflowProcesses to develop.
			class ENGINE_API XMLWorkflowProcesses
			{
			public:
				static String MAIN_NODE;
			};

			class ENGINE_API XMLWorkflowProcess
			{
			public:
				static String MAIN_NODE;

				static String NAME_ATTRIBUTE;
				static String STATUS_NODE;
				static String DESCRIPTION_NODE;
				static String PARENT_PROCESS_NODE;
				static String ACTIVITY_PARENT_PROCESS_NODE;
				static String EXIT2MANAGE_NODE;

				//Process Status
				static String CREATED_STATUS;
				static String QUEUED_STATUS;
				static String RUNNING_STATUS;
				static String COMPLETED_STATUS;
				static String ERROR_STATUS;

				friend class WorkflowProcess;
			};

			class ENGINE_API SQLWorkflowProcess
			{
			public:
				static String TABLE_NAME;

				static String NAME_FIELD;
				static String STATUS_FIELD;
				static String DESCRIPTION_FIELD;

				static String PARENT_PROCESS_FIELD;
				static String ACTIVITY_PARENT_PROCESS_FIELD;
				static String EXIT2MANAGE_FIELD;

				static String TRANSITIONS_FIELD;
				static String MESSAGES_FIELD;

				static String CREATIONDATE_FIELD;
				static String COMPLETITIONDATE_FIELD;

				friend class WorkflowProcess;
			};
		}
	}
}

#endif //_WORKFLOW_PROCESS_H_
