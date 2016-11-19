#ifndef _EVENT_WAITING_ACTIVITIES_H_
#define _EVENT_WAITING_ACTIVITIES_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "WaitingActivity.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API WaitingActivities : public bOS::XML::Data::XMLObjectSet
			{
			public:
				WaitingActivities();
				WaitingActivities( bOS::XML::XMLNode* node );

				virtual ~WaitingActivities();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

			private:

			};

			class ENGINE_API XMLWaitingActivities
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_EVENT_WAITING_ACTIVITIES_H_