#ifndef _TRANSITIONS_H_
#define _TRANSITIONS_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "Transition.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Transitions : public XMLObjectSet
			{
			public:
				Transitions();
				Transitions(bOS::XML::XMLNode* node );
				virtual ~Transitions();

				//XMLObject
				virtual void init();
				bool init(bOS::XML::XMLNode*node);
				bool init(const char* acXML);
				bool parse(bOS::XML::XMLAttribute*);
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() { return true;}

				void addTransitions(Transitions& vTransitions);

			private:

			};

			class ENGINE_API XMLTransitions
			{
			public:
				static String MAIN_NODE;
			};
		}
	}
}

#endif //_TRANSITIONS_H_
