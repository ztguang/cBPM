#ifndef __CONDITION_TASK_H__
#define __CONDITION_TASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Condition
			{
				class ConditionTask : public BaseTask
				{
					public:

						ConditionTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

						virtual ~ConditionTask();

						int execute();
				};
			}
		}
	}
}

#endif //__CONDITION_TASK_H__

