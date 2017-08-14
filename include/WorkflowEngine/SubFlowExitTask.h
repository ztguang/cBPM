#ifndef __SUBFLOWEXIT_TASK_H__
#define __SUBFLOWEXIT_TASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Process
			{
				class SubFlowExitTask : public BaseTask
				{
					public:
					
						SubFlowExitTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task,int iLevel);
					    
						virtual ~SubFlowExitTask();

						int execute();
						int         iWorkflowLevel;

				protected:
						bool bEndTask;
				};
			}
		}
	}
}

#endif //__SUBFLOWEXIT_TASK_H__


