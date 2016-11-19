#ifndef _DATABASE_OBJECT_H_
#define _DATABASE_OBJECT_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"
using namespace bOS::XML;

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "bOSCollectionEntry.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace DataBase
		{
			class ENGINE_API DataBaseObject : public XMLObject, bOS::Collections::CollectionEntry 
			{
				public:

					DataBaseObject();
					DataBaseObject( XMLNode* node );

					virtual ~DataBaseObject();

					//XMLObject
					void init();
					bool init(XMLNode* node);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					XMLNode* getXMLNode(unsigned int iHow);
					bool isValid();

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*);

					//
					String& getManaged() { return sManaged; }
					String& getType() { return sType; }
					String& getValue() { return sValue;}
					String& getRepository() { return sRepository;}

					void setManaged( const String& sValue) { sManaged = sValue; }
					void setType( const String& sValue) { sType = sValue; }
					void setValue( const String& _Value) { sValue = _Value;}
					void setRepository( const String& _Value) {sRepository = _Value;}

					bool isManaged();

					bool isFileRepository();

				private:

					String sType;
					String sManaged;
					String sValue;
					String sRepository;
			};

			class ENGINE_API XMLDataBaseObject
			{
			public:
				
				static String MAIN_NODE;

				static String MANAGED_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;
				static String REPOSITORY_ATTRIBUTE;

				static String PROCESSESINSTANCE_TYPE;
				static String PROCESSESTEMPLATE_TYPE;
				static String DATATYPES_TYPE;
				static String SERVICES_TYPE;
				static String USERS_TYPE;
				static String ROLES_TYPE;

				static String APPLICATIONS_TYPE;
				static String APPLICATIONS_DATABASE_TYPE;
				static String EVENTS_TYPE;
				static String OCCURREDEVENTS_TYPE;
				static String WAITINGEVENTS_TYPE;
				static String REPORTS_TYPE;
				static String CHECKLIST_TYPE;
				static String FORMS_TYPE;

				static String NO_MANAGED;
				static String YES_MANAGED;

				static String FILE_REPOSITORY;
				static String FOLDER_REPOSITORY;
			};
		}
	}
}

#endif //_DATABASE_OBJECT_H_
