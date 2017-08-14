#ifndef _SCRIPT_FUNCTION_EXECUTION_H_
#define _SCRIPT_FUNCTION_EXECUTION_H_

#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "ApplicationFunction.h"
#include "ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "FunctionExecution.h"

namespace WorkflowEngine
{
	class ScriptFunctionExecution : public FunctionExecution
	{
	public:
		ScriptFunctionExecution(ApplicationFunction* functionsignature,ApplicationFunction* function);
		virtual ~ScriptFunctionExecution();

		String replace(const String& sValue, const String& sParam, const String& sParamValue);

		const char* run();

	private:

		ApplicationFunction* functionsignature;
	};

}

#endif //_SCRIPT_FUNCTION_EXECUTION_H_