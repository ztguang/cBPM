#ifndef __ITERATION_ACTION_H__
#define __ITERATION_ACTION_H__

#include "BaseAction.h"

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
					class IterationAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction
					{
						public:
						
							IterationAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

							virtual ~IterationAction();

							virtual int action( String& result ) = 0;

						protected:

							virtual int evaluateAction();

							static const String LOOP_STEP_ATTRIBUTE;
							static const String LOOP_START_ATTRIBUTE;

					};
				}
			}
		}
	}
}

#endif 




