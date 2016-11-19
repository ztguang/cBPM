#ifndef __PROCESS_ACTION_H__
#define __PROCESS_ACTION_H__

#include "BaseAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			class WorkflowManager;
		}

		namespace BasicTask
		{
			namespace Process
			{
				namespace Action
				{
					class ProcessAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction
					{
						public:
						
							ProcessAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, int iLevel );

							virtual ~ProcessAction();

							virtual int action( String& result ) = 0;

						protected:

							virtual int evaluateAction();

							String sProcessName;
							bool bSequence;
							int iOccurency;

							String        iPID;
							int         iWorkflowLevel;

					};
				}
			}
		}
	}
}

#endif 

