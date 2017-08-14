#ifndef _BEHAVIOUR_FINISH_H_
#define _BEHAVIOUR_FINISH_H_

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
			class ENGINE_API BehaviourFinish : public BehaviourBase
			{
				public:
					
					BehaviourFinish();
					BehaviourFinish(bOS::XML::XMLNode* node );

					virtual ~BehaviourFinish();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid(){return true;}

				private:

			};

			class ENGINE_API XMLBehaviourFinish
			{
			public:
				static String MAIN_NODE;

			private:

				friend class BehaviourFinish;
			};
		}
	}
}

#endif //_BEHAVIOUR_FINISH_H_