#ifndef _EVENT_ACTIONS_H_
#define _EVENT_ACTIONS_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringUtils.h"
using namespace bOS::CoreString;

#include "bOSXMLNode.h"

#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "ScenarioEventAction.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API EventActions : public bOS::XML::Data::XMLObjectSet
			{
			public:
				EventActions();
				EventActions(bOS::XML::XMLNode* node);

				virtual ~EventActions();

				//XMLObjectSet
				void init();
				bool init(bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) {return false;}
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

			private:


			};

			class XMLEventActions
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_EVENT_ACTIONS_H_