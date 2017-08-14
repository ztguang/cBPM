#ifndef _BEHAVIOUR_START_
#define _BEHAVIOUR_START_

//TO_BE_EXPORTED

#include "bOS.h"

#include "CriteriaCommonDefines.h"

#include "BehaviourBase.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API BehaviourStart : public BehaviourBase
			{
				public:
					
					BehaviourStart();
					BehaviourStart(bOS::XML::XMLNode* node );

					virtual ~BehaviourStart();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid(){return true;}

					bool isToRexecute();

					void setOnlyOne() { bOnlyOne = true;};
					void setNoOnlyOne() { bOnlyOne = false;}

				private:

					bool bOnlyOne;

			};

			class ENGINE_API XMLBehaviourStart
			{
			public:
				static String MAIN_NODE;

			private:

				static String ONLYONE_ATTRIBUTE;

				static String YES_ONLYONE;
				static String NO_ONLYONE;

				friend class BehaviourStart;
			};
		}
	}
}

#endif //_BEHAVIOUR_START_