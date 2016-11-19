#ifndef __XMLTASK_H__
#define __XMLTASK_H__

#include "BaseTask.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace XML
			{
				class XMLTask : public WorkflowEngine::Criteria::BasicTask::BaseTask
				{
					public:
					
						XMLTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					    
						virtual ~XMLTask();

						int execute();
				};
			}
		}
	}
}

#endif //__XMLTASK_H__


