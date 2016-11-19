
#ifndef __FE_EVALEXPRESSIONACTION_H__
#define __FE_EVALEXPRESSIONACTION_H__

#include "ConditionAction.h"

#include "EvalRetrieveParameter.h"
using namespace WorkflowEngine::Criteria::BasicTask::Action;

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Condition
			{
				namespace Action
				{
					class EvalExpressionAction : public WorkflowEngine::Criteria::BasicTask::Condition::Action::ConditionAction 
					{
						public:

							EvalExpressionAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
						    
							virtual ~EvalExpressionAction();

							virtual int action( String& result );
						
						private:

							String _result;

							virtual int evaluateAction();
							Idioma::Expression* pExpression;
							String sAttribResult;

							static const String DEFAULT_RESULT_ATTRIBUTE;


							friend class EvalRetrieve;
					};
				}
			}
		}
	}
}

#endif
