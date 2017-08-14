#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "BehaviourStart.h"
#include "BehaviourFinish.h"
#include "BehaviourExecution.h"

#include "CriteriaCommonDefines.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class BehaviourBase;

			class ENGINE_API Behaviour : public XMLObjectSet
			{
				public:
					
					Behaviour();
					Behaviour(bOS::XML::XMLNode* node );

					virtual ~Behaviour();

					//XMLObject
					virtual void init();
					bool init(bOS::XML::XMLNode* node);
					bool init(const char* acXML);
					bool parse(bOS::XML::XMLAttribute*);
					bool parse(bOS::XML::XMLNode*);
					bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
					bool isValid() { return true;}

					//tell if BehavoiourExecution Mode is setted to "AUTOMATIC"
					bool isAutomaticExecution();

					//tell if BehaviourStart OnlyOne is setted to "YES"
					bool isToRexecuteStart();

					//set to "NO" BehaviousStart OnlyOne
					void setNotToRexecuteStart();

					//return DataType defined in script tag inside BehaviourExecution
					String getDataType();

					//return Command defined Script Tag inside BehaviourExecution
					String getScriptCommand();

					//return Type defined Script Tag inside BehaviourExecution
					String getScriptType();

					BehaviourStart* getBehaviourStart();
					BehaviourFinish* getBehaviourFinish();
					BehaviourExecution* getBehaviourExecution();


				private:

					BehaviourBase* getBehaviour(String& sKey);

			};

			class ENGINE_API XMLBehaviour
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_BEHAVIOUR_H_