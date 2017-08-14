#ifndef __BASE_PROCESS_EVENT_H__
#define __BASE_PROCESS_EVENT_H__

#include "BaseEvent.h"

#include "WorkflowProcess.h"
using namespace DataManager::Panorama;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace ProcessEvent
			{
				class BaseProcessEvent : public WorkflowEngine::Criteria::Event::BaseEvent
				{
					public:
					
						BaseProcessEvent( WorkflowProcesses::WorkflowProcess* p, String eventName, int eventID );

						BaseProcessEvent( const char* pID, String eventName, int eventID );

						virtual ~BaseProcessEvent();

						const char* getProcessID();

					private:

						WorkflowProcesses::WorkflowProcess* process;

						String processID;
				};
			}
		}
	}
}

#endif//__BASE_PROCESS_EVENT_H__

