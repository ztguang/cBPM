#ifndef _BEHAVIOUR_EXECUTION_H_
#define _BEHAVIOUR_EXECUTION_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "CriteriaCommonDefines.h"

#include "BehaviourBase.h"

#include "Script.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API BehaviourExecution : public BehaviourBase
			{
				public:
					
					BehaviourExecution();
					BehaviourExecution(bOS::XML::XMLNode* node );

					virtual ~BehaviourExecution();

					//XMLObject
					virtual void init();
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid(){return true;}

					void setType(const String& Value) { sType = Value;}
					String& getType() { return sType;}

					Script& getScript() { return script;}

				private:

					String sType;
					Script script;

			};

			class ENGINE_API XMLBehaviourExecution
			{
			public:
				static String MAIN_NODE;

			private:

				static String TYPE_ATTRIBUTE;

				static String ROUTE_TYPE;
				static String IMPLEMENTATION_TYPE;
				static String BLOCKACTIVITY_TYPE;

				friend class BehaviourExecution;
			};
		}
	}
}

#endif //_BEHAVIOUR_EXECUTION_H_