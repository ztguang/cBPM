#ifndef __SUBFLOW_EXIT_ACTION_H__
#define __SUBFLOW_EXIT_ACTION_H__

#include "BaseAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Process
			{
				namespace Action
				{
					class SubFlowExitAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction
					{
						public:
						
							SubFlowExitAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel);

							virtual ~SubFlowExitAction();

							virtual int action( String& result );

						protected:

							int evaluateAction();

							String sReturn;
							String parentProcess;
							String sTaskParentProcess;
							int iWorkflowLevel;

							

					};
				}
			}
		}
	}
}

#endif 

