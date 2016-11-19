#ifndef _LIBRARY_FUNCTION_EXECUTION_H_
#define _LIBRARY_FUNCTION_EXECUTION_H_

#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "ApplicationFunction.h"
#include "ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "FunctionExecution.h"

namespace WorkflowEngine
{
	class LibraryFunctionExecution : public FunctionExecution
	{
	public:
		LibraryFunctionExecution(Application* application,ApplicationFunction* function);
		virtual ~LibraryFunctionExecution();

		const char* run();

	private:

		String sLibraryName;

	};

}

#endif //_LIBRARY_FUNCTION_EXECUTION_H_