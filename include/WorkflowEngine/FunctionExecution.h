#ifndef _FUNCTION_EXECUTION_H_
#define _FUNCTION_EXECUTION_H_

#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "Application.h"
#include "ApplicationFunction.h"
#include "ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "bOS.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

namespace WorkflowEngine
{
	class FunctionExecution
	{
	public:
		FunctionExecution(ApplicationFunction* function);
		FunctionExecution(Application* application, ApplicationFunction* function);
		virtual ~FunctionExecution();

		virtual const char* run() = 0;

	protected:

		ApplicationFunction* function;
		Application* application;
		String sFunction;

		StringBuffer sResultFromExecution;
	};
}

#endif //_FUNCTION_EXECUTION_H_