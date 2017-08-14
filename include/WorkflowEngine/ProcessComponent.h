#ifndef _PROCESS_COMPONENT_H_
#define _PROCESS_COMPONENT_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

#include "bOS.h"

#include "bOSXMLNode.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API ProcessComponent
			{
			public:

				ProcessComponent();
				virtual ~ProcessComponent();

				virtual void setProcessId(const char* _ProcessId) { processId = _ProcessId;}
				virtual const char* getProcessId() { return processId.c_str();}

				void init();
				bool parse(bOS::XML::XMLNode*);
				bool parse(bOS::XML::XMLAttribute*) {return false;}

				void setXML(bOS::XML::XMLNode*node);

			protected:

				String processId;

				//SQL
				bOS::SQL::ResultSetField* setRecord(bOS::SQL::ResultSetRecord&);
				String acGetWhere();
				bool parse(bOS::SQL::ResultSetField*);

			};

			class ENGINE_API XMLProcessComponent
			{
			public:

			private:
				static String PROCESS_ID_NODE;

				friend class ProcessComponent;
			};

			class ENGINE_API SQLProcessComponent
			{
			public:
				static String PROCESS_ID_FIELD;
			};
		};
	}
}

#endif //_PROCESS_COMPONENT_H_
