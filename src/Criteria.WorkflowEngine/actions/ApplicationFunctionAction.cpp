#include "CommonDefines.h"

#include "ApplicationFunctionAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Application::Action;

const String ApplicationFunctionAction::DEFAULT_RESULT_ATTRIBUTE	= "APPLICATION_API";

ApplicationFunctionAction::ApplicationFunctionAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
: BaseAction(process, task)
{
	function = NULL;
}

ApplicationFunctionAction::~ApplicationFunctionAction()
{
	if ( function != NULL )
	{
		delete function;
	}
}
int ApplicationFunctionAction::evaluateAction()
{
	if ( strcmp(_ActionText.c_str(), BaseAction::ACTION_NONE.c_str() )  == 0 )
	{
		return FE_TASK_TASKACTION_NONE;
	}
	
	function = new WorkflowApplicationsData::ApplicationFunction();
	function->init(_ActionText.c_str());


	//
	Common::FormalParameters& parameters=function->getParameters();

	unsigned int iSize = parameters.size();
	Common::FormalParameter* parameter = NULL;
	for ( unsigned int i=0; i<iSize; i++)
	{
		parameter = (Common::FormalParameter*)parameters.at(i);
		//modify by mfarina on 22/05/2005 for bug 1
		//parameter->setValue ( this->getEvaluatedParameter( parameter->getValue() ) );
		parameter->setValue ( this->getEvaluatedParameter( parameter->getValue(), parameter->getType().c_str() ) );
	}


	return FE_OK;
}
