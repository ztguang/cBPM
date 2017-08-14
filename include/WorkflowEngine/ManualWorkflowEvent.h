#ifndef __MANUAL_WORKFLOW_EVENT_H__
#define __MANUAL_WORKFLOW_EVENT_H__

#include "BaseWorkflowEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace WorkflowEvent
			{
				class ManualWorkflowEvent : public BaseWorkflowEvent
				{
					public:
					
						ManualWorkflowEvent( Workflow* wf );

						virtual ~ManualWorkflowEvent();

					private:

						static String  _EventName;
						static int     _EventID;
				};
			}
		}
	}
}

#endif


