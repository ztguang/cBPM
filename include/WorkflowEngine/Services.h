#ifndef _SERVICES_H_
#define _SERVICES_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "Service.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowServices
		{
			class ENGINE_API Services : public XMLObjectSet
			{
			public:

				Services();
				Services(bOS::XML::XMLNode*);
				virtual ~Services();

				void init();
				bool init(bOS::XML::XMLNode*node);
				bool init(const char* acXML);
				//bool init(bOS::IO::File& file);     //ztg delete
				bool init(bOS::IO::File file);

				bool parse(bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				bool addService(const char* acService);
				bool deleteService(const char* acServiceName);

			private:

			};

			class ENGINE_API XMLServices
			{
			public:
				static String MAIN_NODE;
			};

			class ENGINE_API SQLServices
			{
			public:
				static String TABLE_NAME;
			};
		}
	}
}

#endif //_SERVICES_H_
