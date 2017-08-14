#ifndef __CONSUME_EVENT_ATTACH_H__
#define __CONSUME_EVENT_ATTACH_H__

#include "EventAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Event
			{
				namespace Action
				{
					class ConsumeEventAction : public EventAction
					{
						public:

							ConsumeEventAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, Common::FormalParameters& parametersByOccurredEvent );
					        
							virtual ~ConsumeEventAction();

							virtual int action( String& result );

						protected:

							int evaluateAction();

						private:

							Common::FormalParameters parametersEvent;

					};
				}
			}
		}
	}
}

#endif //__CONSUME_EVENT_ATTACH_H__



