#include "CommonDefines.h"

#include "EventsManager.h"
using namespace WorkflowEngine;

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "ConsumeEventAction.h"
using namespace WorkflowEngine::Criteria::BasicTask::Event::Action;

ConsumeEventAction::ConsumeEventAction( WorkflowProcesses::WorkflowProcess* process, WorkflowProcesses::Activity* task, Common::FormalParameters& parametersByOccurredEvent) 
    : EventAction(process, task) 
{
	parametersEvent.addParameter(parametersByOccurredEvent);
}

ConsumeEventAction::~ConsumeEventAction() 
{
}

int ConsumeEventAction::action( String& result )
{
	CM_CODEBLOCK(action)

    int feErr = this->evaluateAction();
    
	if ( feErr != FE_OK)
	{
		CM_TRACE_CODEPATH( "No Action performed.")
        return feErr;
	}

	int iRet = FE_OK;
    try
    {
		if ( parametersEvent.size() > 0) 
		{
			Common::FormalParameters& parameters = event->getParameters();
			int iSize = parameters.size();

			for ( int i=0; i<iSize; i++)
			{
				Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

				CM_TRACE_CODEPATH("Parameter Name[" << parameter->getName() << "] Value[" << parameter->getValue() << "]")
				//modify by mfarina on 22/05/2005 for bug 1
				//WorkflowRelevantData::Attribute* variable = _varsContext.add(this->getEvaluatedParameter(parameter->getValue().c_str()).c_str(), WorkflowRelevantData::XMLAttribute::STRING_TYPE.c_str());
				WorkflowRelevantData::Attribute* variable = _varsContext.add(this->getEvaluatedParameter(parameter->getValue().c_str(), parameter->getType().c_str()).c_str(), WorkflowRelevantData::XMLAttribute::STRING_TYPE.c_str());
				assert(variable != NULL);
				Common::FormalParameter* eventParam = parametersEvent.get(parameter->getName().c_str());
				assert(eventParam != NULL );
				variable->setValue ( eventParam->getValue());
			}
		}
		else
		{
			WorkflowEvents::WaitingActivity* activity = EventsManager::instance()->addWaitingActivity (task,event);
			iRet = FE_TASK_STOPPED_BY_WAINTING_EVENT;
		}


        result = StringUtils::toString(0);

	}
	catch ( ...)
	{
		CM_TRACE_ERROR( "Unknow Error")
        iRet=FE_TASK_TASKACTION_PROCESS_ERROR;
    }

	return iRet;
}

int ConsumeEventAction::evaluateAction()
{
	CM_CODEBLOCK(evaluateAction)

	int iErr = EventAction::evaluateAction ();

	if ( iErr != FE_OK ) 
	{
		return iErr;
	}

    return FE_OK;
}

