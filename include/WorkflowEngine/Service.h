#ifndef _SERVICE_H_
#define _SERVICE_H_

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

#include "Roles.h"
#include "Users.h"

#include "ExtendedAttributes.h"

using namespace DataManager::Panorama;

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowServices
		{
			class ENGINE_API Service :	public bOS::Collections::CollectionEntry,
											public virtual XMLObject,
											public bOS::SQL::SQLTable
			{
				public:

					Service();
					Service(const char* acXML);
					Service(bOS::XML::XMLNode*);

					virtual ~Service();

					//XMLObject
					virtual void init();
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

					String& getName() { return sName; }
					String& getDescription() { return sDescription;}
					String& getWorkflowName() { return sWorkflowName; }

					void setName( const String& Value ) { sName = Value; }
					void setDescription( const String& Value ) { sDescription = Value; }
					void setWorkflowName( const String& Value ) { sWorkflowName = Value; }

					WorkflowParticipantsData::Users&	getUsers() { return vUsers;}
					WorkflowParticipantsData::Roles&	getRoles() { return vRoles;}

					Common::ExtendedAttributes& getExtendedAttributes() { return vExtendedAttributes;}

				private:

					String sName;
					String sDescription;
					String sWorkflowName;

					WorkflowParticipantsData::Users vUsers;
					WorkflowParticipantsData::Roles vRoles;

					Common::ExtendedAttributes vExtendedAttributes;

			};

			class ENGINE_API XMLService
			{
			public:
				static String MAIN_NODE;

			private:
				static String NAME_ATTRIBUTE;
				static String WORKFLOW_NODE;
				static String DESCRIPTION_NODE;

				friend class Service;

			};

			class ENGINE_API SQLService
			{
			public:
				static String TABLE_NAME;

			private:
				static String NAME_FIELD;
				static String WORKFLOW_FIELD;
				static String DESCRIPTION_FIELD;

				static String USERS_FIELD;
				static String ROLES_FIELD;
				static String EXTENDEDATTRIBUTES_FIELD;

				friend class Service;
			};
		}
	}
}

#endif //_SERVICE_H_