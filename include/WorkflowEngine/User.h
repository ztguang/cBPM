#ifndef _USER_DATAMODEL_H_
#define _USER_DATAMODEL_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSCollectionEntry.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "bOSSQLTable.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowParticipantsData
		{
			class ENGINE_API User :	public bOS::Collections::CollectionEntry, 
										public virtual XMLObject,
										public bOS::SQL::SQLTable
			{
				public:

					User();
					User(const char* acXML);
					User( bOS::XML::XMLNode*);

					virtual ~User();

					//XMLObject
					void init();
					bool init(bOS::XML::XMLNode* node);
					bool init(const char* acXML);
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
					String& getName() { return sName; }
					String&	getDescription() { return sDescription;}
					String& getPassword() { return sPassword;}
					String& getDisplayName() { return sDisplayName;}
					String& getEmail() { return sEmail;}

					void setKey(const String& Value ) { sKey = Value;}
					void setName( const String& Value ) { sName = Value; }
					void setDescription( const String& Value ) { sDescription = Value; }
					void setPassword(const String& Value) { sPassword = Value;}
					void setDisplayName( const String& Value ) { sDisplayName = Value; }
					void setEmail(const String& Value) { sEmail = Value;}

				private:

					String sKey;
					String sName;
					String sDescription;
					String sPassword;
					String sDisplayName;
					String sEmail;
			};

			class ENGINE_API XMLUser
			{
			public:
				static String MAIN_NODE;

				static String KEY_ATTRIBUTE;
				static String NAME_NODE;
				static String DESCRIPTION_NODE;
				static String PASSWORD_NODE;
				static String DISPLAYNAME_NODE;
				static String EMAIL_NODE;
			};

			class ENGINE_API SQLUser
			{
			public:
				static String TABLE_NAME;

				static String KEY_FIELD;
				static String NAME_FIELD;
				static String DESCRIPTION_FIELD;
				static String PASSWORD_FIELD;
				static String DISPLAYNAME_FIELD;
				static String EMAIL_FIELD;
			};
		}
	}
}

#endif //_USER_DATAMODEL_H_

