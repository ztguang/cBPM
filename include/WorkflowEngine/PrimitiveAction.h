#ifndef __PRIMITIVE_ACTION_H__
#define __PRIMITIVE_ACTION_H__

#include "BaseAction.h"

#include "bOSProcess.h"
using namespace bOS::System;

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
					class PrimitiveAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction
					{
						public:
						
							PrimitiveAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

							virtual ~PrimitiveAction();

							virtual int action( String& result ) = 0;

						protected:

							virtual int evaluateAction();

							ProcessArguments  _Arguments;
							Process*		  _Process;
							String			  _primitive;

							static const String DEFAULT_RESULT_ATTRIBUTE;

					};
				}
			}
		}
	}
}

#endif


