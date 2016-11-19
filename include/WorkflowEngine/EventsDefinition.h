#ifndef _EVENTS_DEFINITION_H_
#define _EVENTS_DEFINITION_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "Event.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API EventsDefinition : public bOS::XML::Data::XMLObjectSet
			{
			public:

				EventsDefinition();
				EventsDefinition( bOS::XML::XMLNode* node );

				virtual ~EventsDefinition();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();	

				Event* getEvent(const String& sEventId);

			private:
			

			};

			class ENGINE_API XMLEventsDefinition
			{
			public:
				static String MAIN_NODE;

			};
		}
	}
}

#endif //_EVENTS_DEFINITION_H_