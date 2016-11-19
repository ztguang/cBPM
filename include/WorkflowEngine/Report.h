#ifndef _REPORT_H_
#define _REPORT_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObject.h"

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSSQLTable.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "ProcessComponent.h"

#include "CriteriaCommonDefines.h"

#include "bOSCollectionEntry.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Report :	public bOS::XML::Data::XMLObject,
											public bOS::Collections::CollectionEntry,
											public bOS::SQL::SQLTable,
											public ProcessComponent
			{
				public:

					Report();
					Report(bOS::XML::XMLNode* node);

					virtual ~Report();

					//XMLObject
					void init();
					bool init(bOS::XML::XMLNode*node);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//SQLTable
					const char* acGetTableName();
					void setRecord(bOS::SQL::ResultSetRecord&);
					String acGetWhere();
					bool parse(bOS::SQL::ResultSetField*);
					bool parse(bOS::SQL::ResultSetRecord*);

					bool haveAutoIncrementField() { return false;}
					void setAutoIncrementField(long ) {;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*) { return false;}

					String&  getValue() { return sValue;}
					String&  getDateTime() { return sDateTime;}

					void setValue(const String& Value) { sValue = Value;}
					void setDateTime(const String& Value) { sDateTime = Value;}

				private:
					String		sValue;
					String      sDateTime;
			};

			class ENGINE_API XMLReport
			{
			public:
				static String MAIN_NODE;

				static String DATETIME_ATTRIBUTE;

				static String DATE_TIME_VARIABLE;
				static String PROCESS_ID_VARIABLE;
			    static String WORKFLOW_NAME_VARIABLE;
			    static String ACTIVITY_NAME_VARIABLE;
				static String WORKFLOW_LEVEL_VARIABLE;
			};

			class ENGINE_API SQLReport
			{
			public:
				static String TABLE_NAME;

				static String DATETIME_FIELD;
				static String DESCRIPTION_FIELD;
			};
		}
	}
}

#endif //_REPORT_H_