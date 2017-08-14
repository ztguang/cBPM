#ifndef _EVENT_CONTEXT_H_
#define _EVENT_CONTEXT_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObjectSet.h"

#include "CriteriaCommonDefines.h"

#include "Events.h"

#include "bOSCollectionEntry.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API EventContext : public bOS::XML::Data::XMLObjectSet,
													public bOS::Collections::CollectionEntry 
			{
			public:
				EventContext();
				EventContext( bOS::XML::XMLNode* node );

				virtual ~EventContext();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				//CollectionEntry
				bool equalTo(bOS::Collections::CollectionEntry*);
				
				//
				String& getName();
				void setName(const String&);

				//
				Event* getEvent(const String& sEventId);

			private:
			
				String sName;
				
				Events events;

			};

			class XMLEventContext
			{
			public:
				static String MAIN_NODE;
				
				static String NAME_ATTRIBUTE;
				

			};

		}
	}
}

#endif //_EVENT_CONTEXT_H_