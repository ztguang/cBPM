#ifndef _APPLICATION_FUNCTIONS_DATAMODEL_H_
#define _APPLICATION_FUNCTIONS_DATAMODEL_H_

//TO_BE_EXPORTED
#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObjectSet.h"

#include "ApplicationFunction.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowApplicationsData
		{
			class ENGINE_API ApplicationFunctions : public bOS::XML::Data::XMLObjectSet 
			{
			public:
				ApplicationFunctions();
				ApplicationFunctions(bOS::XML::XMLNode* node);
				virtual ~ApplicationFunctions();

				//XMLObjectSet
				void init();
				bool init(bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) {return false;}
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				ApplicationFunction* get(const char* acFunctionName);

			private:

			};

			class ENGINE_API XMLApplicationFunctions
			{
			public:
				static String MAIN_NODE;

			private:
				friend class ApplicationFunctions;
			};
		}
	}
}


#endif //_APPLICATION_FUNCTIONS_DATAMODEL_H_