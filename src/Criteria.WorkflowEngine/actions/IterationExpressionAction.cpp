#include "CommonDefines.h"

#include "Condition.h"

#include "IterationExpressionAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Iteration::Action;

#include "EvalRetrieveParameter.h"
using namespace WorkflowEngine::Criteria::BasicTask::Action;

IterationExpressionAction::IterationExpressionAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task ) 
    : IterationAction(process, task)
{
}


IterationExpressionAction::~IterationExpressionAction()
{
}

int IterationExpressionAction::action( String& result )
{
	CM_CODEBLOCK(action)

	int feErr = evaluateAction();
    
	if ( feErr != FE_OK)
	{
		CM_TRACE_DEBUG( "No Action performed.")
        return FE_TASK_TASKACTION_ERROR;
	}

	/*
		Default is almost one loop.
	*/
    int nLoopStart;
    int nLoopStep = 1;

    WorkflowRelevantData::Attribute* attr = NULL;
	WorkflowRelevantData::Attribute* attrStart=NULL;

	attrStart= getAttribute(IterationAction::LOOP_START_ATTRIBUTE.c_str());
    if ( attrStart == NULL )
	{
		CM_TRACE_ERROR( "Loop Start Attribute is not present.")
        return FE_TASK_TASKACTION_PROCESS_ERROR;	
	}
	else
	{
		CM_TRACE_CODEPATH( "loop start[" << attrStart->getValue() << "]")
        nLoopStart = atoi( attrStart->getValue().c_str() );
	}

    attr = getAttribute(IterationAction::LOOP_STEP_ATTRIBUTE.c_str() );
	if ( attr != NULL )
	{
		CM_TRACE_CODEPATH( "loop step[" << attr->getValue() << "]")
        nLoopStep = atoi( attr->getValue().c_str() );
	}

	CM_TRACE_DEBUG("Loop Attribute. Counter[" << nLoopStart << "] Step[" << nLoopStep << "]")
    
	//loop condition
    if ( pCondition->getResult() )
    {
		CM_TRACE_CODEPATH( "Condition is true")
		result = "1";

		
    }
    else
    {
		CM_TRACE_CODEPATH( "Condition is false")
        result = "0";
    }

	
    nLoopStart = nLoopStart + nLoopStep;
	attrStart->setValue( bOS::CoreString::StringUtils::toString(nLoopStart) );

	return FE_OK;
}

int IterationExpressionAction::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	String sResultName;

	//La creazione dell'oggetto script e la valutazione dell'action text dovrebbero essere
	//separate in due metodi diversi in modo da permettere operazioni intermedie
	//da parte delle vare azioni.In questo caso non è stato possibile utilizzare
	//il metodo evaluataAction della classe Action.
	if ( strcmp(_ActionText.c_str(), BaseAction::ACTION_NONE.c_str() )  == 0 )
	{
		return FE_TASK_TASKACTION_NONE;
	}


	CM_TRACE_CODEBLOCK( "Evaluating Action Text for EvalExpression Action.")
	_script = new Idioma::Evaluator();

	CM_TRACE_CODEBLOCK( "Setting Retrieve Function.")
	EvalRetrieveParameter eval;
	eval.setAction(this);
	_script->setRetrieveParameter(&eval);

	CM_TRACE_CODEBLOCK( "Parsering Expression.")
    try 
    {
	    _script->make( _ActionText );
        assert( _script != NULL );
    }
	catch ( Idioma::ScriptException&)
    {
        return FE_TASK_TASKACTION_ERROR;
    }

	Idioma::ItemListIterator iItem;
	Idioma::ItemInterface* pItem = _script->getFirstItem(iItem);

    if ( pItem == NULL ) 
	{
		CM_TRACE_ERROR( "The first item inside Task Action is empty")
        return FE_TASK_TASKACTION_INVALID;
	}
	else if ( pItem->getType() != Idioma::ITEM_CONDITION ) 
	{
		CM_TRACE_ERROR( "The first item is not a function")
        return FE_TASK_TASKACTION_INVALID;
	}

	pCondition = (Idioma::Condition*)pItem;

	return FE_OK;
}



