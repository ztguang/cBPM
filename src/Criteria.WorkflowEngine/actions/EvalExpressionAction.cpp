#include "CommonDefines.h"

#include "EvalExpressionAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Condition::Action;

const String EvalExpressionAction::DEFAULT_RESULT_ATTRIBUTE	= "Evaluator";

EvalExpressionAction::EvalExpressionAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task ) 
    : ConditionAction(process, task)
{
	CM_CODEBLOCK(EvalExpressionAction)
	attribResult = NULL;
}


EvalExpressionAction::~EvalExpressionAction()
{
	CM_CODEBLOCK(~EvalExpressionAction)
}

int EvalExpressionAction::action( String& result )
{
	CM_CODEBLOCK(action)

	int feErr = evaluateAction();
    if ( feErr != FE_OK)
    {
        return feErr;
    }
	

	attribResult->setValue( pExpression->getResult());
    result = pExpression->getResult();

	CM_TRACE_CODEPATH( "EvalExpression is executed with result code[" << result << "]")

	return FE_OK;
}

int EvalExpressionAction::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	String sResultName;

	if ( strcmp(_ActionText.c_str(), BaseAction::ACTION_NONE.c_str() )  == 0 )
	{
		return FE_TASK_TASKACTION_NONE;
	}

	_script = new Idioma::Evaluator();

	EvalRetrieveParameter eval;
	eval.setAction (this);
	_script->setRetrieveParameter(&eval);

	try
	{
		_script->make(_ActionText);
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
	else if ( pItem->getType() != Idioma::ITEM_EXPRESSION ) 
	{
		CM_TRACE_ERROR( "The first item is not a function")
        return FE_TASK_TASKACTION_INVALID;
	}

	pExpression = (Idioma::Expression*)pItem;

	if ( pExpression->getResultAttribute().compare("") != 0) 
	{
		attribResult = getAttribute( pExpression->getResultAttribute() );
		sResultName=pExpression->getResultAttribute();
	}
	else
	{	
		sResultName = EvalExpressionAction::DEFAULT_RESULT_ATTRIBUTE;
		
	}
	CM_TRACE_CODEPATH( "A result tag is not defined. Attribute Result[" << sResultName << "]")
	
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

	return FE_OK;
}


