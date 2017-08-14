#ifndef __XMLACTION_H__
#define __XMLACTION_H__

#include "BaseAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace XML
			{
				namespace Action
				{
					class XMLAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction
				{
					public:
					
						XMLAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

						virtual ~XMLAction();

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


