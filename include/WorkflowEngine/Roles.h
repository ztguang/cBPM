#ifndef _ROLES_DATAMODEL_H_
#define _ROLES_DATAMODEL_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "Role.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowParticipantsData
		{
			class ENGINE_API Roles : public bOS::XML::Data::XMLObjectSet
			{
			public:
				Roles();
				Roles(bOS::XML::XMLNode* node);
				virtual ~Roles();

				//XMLObject
				virtual void init();
				bool init(bOS::XML::XMLNode* node);
				//bool init(bOS::IO::File& file);     //ztg delete
				bool init(bOS::IO::File file);

				bool init(const char* acXML);
				bool parse(bOS::XML::XMLAttribute*);
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				bool checkRole(const char* acRoleKey);
				bool checkRoles(Roles* roles);
				bool getRolesByUser(const char* acUser, Roles* roles);
				bool getRole(Role*);
				bool addRole(const char* acRole);
				bool updateRole(const char* acRole);
				bool deleteRole(const char* acRoleKey);

			private:

			};

			class ENGINE_API XMLRoles
			{
			public:
				static String MAIN_NODE;
			};

		}
	}
}


#endif //_ROLES_DATAMODEL_H_
