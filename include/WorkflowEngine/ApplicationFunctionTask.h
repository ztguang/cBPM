#ifndef __APPLICATION_FUNCTION_TASK_H__
#define __APPLICATION_FUNCTION_TASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Application
			{
			class ApplicationFunctionTask : public WorkflowEngine::Criteria::BasicTask::BaseTask
			{
				public:
				
					ApplicationFunctionTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
				    
					virtual ~ApplicationFunctionTask();

					int execute();
			};
			}
		}
	}
}

#endif //__APPLICATION_FUNCTION_TASK_H__


