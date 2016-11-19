#ifndef _GRANTS_H_
#define _GRANTS_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace Common
		{
			class ENGINE_API Grants : public XMLObjectSet
			{
				public:
					
					Grants();
					Grants(bOS::XML::XMLNode* node );

					virtual ~Grants();

					//XMLObject
					bool init(const char* acXML);
					bool init(bOS::XML::XMLNode* node);
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid() { return true;}

					bool check(const char* acUserKey, const char* acRoleKey, const char* acGrantType);

				private:

			};

			class ENGINE_API XMLGrants
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif