#ifndef __ITERATION_COUNTER_ACTION_H__
#define __ITERATION_COUNTER_ACTION_H__

#include "IterationAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Iteration
			{
				namespace Action
				{
					class IterationCounterAction : public IterationAction
					{
						public:

							IterationCounterAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					        
							virtual ~IterationCounterAction();

							virtual int action( String& result );
						
						private:

							String _result;

							static const String MAX_LOOPS_ATTRIBUTE;
					};
				}
			}
		}
	}
}

#endif
