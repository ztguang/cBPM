#ifndef __EMAIL_TASK_H__
#define __EMAIL_TASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Mail
			{
				class EMailTask : public WorkflowEngine::Criteria::BasicTask::BaseTask
				{
					public:
					
						EMailTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					    
						virtual ~EMailTask();

						int execute();
				};
			}
		}
	}
}

#endif


