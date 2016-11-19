#ifndef __APPLICATION_FUNCTION_ACTION_H__
#define __APPLICATION_FUNCTION_ACTION_H__

#include "BaseAction.h"

#include "ApplicationFunction.h"
using namespace DataManager::Panorama;

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
					class ApplicationFunctionAction : public WorkflowEngine::Criteria::BasicTask::Action::BaseAction
					{
						public:
						
							ApplicationFunctionAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task);

							virtual ~ApplicationFunctionAction();

							virtual int action( String& result ) = 0;

						protected:

							virtual int evaluateAction();
							WorkflowApplicationsData::ApplicationFunction* function;

							static const String DEFAULT_RESULT_ATTRIBUTE;
					};
				}
			}
		}
	}
}

#endif


