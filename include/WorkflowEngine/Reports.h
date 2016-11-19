#ifndef _REPORTS_H_
#define _REPORTS_H_

//TO_BE_EXPORTED

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLTable.h"

#include "ProcessComponent.h"

#include "Report.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Reports :	public bOS::XML::Data::XMLObjectSet,
											public bOS::SQL::SQLTable,
											public ProcessComponent
			{
			public:

				Reports();
				Reports(bOS::XML::XMLNode* node);
				virtual ~Reports();

				//XMLObject
				void init();
				bool init(bOS::XML::XMLNode* node);
				bool init(const char* acXML);
				bool parse(bOS::XML::XMLAttribute*) {return false;}
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				//SQLTable
				const char* acGetTableName()				{return SQLReport::TABLE_NAME.c_str();}
				void setRecord(bOS::SQL::ResultSetRecord&)	{;}
				String acGetWhere()							{return ProcessComponent::acGetWhere();}
				bool parse(bOS::SQL::ResultSetField*)		{return true;}
				bool parse(bOS::SQL::ResultSetRecord*);
				void addSQLCommands(bOS::SQL::SQLCommands& vCommands, int operation);

				bool haveAutoIncrementField() { return true;}
				void setAutoIncrementField(long ) {;}

				bool addReport(Report& report);

			
			private:

			};

			class ENGINE_API XMLReports
			{
			public:
				static String MAIN_NODE;
			};

			class ENGINE_API SQLReports
			{
			public:
				static String TABLE_NAME;

			private:
				friend class Reports;
			};

		}
	}
}

#endif //_REPORTS_H_