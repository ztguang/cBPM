#ifndef __WORKFLOW_LISTENER_H__
#define __WORKFLOW_LISTENER_H__

//TO_BE_EXPORTED

#include "EventListener.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace Listener
			{
				/**
				* This class implements the Workflow default listener.
				* It receives workflow events.
				*
				*/
				class WorkflowListener : public EventListener 
				{
					public:

						WorkflowListener();
			            
						virtual ~WorkflowListener();

						//void eventAction( BaseEvent& evt );     //ztg delete
						void eventAction( BaseEvent* evt );

					private:

						static const String ENGINE_NOTIFY;
						static const String PROCESSINSTANCE;
						static const String STATUS;

				};
			}
		}
	}
}

#endif


