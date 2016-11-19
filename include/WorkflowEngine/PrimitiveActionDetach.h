#ifndef __PRIMITIVE_ACTION_DETACH_H__
#define __PRIMITIVE_ACTION_DETACH_H__

#include "BaseAction.h"
#include "PrimitiveAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Primitive
			{
				namespace Action
				{
					class PrimitiveActionDetach : public PrimitiveAction
					{
						public:
						
							PrimitiveActionDetach( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

							virtual ~PrimitiveActionDetach();

							virtual int action( String& result );

						protected:
							int evaluateAction();

						private:

							WorkflowRelevantData::Attribute*      attribResult;
					};
				}
			}
		}
	}
}

#endif 

