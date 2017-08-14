#include "FunctionExecution.h"
using namespace WorkflowEngine;

#include "Applications.h"
#include "Application.h"
#include "ApplicationFunction.h"

FunctionExecution::FunctionExecution(ApplicationFunction* _function)
{
	assert(_function != NULL);
	function = _function;

	sFunction = function->getXMLString(1);
}

FunctionExecution::FunctionExecution(Application* _application,ApplicationFunction* _function)
{
	assert((_function != NULL)&&(_application != NULL));
	function = _function;
	application = _application;

	sFunction = function->getXMLString(1);
}

FunctionExecution::~FunctionExecution()
{
}

