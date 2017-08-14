#ifndef __PRIMITIVE_TASK_H__
#define __PRIMITIVE_TASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Primitive
			{
				class PrimitiveTask : public WorkflowEngine::Criteria::BasicTask::BaseTask
				{
					public:
					
						PrimitiveTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					    
						virtual ~PrimitiveTask();

						int execute();
				};
			}
		}
	}
}

#endif


