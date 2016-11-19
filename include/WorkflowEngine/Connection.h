#ifndef _DATABASE_CONNECTION_H_
#define _DATABASE_CONNECTION_H_

//TO_BE_EXPORTED

#include "bOS/bOS.h"

#include "bOS/bOSXMLNode.h"
#include "bOS/bOSXMLAttribute.h"
using namespace bOS::XML;

#include "bOS/bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "bOS/bOSCollectionEntry.h"

#include "PoolManager.h"
#include "DataBaseObjectManager.h"
#include "DataBaseObject.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace DataBase
		{
			class ENGINE_API Connection : public XMLObject, bOS::Collections::CollectionEntry 
			{
				public:

					Connection();
					Connection( XMLNode* node );

					virtual ~Connection();

					//XMLObject
					void init();
					bool init(XMLNode* node);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*);

					PoolManager& getPool() { return poolManager;}

					//
					String& getId() { return sId; }
					String& getType() { return sType; }

					void setId( const String& sValue) { sId = sValue; }
					void setType( const String& sValue) { sType = sValue; }

					int getIdType() { return idType;}

					//return true if type tag is setted to PRIMARY
					bool isPrimary();

					bool manageProcessTemplates();
					bool manageProcessInstances();
					bool manageReports();
					bool manageDataTypes();
					bool manageServices();
					bool manageUsers();
					bool manageRoles();
					bool manageApplications();
					bool manageApplicationsDataBase();
					bool manageEvents();
					bool manageOccurredEvents();
					bool manageWaitingEvents();
					bool manageCheckList();
					bool manageForms();

					String getProcessTemplatesValue();
					String getProcessInstancesValue();
					String getDataTypesValue();
					String getServicesValue();
					String getUsersValue();
					String getRolesValue();
					String getApplicationsValue();
					String getEventsValue();
					String getOccurredEventsValue();
					String getWaitingEventsValue();
					String getCheckListValue();
					String getFormsValue();

					DataBaseObject* getObject(String sManaged);

				protected:
					//utilizzato per identificare la classe derivata.
					//un modo per evitare di individuarlo a run-time.
					int idType;

					

				private:

					bool manage(String sManaged);

					String getObjectValue(String sManaged);
					

					String sType;
					String sId;

					PoolManager poolManager;
					DataBaseObjectManager objectManager;
			};

			class ENGINE_API XMLConnection
			{
			public:

			private:
				static String ID_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;

				static String PRIMARY_TYPE;

				friend class Connection;
			};
		}
	}
}

#endif //_DATABASE_CONNECTION_H_