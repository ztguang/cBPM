#ifndef __PROCESS_TASK_H__
#define __PROCESS_TASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Process
			{
				class ProcessTask : public WorkflowEngine::Criteria::BasicTask::BaseTask
				{
					public:
					
						ProcessTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel );

						virtual ~ProcessTask();

						int execute();

					private:

						int iWorkflowLevel;
				};
			}
		}
	}
}

#endif


