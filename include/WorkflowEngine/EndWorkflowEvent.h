#ifndef __END_WORKFLOW_EVENT_H__
#define __END_WORKFLOW_EVENT_H__

#include "BaseWorkflowEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace WorkflowEvent
			{
				class EndWorkflowEvent : public BaseWorkflowEvent
				{
					public:
					
						EndWorkflowEvent( Workflow* wf );

						virtual ~EndWorkflowEvent();

					private:

						static String  _EventName;
						static int     _EventID;
				};
			}
		}
	}
}

#endif //__END_WORKFLOW_EVENT_H__


