#include "LibraryFunctionExecution.h"
#include "ApplicationException.h"
using namespace WorkflowEngine;

#include "Applications.h"
#include "Application.h"
#include "ApplicationFunction.h"

#include "Tracer.h"

LibraryFunctionExecution::LibraryFunctionExecution(Application* _application, ApplicationFunction* _function) :
	FunctionExecution(_application, _function)
{
	sLibraryName = application->getLibrary();
}

LibraryFunctionExecution::~LibraryFunctionExecution()
{
}

const char* LibraryFunctionExecution::run()
{
	CM_CODEBLOCK(LibraryFunctionExecution::run)

    //ztg alter
	// Open the library

	#ifdef WIN32_NO_USE
		HINSTANCE pDl;
		pDl = LoadLibrary( sLibraryName.c_str() );
	#else
		void *pDl;
		pDl = dlopen( sLibraryName.c_str(), RTLD_NOW | RTLD_GLOBAL );
	#endif

	if ( pDl == 0)
	{
		CM_TRACE_FATAL("Impossible to initialize library[" << sLibraryName << "]")
		throw new DynamicLibraryException(LIBRARY_NOT_INITIALIZE);
	}

	typedef void (*InstanceApplication)(char*);
	typedef void (*DeleteApplication)(char*);
	typedef char* (*ExecuteApplicationApi)(char* );

	// The function pointer
	InstanceApplication instanceApplication = 0;
	DeleteApplication deleteApplication = 0;
	ExecuteApplicationApi executeApplicationApi = 0;

	// Acquire the function pointer
	#ifdef WIN32_NO_USE
		instanceApplication = ( InstanceApplication )GetProcAddress( pDl, "InstanceApplication" );
	#else
		instanceApplication = ( InstanceApplication )dlsym( pDl, "InstanceApplication" );
	#endif

	if ( instanceApplication == 0)
	{
		CM_TRACE_FATAL("Impossible to retrieve InstanceApplication")
		throw new DynamicLibraryException(INSTANCEAPPLICATION_NOT_INITIALIZE);
	}

	instanceApplication( (char*)function->getApplication().c_str() );

	#ifdef WIN32_NO_USE
		executeApplicationApi = ( ExecuteApplicationApi )GetProcAddress( pDl, "ExecuteApplicationApi" );
	#else
		executeApplicationApi = ( ExecuteApplicationApi )dlsym( pDl, "ExecuteApplicationApi" );
	#endif

	if ( executeApplicationApi == 0)
	{
		CM_TRACE_FATAL("Impossible to retrieve ExecuteApplicationApi")
		throw new DynamicLibraryException(EXECUTEAPPLICATIONAPI_NOT_INITIALIZE);
	}

	CM_TRACE_DEBUG("Executing Function...")
	char* acReceive = executeApplicationApi( (char*)function->getXMLString(1).c_str() );
	if ( acReceive == NULL )
	{
		CM_TRACE_DEBUG("acReveive is null directly from libraryFunction")
	}
	else
	{
		CM_TRACE_DEBUG("acReceive[" << acReceive << "]")
	}

	#ifdef WIN32_NO_USE
		deleteApplication = ( DeleteApplication )GetProcAddress( pDl, "DeleteApplication" );
	#else
		deleteApplication = ( DeleteApplication )dlsym( pDl, "DeleteApplication" );
	#endif

	if ( deleteApplication == 0)
	{
		CM_TRACE_FATAL("Impossible to retrieve DeleteApplication")
		throw new DynamicLibraryException(DELETEAPPLICATION_NOT_INITIALIZE);
	}
	deleteApplication( (char*)function->getApplication().c_str() );

	CM_TRACE_CODEPATH("Free Library")
	//TODO: Liberare ..........
	/*
	#ifdef WIN32
		FreeLibrary( pDl );
	#else
		dlclose( pDl );
	#endif
	*/

	return acReceive;
}
