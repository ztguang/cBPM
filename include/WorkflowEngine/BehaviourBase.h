#ifndef _BEHAVIOUR_BASE_START_
#define _BEHAVIOUR_BASE_START_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLObject.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "Report.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API BehaviourBase : public XMLObject, public bOS::Collections::CollectionEntry 
			{
				public:
					
					BehaviourBase(String sKey);
					virtual ~BehaviourBase();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid()	{return true;}

					//CollectionEntry
					bool equalTo(bOS::Collections::CollectionEntry*);

					String& getKey() { return sKey;}

					String& getMode() { return sMode;}
					void setMode(const String& Value) { sMode = Value;}

					bool isAutomatic();

					Report& getReport() { return report;}

				protected:
					Report report;
					String sMode;

				private:

					//used for getting BehaviourTag from Collection.
					//Each derived class set sKey to its NAME_ATTRIBUTE;
					String sKey;
			};

			class ENGINE_API XMLBehaviourBase
			{
			public:

			private:
				static String MODE_ATTRIBUTE;

				static String AUTOMATIC_MODE;
				static String MANUAL_MODE;

				friend class BehaviourBase;
			};
		}
	}
}

#endif //_BEHAVIOUR_BASE_START_