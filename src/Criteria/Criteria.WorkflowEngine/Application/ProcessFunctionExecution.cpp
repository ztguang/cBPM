#include "ProcessFunctionExecution.h"
#include "ApplicationException.h"
using namespace WorkflowEngine;

#include "Applications.h"
#include "Application.h"
#include "ApplicationFunction.h"

#include "bOSProcess.h"
using namespace bOS::System;

#include "bOSRuntimeException.h"
using namespace bOS::Exception;

#include "Tracer.h"

String PARAMETER_EXECUTION_RESULT	= "Execution";

ProcessFunctionExecution::ProcessFunctionExecution(Application* _application, ApplicationFunction* _function) : 
	FunctionExecution(_application, _function)
{
	sProcessName = application->getLibrary();
}

ProcessFunctionExecution::~ProcessFunctionExecution()
{
}

const char* ProcessFunctionExecution::run()
{
	CM_CODEBLOCK(ProcessFunctionExecution::run)

	ProcessArguments  _Arguments;
	Process*		  _Process = new Process();

	Common::FormalParameters& vParameters = function->getParameters();
	Common::FormalParameter* parameter = NULL;

	for ( unsigned int i=0; i<vParameters.size(); i++)
	{
		parameter = (Common::FormalParameter*)vParameters.at(i);
		CM_TRACE_DEBUG("Parameter[" << parameter->getValue() << "]")
		_Arguments.push_back(parameter->getValue() );
	}

	try
    {
        _Process->createProcess( sProcessName, _Arguments );

		CM_TRACE_CODEPATH( "Joining Process........")
		int iProcessReturn = _Process->waitFor();

		if ( _Process->isRunning() )
		{
			CM_TRACE_ERROR( "Primitive is too alive.")
            throw new DynamicLibraryException( "Primitive is too alive.");
		}
		else
		{
			ApplicationFunctionResult result;
			result.setCode (0);
			result.setMessage ("OK");

			Common::FormalParameters& vParameters = result.getParameters();
			Common::FormalParameter parameter(PARAMETER_EXECUTION_RESULT, StringUtils::toString(iProcessReturn));
			parameter.setType (Common::XMLFormalParameter::NUMBER_TYPE);
			vParameters.addParameter (parameter);

			char* acReceive = StringUtils::toChar (result.getXMLString(0));

			return acReceive;

		}
	}
    catch ( RuntimeException& rte)
    {
		CM_TRACE_ERROR( "Primitive [" << sProcessName << "] is not execute. [" << rte.getMessage() << "]")
		throw new DynamicLibraryException(rte.getMessage());
    }
	
	
}