#ifndef __EVENT_ACTION_H__
#define __EVENT_ACTION_H__

#include "BaseAction.h"

#include "Event.h"
#include "OccurredEvent.h"
#include "WaitingEvent.h"
using namespace DataManager::Panorama;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Event
			{
				namespace Action
				{
					class EventAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction
					{
						public:
						
							EventAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

							virtual ~EventAction();

							virtual int action( String& result ) = 0;

						protected:

							virtual int evaluateAction();

							WorkflowEvents::Event* event;

					};
				}
			}
		}
	}
}

#endif //__EVENT_ACTION_H__


