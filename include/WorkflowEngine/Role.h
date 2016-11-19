#ifndef _ROLE_DATAMODEL_H_
#define _ROLE_DATAMODEL_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLTable.h"

#include "bOSCollectionEntry.h"

#include "CriteriaCommonDefines.h"

#include "Users.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowParticipantsData
		{
			class ENGINE_API Role :	public XMLObject, 
										public bOS::Collections::CollectionEntry,
										public bOS::SQL::SQLTable 
			{
				public:

					Role();
					Role( bOS::XML::XMLNode* node );
					Role(const char* acXML);

					virtual ~Role();

					//XMLObject
					virtual void init();
					bool init(const char* acXML);
					bool init(bOS::XML::XMLNode* node);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid() { return true;}

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
					String& getName() { return sName;}
					String&	getDescription() { return sDescription;}

					Users&  getUsers() { return vUsers;}

					void setKey(const String& Value) { sKey=Value;}
					void setName(const String& Value) { sName=Value;}
					void setDescription(const String& Value) { sDescription = Value;} 
			    
				private:

					String sKey;
					String sDescription;
					String sName;

					Users vUsers;
			};

			class ENGINE_API XMLRole
			{
			public:
				static String MAIN_NODE;

				static String KEY_ATTRIBUTE;
				static String NAME_NODE;;
				static String DESCRIPTION_NODE;
			};

			class ENGINE_API SQLRole
			{
			public:
				static String TABLE_NAME;
				
				static String KEY_FIELD;
				static String NAME_FIELD;
				static String DESCRIPTION_FIELD;

				static String USERS_FIELD;
			};
		}
	}
}

#endif //_ROLE_DATAMODEL_H_
