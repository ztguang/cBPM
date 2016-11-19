#ifndef _ACTIVITIES_H_
#define _ACTIVITIES_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLTable.h"

#include "ActivityComponent.h"

#include "Activity.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			typedef vector<String> ActivitiesList;

			class ENGINE_API Activities :public bOS::XML::Data::XMLObjectSet,
											public bOS::SQL::SQLTable,
											public DataManager::Panorama::WorkflowProcesses::ProcessComponent
			{
			public:
				Activities();
				Activities(bOS::XML::XMLNode* node);
				virtual ~Activities();

				//XMLObjectSet
				void init();
				bool init(bOS::XML::XMLNode*);
				bool init(const char* acXML);
				bool parse(bOS::XML::XMLAttribute*) {return false;}
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				bool haveAutoIncrementField() { return false;}
				void setAutoIncrementField(long ) {;}

				//SQLTable
				const char* acGetTableName()				{return SQLActivity::TABLE_NAME.c_str();}
				void setRecord(bOS::SQL::ResultSetRecord&)	{;}
				String acGetWhere()							{return ProcessComponent::acGetWhere();}
				bool parse(bOS::SQL::ResultSetField*)		{return true;}
				bool parse(bOS::SQL::ResultSetRecord*);
				void addSQLCommands(bOS::SQL::SQLCommands& vCommands, int operation);

				Activity* get(String&);
				bool remove(String& _Name);

				Activity* getStartActivity();
				Activity* getActivity(Activity::ActivityType);
				ActivitiesList getActivities(String sStatus, String sOwner);

				void addActivities(Activities&);
				void addActivity(Activity&);

				void setProcessId(const char* _ProcessId);

			private:
			};

			class ENGINE_API XMLActivities
			{
			public:
				static String MAIN_NODE;
			};

			class ENGINE_API SQLActivities
			{
			public:
				static String TABLE_NAME;

				friend class Activity;
			};
		}
	}
}

#endif
