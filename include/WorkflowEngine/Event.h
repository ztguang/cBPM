#ifndef _EVENT_DATA_MODEL_EVENT_H_
#define _EVENT_DATA_MODEL_EVENT_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLObject.h"

#include "CriteriaCommonDefines.h"

#include "FormalParameters.h"

#include "EventActions.h"
#include "EventPolicies.h"

using namespace DataManager::Panorama;

#include "bOSCollectionEntry.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API Event : public bOS::XML::Data::XMLObject,
											 public bOS::Collections::CollectionEntry
			{
			public:
				Event();
				Event( bOS::XML::XMLNode* node );

				virtual ~Event();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool init (const char* acXML);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid();

				//CollectionEntry
				bool equalTo(bOS::Collections::CollectionEntry*);

				String& getId();
				void setId(const String&);

				Common::FormalParameters& getParameters();
				EventActions& getActions();
				EventPolicies& getPolicies();

			protected:
				Common::FormalParameters parameters;

				String sId;

				EventActions actions;
				EventPolicies policies;

			};

			class ENGINE_API XMLEvent
			{
			public:
				static String MAIN_NODE;
				
				static String ID_ATTRIBUTE;

			};
		}
	}
}

#endif //_EVENT_H_