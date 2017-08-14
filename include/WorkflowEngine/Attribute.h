#ifndef _WRD_ATTRIBUTE_H_
#define _WRD_ATTRIBUTE_H_

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

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowRelevantData
		{
			class ENGINE_API Attribute :	public bOS::XML::Data::XMLObject,
											public bOS::Collections::CollectionEntry,
											public bOS::SQL::SQLTable,
											public DataManager::Panorama::WorkflowProcesses::ActivityComponent
			{
				public:

					Attribute();
					Attribute(bOS::XML::XMLNode* node);
					Attribute(const String& name, const String& sType);
					Attribute(Attribute*);

					virtual ~Attribute();

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
					bool equalTo(bOS::Collections::CollectionEntry*);

					//
					String& getName()			{ return sName;}
					String& getValue()			{ return sValue;}
					String& getDirection()		{ return sDirection;}
					String& getType()			{ return sType;}

					void setName(const String& Value )	{ sName= Value;}
					void setValue(const String& Value ) { sValue= Value;}
					void setValue(int Value )			{ sValue=StringUtils::toString(Value);}
					void setDirection(const String& Value)	{sDirection=Value;}
					void setType(const String& Value) { sType = Value;}


					void setAlreadyCreated()	{ bAlreadyCreated=true;}
					bool isAlreadyCreated()		{ return bAlreadyCreated;}

				private:

					String		sName;
					String		sValue;
					String		sType;
					String		sDirection;

					bool bAlreadyCreated;
			};

			class ENGINE_API XMLAttribute
			{
			public:
				static String MAIN_NODE;

				static String NAME_ATTRIBUTE;
				static String DIRECTION_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;

				static String VALUE_NODE;

				static String DIRECTION_NONE;
				static String DIRECTION_INPUT;
				static String DIRECTION_OUTPUT;
				static String DIRECTION_INPUTOUTPUT;
				static String DIRECTION_CONSTANT;
				static String DIRECTION_TASK;
				static String DIRECTION_NOTMIGRATE;

				//Add here Criteria DataTypes
				static String XML_TYPE;
				static String STRING_TYPE;
				static String NUMBER_TYPE;
			};

			class ENGINE_API SQLAttribute
			{
			public:
				static String TABLE_NAME;


				static String NAME_FIELD;
				static String DIRECTION_FIELD;
				static String TYPE_FIELD;
				static String VALUE_FIELD;

				friend class Attribute;
				friend class Attributes;
			};
		}
	}
}

#endif //_WRD_ATTRIBUTE_H_
