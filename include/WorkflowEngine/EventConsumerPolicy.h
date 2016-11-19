#ifndef _EVENT_CONSUMER_POLICY_H_
#define _EVENT_CONSUMER_POLICY_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
using namespace bOS::XML;

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API EventConsumerPolicy : public bOS::XML::Data::XMLObject
			{
			public:
				EventConsumerPolicy();
				EventConsumerPolicy( bOS::XML::XMLNode* node );

				virtual ~EventConsumerPolicy();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				void setType(const String&);
				String& getType();

				void setValue(const String&);
				String& getValue();

			private:

				String sType;
				String sValue;

			};

			class ENGINE_API XMLEventConsumerPolicy
			{
			public:
				static String MAIN_NODE;
				
				static String TYPE_ATTRIBUTE;

				static String YES_TYPE;
				static String NO_TYPE;
				static String NUMBER_TYPE;
			};
		}
	}
}

#endif //_EVENT_CONSUMER_POLICY_H_