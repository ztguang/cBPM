#ifndef _SOCKET_FUNCTION_EXECUTION_H_
#define _SOCKET_FUNCTION_EXECUTION_H_

#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "ApplicationFunction.h"
#include "ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

#include "FunctionExecution.h"

namespace WorkflowEngine
{
	class SocketFunctionExecution : public FunctionExecution
	{
	public:
		SocketFunctionExecution(Application* application,ApplicationFunction* function);
		virtual ~SocketFunctionExecution();

		const char* run();

	private:

		String sHost;
		int iPort;

	};

}

#endif //_SOCKET_FUNCTION_EXECUTION_H_