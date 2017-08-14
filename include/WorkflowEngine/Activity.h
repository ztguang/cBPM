#ifndef _ACTIVITY_H_
#define _ACTIVITY_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObject.h"

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "CriteriaCommonDefines.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLTable.h"

#include "ActivityComponent.h"

#include "bOSCollectionEntry.h"

#include "Attributes.h"
using namespace DataManager::Panorama::WorkflowRelevantData;

#include "Reports.h"
#include "Behaviour.h"
#include "Logs.h"
#include "Grants.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Activity :	public bOS::XML::Data::XMLObject,
											public bOS::Collections::CollectionEntry,
											public bOS::SQL::SQLTable,
											public DataManager::Panorama::WorkflowProcesses::ActivityComponent
			{
				public:

					enum ActivityType
					{
						NONE,
						START,
						END,
						SUBFLOW,
						API,
						CONDITION,
						ITERATION,
						EMAIL,
						APPLICATION,
						XML,
						EXIT,
						EVENT,
						THROWER,
						CATCHER
					};

					enum CatchType
					{
						NEVER,
						EVER,
						ONLY_ONE
					};

					Activity();
					Activity(bOS::XML::XMLNode* node);
				
					virtual ~Activity();

					//XMLObject
					void init();
					bool init(bOS::XML::XMLNode* node);
					bool init(const char* acXML);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid() {return true;}

					//SQLTable
					const char* acGetTableName();
					void setRecord(bOS::SQL::ResultSetRecord&);
					String acGetWhere();
					bool parse(bOS::SQL::ResultSetField*);
					bool parse(bOS::SQL::ResultSetRecord*);
					bOS::SQL::SQLTablesList getSQLTables();

					bool haveAutoIncrementField() { return false;}
					void setAutoIncrementField(long ) {;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*);

					//Attributi strutturati
					Attributes&	getAttributes(); 
					Behaviour&	getBehaviour()	{ return behaviour;}
					Reports&	getReports()	{ return vReports;}
					Logs&		getLogs()		{ return vLogs;}
					Log&		getLog()		{ return log;}
					DataManager::Panorama::Common::Grants&	getGrants()		{ return vGrants;}

					void setNrExecuted(int iValue) { iNrExecuted = iValue;}
					int getNrExecuted() { return iNrExecuted;}

					String& getOwner() { return log.getUserKey();}
					void setOwner(const String& Value);

					//Attributi semplice
					int         getType()			{ return iType;}
					String&     getStatus()			{ return log.getStatus();}
					String&     getResult()			{ return log.getResult();}
					String&		getReferenceActivity()	{ return sReferenceActivity;}
					CatchType	getCatchType()		{ return catchType;}
					String&		getActivityName()	{ return sName;}

					void setName(const char* );
					void setResult(const String& sValue);

					//Status methods
					///////////////////////////////////////////////////////////////////////
					void setCreated();
					void setQueued();
					void setRunning();
					void setCompleted();
					void setError();
					void setManual();
					void setWaitingForEvent();

					bool isCreated();
					bool isQueued();
					bool isRunning();
					bool isCompleted();
					bool isError();
					bool isManual();	
					bool isWaitingForEvent();
					///////////////////////////////////////////////////////////////////////

					bool isAutomatic();
					bool isToRexecute();
					void setNotToRexecute();
					bool isStartType();
					bool isEndType();
					bool isExitType();

					bool isCatcherType();

					bool isAlreadyExecuted();

					void setProcessId(const char* _ProcessId);
					void setActivityId(const char* acId);

				private:

					void setStatus(const String& Value);

					//
					ActivityType	iType;
					String	sDescription;
					String sName;

					//Used from Special Activity.
					String    sReferenceActivity;
					CatchType catchType;

					//tells for Catch Task(Sync) how many times Task must to be executed for.
					int iNrExecuted;

					//Attributi strutturati
					Behaviour	behaviour;
					Reports		vReports;
					Attributes	vAttributes;
					Logs		vLogs;
					Log			log;
					DataManager::Panorama::Common::Grants vGrants;

			};

			class ENGINE_API XMLActivity
			{
			public:
				static String MAIN_NODE;

				static String CREATED_STATUS;
				static String QUEUED_STATUS;
				static String RUNNING_STATUS;
				static String COMPLETED_STATUS;
				static String ERROR_STATUS;
				static String MANUAL_STATUS;
				static String WAITINGFOR_STATUS;

				//Special Attribute
				static String MARKER_FEATURE;
				static String MARKER_NOTIFY_FEATURE;	//a special attribute used in getWorkItemListByNotify
				static String MARKER_ASSIGN_TO;			//if presente assign actvity to user setted in.

				//Subflow
				static String MARKER_OCCURENCY;
				static String MARKER_PROCESSNAME;
				static String MARKER_EXECUTION;

				static String MARKER_SEQUENCE_EXECUTION;

			private:
				static String ID_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;
				static String NAME_ATTRIBUTE;

				static String DESCRIPTION_NODE;
				static String REFERENCE_ACTIVITY_NODE;
				static String CATCH_TYPE_NODE;
				static String NR_EXECUTED_NODE;

				static String START_TYPE;
				static String END_TYPE;
				static String SUBFLOW_TYPE;
				static String API_TYPE;
				static String CONDITION_TYPE;
				static String ITERATION_TYPE;
				static String EMAIL_TYPE;
				static String APPLICATION_TYPE;
				static String XML_TYPE;
				static String EXIT_TYPE;
				static String EVENT_TYPE;
				static String THROWER_TYPE;
				static String CATCHER_TYPE;

				static String NEVER_CATCH_TYPE;
				static String EVER_CATCH_TYPE;
				static String ONLY_ONE_CATCH_TYPE;



				friend class Activity;
			};

			class ENGINE_API SQLActivity
			{
			public:
				static String TABLE_NAME;

				static String TYPE_FIELD;
				static String DESCRIPTION_FIELD;
				static String REFERENCE_ACTIVITY_FIELD;
				static String NAME_FIELD;
				static String STATUS_FIELD;
				static String OWNER_FIELD;

				static String CATCH_TYPE_FIELD;
				static String NR_EXECUTED_FIELD;

				static String GRANTS_FIELD;
				static String BEHAVIOUR_FIELD;
				static String LOG_FIELD;
				static String LOGS_FIELD;
				static String REPORTS_FIELD;

			};
		}
	}
}



#endif //_TASK_H_