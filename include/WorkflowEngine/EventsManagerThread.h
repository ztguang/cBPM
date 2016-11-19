#ifndef _EVENTS_MANAGER_THREAD_H_
#define _EVENTS_MANAGER_THREAD_H_

#include "bOS.h"
#include "bOSThread.h"
using namespace bOS::Core;

namespace WorkflowEngine
{
	class EventsManager;

	namespace Criteria
	{
		namespace Core
		{
			class EventsManagerThread : public Thread
			{
			public:
				EventsManagerThread(EventsManager* manager);
				virtual ~EventsManagerThread();

				void run();
				void finalize() {;}
				void terminate() {;}

				void stopEventManager();

			private:
				EventsManager* eventsManager;

				bool bIsAlive;
			};
		}
	}
}

#endif //_EVENTS_MANAGER_THREAD_H_


