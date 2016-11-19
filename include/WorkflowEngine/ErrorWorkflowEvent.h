#ifndef __ERROR_WORKFLOW_EVENT_H__
#define __ERROR_WORKFLOW_EVENT_H__

#include "BaseWorkflowEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace WorkflowEvent
			{
				class ErrorWorkflowEvent : public BaseWorkflowEvent
				{
					public:
					
						ErrorWorkflowEvent( Workflow* wf );

						virtual ~ErrorWorkflowEvent();

					private:

						static String  _EventName;
						static int     _EventID;
				};
			}
		}
	}
}

#endif


