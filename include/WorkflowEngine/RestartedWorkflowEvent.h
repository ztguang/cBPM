#ifndef __RESTARTED_WORKFLOW_EVENT_H__
#define __RESTARTED_WORKFLOW_EVENT_H__

#include "BaseWorkflowEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace WorkflowEvent
			{
				class RestartedWorkflowEvent : public BaseWorkflowEvent 
				{
					public:

						RestartedWorkflowEvent( Workflow* wf );
					    
						virtual ~RestartedWorkflowEvent();

					private:

						static String  _EventName;
						static int     _EventID;
				};
			}
		}
	}
}

#endif 


