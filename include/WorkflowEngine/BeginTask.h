#ifndef __BEGIN_TASK_H__
#define __BEGIN_TASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			class BeginTask : public BaseTask
			{
				public:

					BeginTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

					virtual ~BeginTask();

					int execute();
			};
		}
	}
}

#endif

