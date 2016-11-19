#ifndef _EVENTS_H_
#define _EVENTS_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "Event.h"
#include "WaitingEvent.h"
#include "OccurredEvent.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API Events : public bOS::XML::Data::XMLObjectSet
			{
			public:
				Events();
				Events( bOS::XML::XMLNode* node );

				virtual ~Events();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();	

				Event* getEvent(const String& sEventId);

			private:
				
			};

			class ENGINE_API XMLEvents
			{
			public:
				static String MAIN_NODE;

			};
		}
	}
}

#endif //_EVENTS_H_