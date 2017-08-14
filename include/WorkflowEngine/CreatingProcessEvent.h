#ifndef __CREATING_PROCESS_EVENT_H__
#define __CREATING_PROCESS_EVENT_H__

#include "BaseProcessEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace ProcessEvent
			{
				class CreatingProcessEvent : public BaseProcessEvent
				{
					public:

						CreatingProcessEvent( const char* pID );
				        
						CreatingProcessEvent( WorkflowProcesses::WorkflowProcess* p );
				    	
						virtual ~CreatingProcessEvent();

					private:

						static String  _EventName;
						static int     _EventID;
				};
			}
		}
	}
}

#endif 


