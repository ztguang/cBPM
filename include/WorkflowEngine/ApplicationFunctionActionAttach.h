#ifndef __APPLICATION_FUNCTION_ACTION_ATTACH_H__
#define __APPLICATION_FUNCTION_ACTION_ATTACH_H__

#include "ApplicationFunctionAction.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace BasicTask
		{
			namespace Application
			{
				namespace Action
				{
					class ApplicationFunctionActionAttach : public ApplicationFunctionAction
					{
						public:

							ApplicationFunctionActionAttach( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);
					        
							virtual ~ApplicationFunctionActionAttach();

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



