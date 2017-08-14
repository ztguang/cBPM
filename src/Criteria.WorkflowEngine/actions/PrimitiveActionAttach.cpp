#include "CommonDefines.h"

#include "PrimitiveActionAttach.h"
using namespace WorkflowEngine::Criteria::BasicTask::Primitive::Action;

#include "bOS.h"
#include "bOSRuntimeException.h"
using namespace bOS::Exception;

#include "bOSProcess.h"
using namespace bOS::System;

PrimitiveActionAttach::PrimitiveActionAttach( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
    : PrimitiveAction(process, task) 
{
    attribResult = NULL;
}

PrimitiveActionAttach::~PrimitiveActionAttach() 
{
}

int PrimitiveActionAttach::action( String& result )
{
	CM_CODEBLOCK(action)

    int feErr = this->evaluateAction();
    
	if ( feErr != FE_OK)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return feErr;
	}

	CM_TRACE_CODEPATH("Performerd Action: [" << _primitive << "]")
	CM_TRACE_CODEPATH("\n********* Primitive Argument *********")
	CM_TRACE_FOR( unsigned int indexArg = 0, indexArg < _Arguments.size(), indexArg++ )
	CM_TRACE_CODEPATH("nr:" << indexArg << " Value:[" << _Arguments[indexArg] << "]\n")
	CM_TRACE_NEXT

    try
    {
        _Process->createProcess( _primitive, _Arguments );

		CM_TRACE_CODEPATH( "Joining Process........")
		int iProcessReturn = _Process->waitFor();

		if ( _Process->isRunning() )
		{
			CM_TRACE_ERROR( "Primitive is too alive.")
            return FE_TASK_TASKACTION_PROCESS_ERROR;
		}
		else
		{
			CM_TRACE_CODEPATH( "Primitive is not alive Return Code [" << iProcessReturn << "]")
			attribResult->setValue( StringUtils::toString(iProcessReturn) );
            result = StringUtils::toString(iProcessReturn);
		}
	}
    catch ( RuntimeException& rte)
    {
		CM_TRACE_ERROR( "Primitive [" << _primitive << "] is not execute. [" << rte.getMessage() << "]")
        return FE_TASK_TASKACTION_PROCESS_ERROR;
    }
	
	CM_TRACE_CODEPATH( "Primitive [" << _primitive << "] is executed with result code[" << result << "]")

	return FE_OK;
}

int PrimitiveActionAttach::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	int iErr = PrimitiveAction::evaluateAction ();

	if ( iErr != FE_OK ) 
	{
		return iErr;
	}

	Idioma::ItemListIterator iItem;
	Idioma::ItemInterface* pItem = _script->getFirstItem(iItem);

    if ( pItem == NULL ) 
    {
		CM_TRACE_ERROR( "TaskAction is empty.")
        return FE_TASK_TASKACTION_INVALID;
    }
    else if ( pItem->getType() != Idioma::ITEM_FUNCTION ) 
	{
		CM_TRACE_ERROR( "TaskAction is not a function")
        return FE_TASK_TASKACTION_INVALID;
	}

	Idioma::Function* pFunc = (Idioma::Function*)pItem;
	String sResultName;

	if ( pFunc->getResult().compare("") != 0) 
	{
		attribResult = getAttribute( pFunc->getResult() );
		sResultName=pFunc->getResult();
		CM_TRACE_CODEPATH( "A result tag is defined. Attribute Result[" << sResultName << "]")
	}
	else
	{	
		sResultName = PrimitiveAction::DEFAULT_RESULT_ATTRIBUTE;
		CM_TRACE_CODEPATH( "A result tag is not defined. Attribute Result[" << sResultName << "]")
	}
	
	//
	//If result attribute is missing will be a new attribute with same name 
	//
	if ( attribResult == NULL )
	{
		attribResult = _varsContext.add(sResultName.c_str(), WorkflowRelevantData::XMLAttribute::NUMBER_TYPE.c_str());
	}
	else
	{
		attribResult = _varsContext.add(*attribResult);
	}
	

    Idioma::ParamListIterator iP;
	Idioma::Parameter* pParam = pFunc->getFirstParam(iP);
	
	while ( pParam != NULL ) 
	{
		WorkflowRelevantData::Attribute* attr = getAttribute( pParam->getName() );
		if ( !attr ) 
            return FE_TASK_TASKACTION_INVALID;
	
		switch ( pParam->getType() )
		{
		case Idioma::PARAM_IN:
            {
				//modify by mfarina on 22/05/2005 for bug 1
                _Arguments.push_back( this->getEvaluatedParameter( attr->getValue() ));
				//_Arguments.push_back( this->getEvaluatedParameter( attr->getValue(), attr->getType() ));
            }
            break;
        case Idioma::PARAM_INOUT:
            {
                return FE_TASK_TASKACTION_INVALID;
            }
            break;
        case Idioma::PARAM_OUT:
            {
                return FE_TASK_TASKACTION_INVALID;
            }
            break;
		}
		pParam = pFunc->getNextParam(iP);
	}

    _primitive = pFunc->getFunctionName();

    return FE_OK;
}

