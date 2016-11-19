#ifndef _GRANT_H_
#define _GRANT_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "Roles.h"
#include "Users.h"
using namespace DataManager::Panorama::WorkflowParticipantsData;

namespace DataManager
{
	namespace Panorama
	{
		namespace Common
		{
			class ENGINE_API Grant : public bOS::Collections::CollectionEntry, public XMLObject
			{
				public:
					
					Grant();
					Grant( bOS::XML::XMLNode* node );

					virtual ~Grant();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid(){return true;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*) {return false;}


					//Attributi strutturati
					Users&	getUsers() { return vUsers;}
					Roles&	getRoles() { return vRoles;}

					void setUsers(Users& Value);
					void setRoles(Roles& Value);

					bool isEnabled() { return bEnabled;}
					void setEnabled(bool bValue) { bEnabled=bValue;}

					String& getType() { return sType;}
					void setType(const String& sValue) { sType=sValue;}

				private:

					bool bEnabled;
					String sType;

					//Attributi strutturati
					Users vUsers;
					Roles vRoles;

			};

			class ENGINE_API XMLGrant
			{
			public:
				static String MAIN_NODE;

				static String ENABLED_ATTRIBUTE;
				static String TYPE_ATTRIBUTE;

				static String YES_ENABLED;
				static String NO_ENABLED;

				static String EXECUTION_TYPE;
				static String VISIBLE_TYPE;

				friend class Grant;
			};
		}
	}
}

#endif //_GRANT_H_