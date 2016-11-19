#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSCollectionEntry.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "DataTypeValues.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLTable.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowDataTypes
		{
			class ENGINE_API DataType :	public bOS::Collections::CollectionEntry,
											public virtual XMLObject,
											public bOS::SQL::SQLTable 
			{
				public:

					DataType();
					DataType(const char* acXML);
					DataType( bOS::XML::XMLNode*);

					virtual ~DataType();

					//XMLObject
					void init();
					bool init(bOS::XML::XMLNode*);
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

					bool haveAutoIncrementField() { return true;}
					void setAutoIncrementField(long ) {;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*);

					String& getKey() { return sKey;}
					String& getType() { return sType; }
					String&	getDescription() { return sDescription;}

					void setKey(const String& Value ) { sKey = Value;}
					void setType( const String& Value ) { sType = Value; }
					void setDescription( const String& Value ) { sDescription = Value; }

					DataTypeValues& getDataTypeValues() { return vValues;}

				private:

					String sKey;
					String sType;
					String sDescription;
					
					DataTypeValues vValues;

			};

			class ENGINE_API XMLDataType
			{
			public:
				static String MAIN_NODE;

				static String KEY_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;
				static String DESCRIPTION_NODE;

				friend class DataType;
			};

			class ENGINE_API SQLDataType
			{
			public:
				static String TABLE_NAME;

				static String KEY_FIELD;
				static String TYPE_FIELD;
				static String DESCRIPTION_FIELD;

				static String VALUES_FIELD;
			};
		}
	}
}

#endif //_DATA_TYPE_H_

