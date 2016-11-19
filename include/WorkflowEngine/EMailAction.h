#ifndef __EMAIL_ACTION_H__
#define __EMAIL_ACTION_H__

#include "BaseAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Mail
			{
				namespace Action
				{
					class EMailAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction 
					{
						public:
						
							EMailAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
							virtual ~EMailAction();

							virtual int action( String& result ) = 0;

						protected:

							virtual int evaluateAction();
					};
				}
			}
		}
	}
}

#endif


