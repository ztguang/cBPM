#ifndef _PROCESS_FUNCTION_EXECUTION_H_
#define _PROCESS_FUNCTION_EXECUTION_H_

#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "ApplicationFunction.h"
#include "ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "FunctionExecution.h"

namespace WorkflowEngine
{
	class ProcessFunctionExecution : public FunctionExecution
	{
	public:
		ProcessFunctionExecution(Application* application,ApplicationFunction* function);
		virtual ~ProcessFunctionExecution();

		const char* run();

	private:

		String sProcessName;

	};

}

#endif //_LIBRARY_FUNCTION_EXECUTION_H_