#ifndef __STARTED_WORKFLOW_EVENT_H__
#define __STARTED_WORKFLOW_EVENT_H__

#include "BaseWorkflowEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace WorkflowEvent
			{
				class StartedWorkflowEvent : public BaseWorkflowEvent 
				{
					public:

						StartedWorkflowEvent( Workflow* wf );
					    
						virtual ~StartedWorkflowEvent();

					private:

						static String  _EventName;
						static int     _EventID;
				};
			}
		}
	}
}

#endif //__STARTED_WORKFLOW_EVENT_H__


