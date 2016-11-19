#ifndef __BASE_EVENT_H__
#define __BASE_EVENT_H__

//TO_BE_EXPORTED

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Event
		{
			class BaseEvent 
			{
				public:

					BaseEvent( String eventName, int eventID );

					virtual ~BaseEvent();

					String getName();

					int getID();

					String getDateTime();

				private:

					String  sName;
					String  sDateTime;
					int     iID;
			};
		}
	}
}

#endif

