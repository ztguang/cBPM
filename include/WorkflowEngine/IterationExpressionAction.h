#ifndef __ITERATION_EXPRESSION_ACTION_H__
#define __ITERATION_EXPRESSION_ACTION_H__

#include "IterationAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Iteration
			{
				namespace Action
				{
					class IterationExpressionAction : public IterationAction
					{
						public:

							IterationExpressionAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					        
							virtual ~IterationExpressionAction();

							virtual int evaluateAction();
							Idioma::Condition* pCondition;

							virtual int action( String& result );
						
						private:

							String _result;
					};
				}
			}
		}
	}
}

#endif
