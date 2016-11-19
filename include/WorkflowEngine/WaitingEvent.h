#ifndef _WAITING_EVENT_H_
#define _WAITING_EVENT_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObject.h"

#include "CriteriaCommonDefines.h"

#include "WaitingActivities.h"

#include "Event.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API WaitingEvent : public Event
			{
			public:
				WaitingEvent();
				WaitingEvent( bOS::XML::XMLNode* node);

				virtual ~WaitingEvent();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				WaitingActivities& getActivities();

			private:
				WaitingActivities activities;

			};

			class ENGINE_API XMLWaitingEvent: public XMLEvent
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_WAITING_EVENT_H_