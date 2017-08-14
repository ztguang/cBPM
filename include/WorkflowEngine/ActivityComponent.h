#ifndef _ACTIVITY_COMPONENT_H_
#define _ACTIVITY_COMPONENT_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

#include "bOS.h"

#include "bOSXMLNode.h"

#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

#include "ProcessComponent.h"

namespace DataManager
{
	namespace Panorama
	{
		namespace WorkflowProcesses
		{
			class ENGINE_API ActivityComponent : public ProcessComponent

			{
			public:

				ActivityComponent();
				virtual ~ActivityComponent();

				virtual void setActivityId(const char* acId);
				virtual String& getActivityId();

				void init();
				bool parse(bOS::XML::XMLAttribute*);
				bool parse(bOS::XML::XMLNode*);

				void setXML(bOS::XML::XMLNode*node);

			protected:

				String sId;

				//SQL
				bOS::SQL::ResultSetField* setRecord(bOS::SQL::ResultSetRecord&);
				String acGetWhere();
				bool parse(bOS::SQL::ResultSetField*);

			};

			class ENGINE_API XMLActivityComponent
			{
			public:
				static String ID_ATTRIBUTE;
			};

			class ENGINE_API SQLActivityComponent
			{
			public:
				static String ACTIVITY_ID_FIELD;
			};
		};
	}
}

#endif //_ACTIVITY_COMPONENT_H_
