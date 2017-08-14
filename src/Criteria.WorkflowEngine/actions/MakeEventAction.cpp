#include "CommonDefines.h"

#include "EventsManager.h"
using namespace WorkflowEngine;

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "MakeEventAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Event::Action;

MakeEventAction::MakeEventAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task) 
    : EventAction(process, task) 
{
}

MakeEventAction::~MakeEventAction() 
{
}

int MakeEventAction::action( String& result )
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
		Common::FormalParameters& parameters = event->getParameters();
		int iSize = parameters.size();

		for ( int i=0; i<iSize; i++)
		{
			Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

			//modify by mfarina on 22/05/2005 for bug 1
			//parameter->setValue( this->getEvaluatedParameter(parameter->getValue()));
			parameter->setValue( this->getEvaluatedParameter(parameter->getValue(), parameter->getType().c_str()));
		}

		WorkflowEvents::OccurredEvent* occurredEvent = EventsManager::instance()->addEventbyActivity (event, task);
	
        result = StringUtils::toString(0);

	}
	catch ( ... )
	{
		CM_TRACE_ERROR( "Unknow Error")
        return FE_TASK_TASKACTION_PROCESS_ERROR;
    }
	
	return FE_OK;
}

int MakeEventAction::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	int iErr = EventAction::evaluateAction ();

	if ( iErr != FE_OK ) 
	{
		return iErr;
	}

    return FE_OK;
}

