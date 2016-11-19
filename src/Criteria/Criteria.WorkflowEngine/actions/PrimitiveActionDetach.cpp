#include "CommonDefines.h"

#include "PrimitiveActionDetach.h"
using namespace WorkflowEngine::Criteria::BasicTask::Primitive::Action;

#include "bOS.h"
#include "bOSRuntimeException.h"
using namespace bOS::Exception;

PrimitiveActionDetach::PrimitiveActionDetach( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task)
    : PrimitiveAction(process, task)
{
    attribResult = NULL;
}

PrimitiveActionDetach::~PrimitiveActionDetach()
{
}

int PrimitiveActionDetach::action( String& result )
{
	CM_CODEBLOCK(action)

    int feErr = this->evaluateAction();
    if ( feErr != FE_OK)
    {
		CM_TRACE_CODEBLOCK( "No Action performed.")
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
	}
    catch ( RuntimeException& rte)
    {
		CM_TRACE_ERROR( "Primitive [" << _primitive << "] is not execute. [" << rte.getMessage() << "]")
        return FE_TASK_TASKACTION_PROCESS_ERROR;
    }

	CM_TRACE_CODEPATH( "Primitive executing.....")
	result = "";
	return FE_OK;
}

int PrimitiveActionDetach::evaluateAction()
{
	int feErr = PrimitiveAction::evaluateAction ();

	if ( feErr != FE_OK ) 
	{
		return feErr;
	}

	Idioma::ItemListIterator iItem;
	Idioma::ItemInterface* pItem = _script->getFirstItem(iItem);

    if ( pItem == NULL ) 
    {
        return FE_TASK_TASKACTION_INVALID;
    }
	else if ( pItem->getType() != Idioma::ITEM_FUNCTION ) 
	{
        return FE_TASK_TASKACTION_INVALID;
	}

	Idioma::Function* pFunc = (Idioma::Function*)pItem;

	
	if ( pFunc->getResult().compare("") != 0) 
	{
		attribResult = getAttribute( pFunc->getResult() );

		//TODO: The result code is to set. 
		/*
		if ( !attribResult ) 
            return FE_TASK_TASKACTION_INVALID;
		*/
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
                _Arguments.push_back( attr->getValue() );
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

