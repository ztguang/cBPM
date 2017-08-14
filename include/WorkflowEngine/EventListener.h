#ifndef __EVENT_LISTENER_H__
#define __EVENT_LISTENER_H__

//TO_BE_EXPORTED

#include "BaseEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			class EventListener
			{
    			public:
			
					EventListener( String Name );
		     
					virtual ~EventListener();
				
					String getName();
				
					//virtual void eventAction( BaseEvent& evt ) = 0;     //ztg delete
					virtual void eventAction( BaseEvent* evt ) = 0;

				protected:
				
				private:

					String  _Name;
			};

			typedef vector<EventListener*> EventListenerList;
		}
	}
}

#endif


