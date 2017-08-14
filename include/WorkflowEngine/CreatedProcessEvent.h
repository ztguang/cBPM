#ifndef __CREATED_PROCESS_EVENT_H__
#define __CREATED_PROCESS_EVENT_H__

#include "BaseProcessEvent.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			namespace ProcessEvent
			{
				class CreatedProcessEvent : public BaseProcessEvent
				{
					public:
					
						CreatedProcessEvent( const char* pID );
				        
						CreatedProcessEvent( WorkflowProcesses::WorkflowProcess* p );
				    	
						virtual ~CreatedProcessEvent();

					private:

						static String  _EventName;
						static int     _EventID;
				};
			}
		}
	}
}

#endif 


