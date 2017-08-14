#ifndef _OCCURRED_EVENT_H_
#define _OCCURRED_EVENT_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObject.h"

#include "CriteriaCommonDefines.h"

#include "EventSource.h"
#include "ManagedEventElement.h"
#include "Event.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API OccurredEvent : public Event
			{
			public:
				OccurredEvent();
				OccurredEvent( bOS::XML::XMLNode* node );

				virtual ~OccurredEvent();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				void set2Managing();
				void set2Managed();

				EventSource& getSource();
				ManagedEventElement& getManaged();

			private:
				EventSource source;
				ManagedEventElement managed;

			};

			class ENGINE_API XMLOccurredEvent : public XMLEvent
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_OCCURRED_EVENT_H_