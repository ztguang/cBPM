#include "CommonDefines.h"

#include "IterationCounterAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Iteration::Action;

const String IterationCounterAction::MAX_LOOPS_ATTRIBUTE	= "MAX_LOOPS";

IterationCounterAction::IterationCounterAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task ) 
    : IterationAction(process, task)
{
}

IterationCounterAction::~IterationCounterAction()
{
}

int IterationCounterAction::action( String& result )
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
    int nMaxLoops = 1;
    int nLoopStart;
    int nLoopStep = 1;

    WorkflowRelevantData::Attribute* attr = NULL;
	WorkflowRelevantData::Attribute* attrStart=NULL;

	attrStart= getAttribute(IterationCounterAction::LOOP_START_ATTRIBUTE.c_str());
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

    //Retrieving loop attributes.
    attr = getAttribute( IterationCounterAction::MAX_LOOPS_ATTRIBUTE.c_str() );
    if ( attr != NULL )
	{
		CM_TRACE_CODEPATH( "Nr. loops[" << attr->getValue() << "]")
        nMaxLoops = atoi( attr->getValue().c_str() );
	}

    attr = getAttribute(IterationCounterAction::LOOP_STEP_ATTRIBUTE.c_str() );
	if ( attr != NULL )
	{
		CM_TRACE_CODEPATH( "loop step[" << attr->getValue() << "]")
        nLoopStep = atoi( attr->getValue().c_str() );
	}

	CM_TRACE_DEBUG("Loop Attribute. Counter[" << nLoopStart << "] Loops[" << nMaxLoops << "] Step[" << nLoopStep << "]")
    
	//loop condition
    if ( nLoopStart < nMaxLoops )
    {
		CM_TRACE_CODEPATH( "Condition is true")
        nLoopStart = nLoopStart + nLoopStep;
		attrStart->setValue( StringUtils::toString(nLoopStart) );

		result = "1";
    }
    else
    {
		CM_TRACE_CODEPATH( "Condition is false")
        result = "0";
    }

	return FE_OK;
}

