#ifndef _USERS_DATAMODEL_H_
#define _USERS_DATAMODEL_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "User.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowParticipantsData
		{
			class ENGINE_API Users : public XMLObjectSet
			{
			public:

				Users();
				Users(bOS::XML::XMLNode*);
				virtual ~Users();

				void init();
				bool init(bOS::XML::XMLNode*node);
				//bool init(bOS::IO::File& file);     //ztg delete
				bool init(bOS::IO::File file);

				bool init(const char* acXML);
				bool parse(bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				bool checkUser(const char* acUserKey);
				bool getUser(User* user);
				bool addUser(const char* acUser);
				bool updateUser(const char* acUser);
				bool deleteUser(const char* acUserKey);

			private:

			};

			class ENGINE_API XMLUsers
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_USERS_DATAMODEL_H_
