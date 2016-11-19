#ifndef _APPLICATIONS_DATAMODEL_H_
#define _APPLICATIONS_DATAMODEL_H_

//TO_BE_EXPORTED
#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObjectSet.h"

#include "Application.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowApplicationsData
		{
			class ENGINE_API Applications : public bOS::XML::Data::XMLObjectSet
			{
			public:
				Applications();
				Applications(bOS::XML::XMLNode* node);
				virtual ~Applications();

				//XMLObjectSet
				void init();
				bool init(bOS::XML::XMLNode*);
				//bool init(bOS::IO::File& file);     //ztg delete
				bool init(bOS::IO::File file);

				bool parse(bOS::XML::XMLAttribute*) {return false;}
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				Application* get(const char* acApplicationName);

			private:

			};

			class ENGINE_API XMLApplications
			{
			public:
				static String MAIN_NODE;

			private:

				friend class Applications;
			};
		}
	}
}

#endif //_APPLICATIONS_DATAMODEL_H_
