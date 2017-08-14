#ifndef _TASK_LOGS_H_
#define _TASK_LOGS_H_

//TO_BE_EXPORTED

#include "bOSXMLNode.h"
#include "bOSXMLAttribute.h"

#include "bOSXMLObjectSet.h"
using namespace bOS::XML::Data;

#include "CriteriaCommonDefines.h"

#include "Log.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API Logs : public XMLObjectSet
			{
			public:
				Logs();
				Logs(bOS::XML::XMLNode* node);
				virtual ~Logs();

				//XMLObjectSet
				virtual void init();
				bool init(bOS::XML::XMLNode* node);
				bool init(const char* acXML);
				bool parse(bOS::XML::XMLAttribute*);
				bool parse(bOS::XML::XMLNode*);
				bOS::XML::XMLNode* getXMLNode(unsigned int iHow);
				bool isValid() {return true;}

				void add( Log& log);

				bool checkStatus(const char* acStatus);

			private:

			};

			class ENGINE_API XMLLogs
			{
			public:
				static String MAIN_NODE;
			};

		}
	}
}

#endif 
