#ifndef _EVENT_POLICIES_H_
#define _EVENT_POLICIES_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObject.h"

#include "CriteriaCommonDefines.h"

#include "EventConsumerPolicy.h"
#include "EventInvocationPolicy.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API EventPolicies : public bOS::XML::Data::XMLObject
			{
			public:
				EventPolicies();
				EventPolicies( bOS::XML::XMLNode* node );

				virtual ~EventPolicies();
				
				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);

				bool isValid();

			private:

				EventConsumerPolicy consumer;
				EventInvocationPolicy invocation;

			};

			class ENGINE_API XMLEventPolicies
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_EVENT_POLICIES_H_