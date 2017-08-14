#ifndef __PRIMITIVE_ACTION_ATTACH_H__
#define __PRIMITIVE_ACTION_ATTACH_H__

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
				class PrimitiveActionAttach : public PrimitiveAction
				{
					public:

						PrimitiveActionAttach( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
				        
						virtual ~PrimitiveActionAttach();

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



