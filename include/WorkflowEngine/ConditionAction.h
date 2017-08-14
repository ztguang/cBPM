#ifndef __CONDITION_ACTION_H__
#define __CONDITION_ACTION_H__

#include "BaseAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Condition
			{
				namespace Action
				{
				
				class ConditionAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction
				{
					public:
					
						ConditionAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

						virtual ~ConditionAction();

						virtual int action( String& result ) = 0;

					protected:

						virtual int evaluateAction();
						WorkflowRelevantData::Attribute*      attribResult;
				};
				}
			}
		}
	}
}

#endif







