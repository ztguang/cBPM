#include "CommonDefines.h"

#include "ApplicationFunctionActionAttach.h"
using namespace WorkflowEngine::Criteria::BasicTask::Application::Action;

#include "ApplicationManager.h"
#include "ApplicationException.h"
using namespace WorkflowEngine;

ApplicationFunctionActionAttach::ApplicationFunctionActionAttach( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
    : ApplicationFunctionAction(process, task) 
{
    attribResult = NULL;
}

ApplicationFunctionActionAttach::~ApplicationFunctionActionAttach() 
{
}

int ApplicationFunctionActionAttach::action( String& result )
{
	CM_CODEBLOCK(action)

    int feErr = this->evaluateAction();
    
	if ( feErr != FE_OK)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return feErr;
	}

    try
    {
		ApplicationFunctionResult* resultFunction = ApplicationManager::instance()->execute(*function);
				
		if ( resultFunction->getCode () == 0 )
		{
			Common::FormalParameter* parameter=NULL;
			WorkflowRelevantData::Attribute* variable=NULL;
			for ( unsigned int i=0; i<function->getResult().getParameters().size(); i++)
			{
				parameter = (Common::FormalParameter*)function->getResult().getParameters().at(i);
				CM_TRACE_DEBUG("Parameter Modeled: Name[" << parameter->getName() << "] Value[" << parameter->getValue() << "] Bind[" << parameter->getBind() << "]")
				
				variable = getAttribute(parameter->getBind());

				if ( variable != NULL )
				{
					CM_TRACE_DEBUG("Attribute[" << parameter->getBind() << "] found inside process.")
					variable = _varsContext.add(*variable);
				}
				else
				{
					CM_TRACE_DEBUG("Attribute[" << parameter->getValue() << "] not found inside process.")
					variable = _varsContext.add(parameter->getName().c_str(), WorkflowRelevantData::XMLAttribute::NUMBER_TYPE.c_str());
					variable->setDirection ( WorkflowRelevantData::XMLAttribute::DIRECTION_TASK );
				}

				Common::FormalParameters& parameters = resultFunction->getParameters();
				Common::FormalParameter* parameterOut = parameters.get(parameter->getName().c_str());

				if ( parameterOut != NULL) 
				{
					variable->setValue (parameterOut->getValue());

					//TODO
					//Verificare il value del parametro sia salvato sul file.
					parameter->setValue (parameterOut->getValue());
				}
				else
				{
					CM_TRACE_WARNING("Parameter[" << parameter->getName() << "] not found inside ResultTag return from Application Api.")
				}
			}
		}

		attribResult->setValue( resultFunction->getMessage());
        result = StringUtils::toString(resultFunction->getCode());

		delete resultFunction;
	}
	catch ( ApplicationException& ae)
	{
		CM_TRACE_ERROR( "Error [" << function->getName() << "] is not execute. [" << ae.getMessage() << "]")
        return FE_TASK_TASKACTION_PROCESS_ERROR;
    }
	catch ( ChannelException& ce)
	{
		CM_TRACE_ERROR( "Function [" <<  function->getName() << "] is not execute. [" << ce.getMessage() << "]")
        return FE_TASK_TASKACTION_PROCESS_ERROR;
    }
	
	CM_TRACE_CODEPATH( "Function [" << function->getName() << "] is executed with result code[" << result << "]")

	return FE_OK;
}

int ApplicationFunctionActionAttach::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	int iErr = ApplicationFunctionAction::evaluateAction ();

	if ( iErr != FE_OK ) 
	{
		return iErr;
	}

	String sResultName;

	ApplicationFunctionResult& result = function->getResult();

	sResultName = ApplicationFunctionAction::DEFAULT_RESULT_ATTRIBUTE;
	CM_TRACE_CODEPATH( "A result tag is not defined. Attribute Result[" << sResultName << "]")

	attribResult = _varsContext.add(sResultName.c_str(), WorkflowRelevantData::XMLAttribute::NUMBER_TYPE.c_str());

    return FE_OK;
}

