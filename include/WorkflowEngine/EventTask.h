#ifndef _EVENT_TASK_H__
#define _EVENT_TASK_H__

#include "BaseTask.h"

#include "FormalParameters.h"
using namespace DataManager::Panorama;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Event
			{
				class EventTask : public WorkflowEngine::Criteria::BasicTask::BaseTask
				{
					public:
					
						EventTask( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, Common::FormalParameters& eventParameters );
					    
						virtual ~EventTask();

						int execute();

				private:
					Common::FormalParameters parametersByOccurredEvent;
				};
			}
		}
	}
}

#endif //_EVENT_TASK_H__


