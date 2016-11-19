#ifndef __LOOP_TASK_H__
#define __LOOP_TASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Iteration
			{
				class LoopTask : public WorkflowEngine::Criteria::BasicTask::BaseTask
				{
					public:
					
						LoopTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					    
						virtual ~LoopTask();

						int execute();
				};
			}
		}
	}
}

#endif


