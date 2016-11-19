#ifndef _WRD_ATTRIBUTES_H_
#define _WRD_ATTRIBUTES_H_

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

#include "Attribute.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowRelevantData
		{
			class ENGINE_API Attributes :	public bOS::XML::Data::XMLObjectSet,
												public bOS::SQL::SQLTable,
												public DataManager::Panorama::WorkflowProcesses::ActivityComponent
			{
			public:
				Attributes();
				Attributes(bOS::XML::XMLNode* node);
				virtual ~Attributes();

				//XMLObjectSet
				void init();
				bool init(bOS::XML::XMLNode*);
				bool init(const char* acXML);
				bool parse(bOS::XML::XMLAttribute*) {return false;}
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				//SQLTable
				const char* acGetTableName()				{return SQLAttribute::TABLE_NAME.c_str();}
				void setRecord(bOS::SQL::ResultSetRecord&)	{;}
				String acGetWhere()							{return ActivityComponent::acGetWhere();}
				bool parse(bOS::SQL::ResultSetField*)		{return true;}
				bool parse(bOS::SQL::ResultSetRecord*);
				void addSQLCommands(bOS::SQL::SQLCommands& vCommands, int operation);

				bool haveAutoIncrementField() { return false;}
				void setAutoIncrementField(long ) {;}

				Attribute* get(const char*);
				Attribute* add(Attribute&);
				void updateAttributes(Attributes& );
				void add(Attribute*);
				void add(Attributes&);
				Attribute* add(const char* acName, const char* acType);
				void assign(Attributes&);

				bool remove(const char*);

				void setProcessId(const char* _ProcessId);
				void setActivityId(const char* acId);


			private:

			};

			class XMLAttributes
			{
			public:
				static String MAIN_NODE;
			};


		}
	}
}

#endif //_VARIABLES_H_
