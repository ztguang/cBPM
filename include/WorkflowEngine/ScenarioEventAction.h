#ifndef _DATAMODEL_EVENT_ACTION_H_
#define _DATAMODEL_EVENT_ACTION_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSCollectionEntry.h"

#include "bOSXMLObject.h"
#include "bOSXMLNode.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowEvents
		{
			class ENGINE_API ScenarioEventAction :	public bOS::XML::Data::XMLObject, 
													public bOS::Collections::CollectionEntry 
			{
			public:

				ScenarioEventAction();
				ScenarioEventAction( bOS::XML::XMLNode* node );

				virtual ~ScenarioEventAction();

				void init();
				bool init (bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) ;
				bool parse(bOS::XML::XMLNode*) ;
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);

				bool isValid();

				//CollectionEntry
				bool equalTo(CollectionEntry*);

				bool isProcessExecuteType();
				void setType(const String&);
				String& getType();

				void setValue(const String&);
				String& getValue();

				void setId(const String&);
				String& getId();

			private:

				String sId;
				String sType;
				String sValue;
			};

			class ENGINE_API XMLScenarioEventAction
			{
			public:
				static String MAIN_NODE;
				
				static String TYPE_ATTRIBUTE;
				static String ID_ATTRIBUTE;

				//
				static String PROCESSEXECUTE_TYPE;

			};

		}
	}
}

#endif //_DATAMODEL_EVENT_ACTION_H_