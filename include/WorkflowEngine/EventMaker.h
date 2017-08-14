#ifndef __EVENT_MAKER_H__
#define __EVENT_MAKER_H__

#define TO_BE_EXPORTED

#include "EventListener.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			class EventMaker
			{
    			public:

    				EventMaker( String Name );

					virtual ~EventMaker();

					void addEventListener( EventListener* evl );
					void addEventListeners(EventListenerList& evls);
					EventListenerList& getEventListeners() { return eList;}

					//void throwEvent( BaseEvent& evt );     //ztg delete
					void throwEvent( BaseEvent* evt );

				protected:

				private:

					String _Name;

					EventListenerList eList;
			};
		}
	}
}

#endif



