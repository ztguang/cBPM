#ifndef _EVENT_WAITING_ACTIVITY_H_
#define _EVENT_WAITING_ACTIVITY_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObject.h"

#include "bOSDateTime.h"

#include "CriteriaCommonDefines.h"

#include "ManagedEventElement.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API WaitingActivity :	public bOS::XML::Data::XMLObject,
														public bOS::Collections::CollectionEntry 
			{
			public:
				WaitingActivity();
				WaitingActivity( bOS::XML::XMLNode* node );

				virtual ~WaitingActivity();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				//CollectionEntry
				bool equalTo(bOS::Collections::CollectionEntry*);
				
				//
				const char* getProcessId();
				void setProcessId(const char* value);

				String& getActivityName();
				void setActivityName(const String&);

				bOS::Utils::DateTime& getDatetime();
				void setDateTime2Now();
				void setDateTime(const bOS::Utils::DateTime& datetimeValue);

				ManagedEventElement& getManaged();
				void set2Managing();
				void set2Managed();
				bool is2Manage();


			private:
			
				String processId;
				String sActivityName;
				bOS::Utils::DateTime datetime;

				ManagedEventElement managed;

			};

			class ENGINE_API XMLWaitingActivity
			{
			public:
				static String MAIN_NODE;

				static String PROCESSID_ATTRIBUTE;
				static String NAME_ATTRIBUTE;
				static String DATETIME_ATTRIBUTE;
			};
		}
	}
}

#endif //_EVENT_CONTEXT_H_