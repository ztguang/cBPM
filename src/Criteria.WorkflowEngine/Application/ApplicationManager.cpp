#include "ApplicationManager.h"
#include "ApplicationException.h"
#include "FunctionExecution.h"
#include "SocketFunctionExecution.h"
#include "LibraryFunctionExecution.h"
#include "ProcessFunctionExecution.h"
#include "ScriptFunctionExecution.h"
using namespace WorkflowEngine;

#include "Applications.h"
#include "Application.h"
#include "ApplicationFunction.h"

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "Tracer.h"

ApplicationManager* ApplicationManager::_instance = NULL;

ApplicationManager::ApplicationManager()
{
}

ApplicationManager::~ApplicationManager()
{
}

ApplicationManager* ApplicationManager::instance()
{
	if ( _instance == NULL )
	{
		_instance = new ApplicationManager();
	}

	return _instance;
}

void ApplicationManager::deinstance()
{
	if ( _instance != NULL )
	{
		delete _instance;
	}

	_instance =NULL;
}


ApplicationFunctionResult* ApplicationManager::execute (ApplicationFunction& function)
{
	CM_CODEBLOCK(execute)

	CM_TRACE_DEBUG("Reading info Application[" << function.getApplication().c_str() << "]")
	Application application;
	application.setName (function.getApplication());
	
	try
	{
		DataBaseHelper::instance()->getApplication(application);
	}
	catch ( DBException& dbErr )
	{
		CM_TRACE_ERROR("Impossible to execute primitive. Application[" << function.getApplication() << "] not found.["<<dbErr.getMessage() << "]")
		throw ApplicationException(APPLICATION_NOT_FOUND);
	}

	ApplicationFunctions& functions = application.getFunctions();

	ApplicationFunction* functionCheck = functions.get(function.getName().c_str());
	if ( functionCheck == NULL )
	{
		CM_TRACE_ERROR("Impossible to execute function. function[" << function.getName() << "] not found.")
		throw ApplicationException(FUNCTION_NOT_FOUND);
	}

	FunctionExecution* execution = NULL;

	if ( functionCheck->isScriptable() )
	{
		execution = new ScriptFunctionExecution(functionCheck, &function);
	}
	else
	{
		String sApplicationType = application.getType();

		if ( strcmp( sApplicationType.c_str(), XMLApplication::EXECUTABLE_TYPE.c_str() ) == 0 )
		{
			execution = new SocketFunctionExecution(&application, &function);
		}
		else if ( strcmp( sApplicationType.c_str(), XMLApplication::LIBRARY_TYPE.c_str() ) == 0 )
		{
			execution = new LibraryFunctionExecution(&application, &function);
		}
		else if ( strcmp( sApplicationType.c_str(), XMLApplication::PROCESS_TYPE.c_str() ) == 0 )
		{
			execution = new ProcessFunctionExecution(&application, &function);
		}
		else
		{
			CM_TRACE_WARNING("Unknow Application Type!")
			throw ApplicationException(TYPE_NOT_MANAGED);
		}
	}

	ApplicationFunctionResult* result = new ApplicationFunctionResult();
	try
	{
		const char* acReceive = execution->run();
		if ( acReceive == NULL )
		{
			CM_TRACE_DEBUG("Receive is null.")
			result->setCode(1000);
			result->setMessage("UnknowError.Impossible to parse Application Result.");
		}
		else
		{
			result->init(acReceive);
		}

		/*if ( acReceive != NULL )
			delete acReceive;
			*/
	}
	catch ( ChannelException ceErr) 
	{
		CM_TRACE_ERROR("Impossible to execute Application.Err[" << ceErr.getMessage() << "]")
		result->setCode(1000);
		result->setMessage(ceErr.getMessage());
	}
	catch ( DynamicLibraryException dlErr ) 
	{
		result->setCode(1000);
		result->setMessage(dlErr.getMessage());
		CM_TRACE_ERROR("Impossible to execute Application.Err[" << dlErr.getMessage() << "]")
	}
	catch ( ProcessExecutionException peErr)
	{
		result->setCode(1000);
		result->setMessage(peErr.getMessage());
		CM_TRACE_ERROR("Impossible to execute Application.Err[" << peErr.getMessage() << "]")
	}
	catch ( ...)
	{
		result->setCode(1000);
		result->setMessage("UnknowError.Impossible to parse Application Result.");
		CM_TRACE_ERROR("UnknowError.Impossible to parse Application Result.")
	}

	//Analyzing parameter.

	delete execution;

	return result;
}

