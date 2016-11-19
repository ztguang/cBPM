#ifndef __STARTING_WORKFLOW_EVENT_H__
#define __STARTING_WORKFLOW_EVENT_H__

#include "BaseWorkflowEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace WorkflowEvent
			{
				class StartingWorkflowEvent : public BaseWorkflowEvent
				{
					public:

						StartingWorkflowEvent( Workflow* wf );
					    
						virtual ~StartingWorkflowEvent();

					private:

						static String  _EventName;
						static int     _EventID;
				};
			}
		}
	}
}

#endif 


