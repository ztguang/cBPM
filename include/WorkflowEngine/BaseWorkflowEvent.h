#ifndef __BASE_WORKFLOW_EVENT_H__
#define __BASE_WORKFLOW_EVENT_H__

#include "BaseEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			class Workflow;
		}
	}
}
using namespace WorkflowEngine::Criteria::Core;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace WorkflowEvent
			{
				class BaseWorkflowEvent : public WorkflowEngine::Criteria::Event::BaseEvent
				{
					public:
					
						BaseWorkflowEvent( Workflow* wf, String eventName, int eventID );

						virtual ~BaseWorkflowEvent();

						const char* getProcessID();

					private:

						Workflow* _WF;
				};
			}
		}
	}
}

#endif 

