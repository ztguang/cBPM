#ifndef _EVENT_INVOCATION_POLICY_H_
#define _EVENT_INVOCATION_POLICY_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSXMLObject.h"
#include "bOSXMLNode.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API EventInvocationPolicy : public bOS::XML::Data::XMLObject
			{
			public:
				EventInvocationPolicy();
				EventInvocationPolicy( bOS::XML::XMLNode* node );

				virtual ~EventInvocationPolicy();

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

			class ENGINE_API XMLEventInvocationPolicy
			{
			public:
				static String MAIN_NODE;
				
				static String TYPE_ATTRIBUTE;

				static String ONDEMAND_TYPE;
				static String TIME_TYPE;
				static String LOOP_TYPE;
				static String DATE_TYPE;
			};
		}
	}
}

#endif //_EVENT_INVOCATION_POLICY_H_