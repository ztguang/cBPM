#ifndef _EVENT_SOURCE_H_
#define _EVENT_SOURCE_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObject.h"

#include "bOSDateTime.h"
using namespace bOS::Utils;

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API EventSource : public bOS::XML::Data::XMLObject
			{
			public:

				enum SourceType
				{
					Workflow,
					User,
					System
				};

				EventSource();
				EventSource( bOS::XML::XMLNode* node );

				virtual ~EventSource();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				void setType(const String& sTypeValue);
				void setType(SourceType typeValue);
				String& getType();

				void setName(const String& sNameValue);
				String& getName();

				void setDateTime2Now();
				void setDateTime(const String& DateTimeValue);
				DateTime& getDateTime();

			private:
				String sType;
				String sName;

				bOS::Utils::DateTime datetime;
			};

			class ENGINE_API XMLEventSource
			{
			public:
				static String MAIN_NODE;

				static String TYPE_ATTRIBUTE;
				static String NAME_ATTRIBUTE;
				static String DATETIME_ATTRIBUTE;

				static String WORKFLOW_TYPE;
				static String USER_TYPE;
				static String SYSTEM_TYPE;
			};

		}
	}
}

#endif //_EVENT_SOURCE_H_