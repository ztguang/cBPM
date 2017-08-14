#ifndef __MAKE_EVENT_ACTION_H__
#define __MAKE_EVENT_ACTION_H__

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
					class MakeEventAction : public EventAction
					{
						public:

							MakeEventAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					        
							virtual ~MakeEventAction();

							virtual int action( String& result );

						protected:
							int evaluateAction();

						private:

					};
				}
			}
		}
	}
}

#endif //__MAKE_EVENT_ACTION_H__



