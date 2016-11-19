#include "CommonDefines.h"

#include "EventsManager.h"
using namespace WorkflowEngine;

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "Activity.h"

#include "Event.h"
#include "OccurredEvent.h"
#include "WaitingActivity.h"
using namespace DataManager::Panorama;

#include "Tracer.h"

WorkflowAction::WorkflowAction(String sWorkflowNameValue)
{
	sWorkflowName = sWorkflowNameValue;
	processId = "";
	sActivityName = "";
}

WorkflowAction::WorkflowAction(const char* processIdValue, String sActivityNameValue)
{
	sWorkflowName = "";
	processId = processIdValue;
	sActivityName = sActivityNameValue;
}

WorkflowAction::~WorkflowAction()
{
	;
}

const char* WorkflowAction::getProcessId()
{
	return processId.c_str();
}

String& WorkflowAction::getActivityName()
{
	return sActivityName;
}

String& WorkflowAction::getWorkflowName()
{
	return sWorkflowName;
}

EventsManager* EventsManager::_instance = NULL;

EventsManager* EventsManager::instance()
{
	if ( _instance == NULL )
	{
		_instance = new EventsManager();
	}

	return _instance;
}

void EventsManager::deinstance()
{
	if ( _instance != NULL )
	{
		delete _instance;
	}
	_instance=NULL;
}

EventsManager::~EventsManager()
{
}

EventsManager::EventsManager()
{
}

WorkflowEvents::OccurredEvent* EventsManager::addEventbyActivity(WorkflowEvents::Event* event, WorkflowProcesses::Activity* task)
{
	WorkflowEvents::OccurredEvent* occurredEvent = new WorkflowEvents::OccurredEvent();
	occurredEvent->setId(event->getId());

	WorkflowEvents::EventSource& source = occurredEvent->getSource();
	source.setType(WorkflowEvents::EventSource::Workflow);
	source.setName(task->getActivityName());
	source.setDateTime2Now();

	Common::FormalParameters& parameters = event->getParameters();
	int iSize = parameters.size();

	Common::FormalParameters& occurredParameters = occurredEvent->getParameters();

	for ( int i=0; i<iSize; i++)
	{
		Common::FormalParameter* parameter = (Common::FormalParameter*)parameters.at(i);

		XMLNode* node = parameter->getXMLNode(0);
		Common::FormalParameter* parameter2Copy = new Common::FormalParameter( node);
		delete node;

		occurredParameters.add ( (bOS::Collections::CollectionEntry*)parameter2Copy);
	}


	DataBaseHelper::instance()->addOccurredEvent(occurredEvent);

	return occurredEvent;
}

WorkflowEvents::WaitingActivity* EventsManager::addWaitingActivity(WorkflowProcesses::Activity* task,WorkflowEvents::Event* event)
{
	WorkflowEvents::WaitingActivity* activity = new WorkflowEvents::WaitingActivity();

	activity->setProcessId (task->getProcessId());
	activity->setActivityName(task->getActivityName());
	activity->setDateTime2Now();

	DataBaseHelper::instance()->addWaitingActivity(event, activity);

	return activity;
}

WorkflowEvents::OccurredEvent* EventsManager::getAnEvent2Manage(WorkflowActionList& vWorkflows)
{
	CM_CODEBLOCK(manageAnEvent)

	static bool manageFromBootstrap = true;
	
	WorkflowEvents::OccurredEvent* event = NULL;
	
	if (  manageFromBootstrap )
	{
		event = DataBaseHelper::instance()->getUnmanagedEvent(true);
		manageFromBootstrap = false;
	}
	else
	{
		event = DataBaseHelper::instance()->getUnmanagedEvent(false);
	}

	if ( event == NULL )
	{
		return false;
	}

	event->set2Managing();

	//Retrieving ProcessAction
	WorkflowEvents::Event* definedEvent = DataBaseHelper::instance()->getEventDefinition(event->getId() );
	if ( definedEvent == NULL )
	{
		CM_TRACE_ERROR("Occurred Event[" << event->getId().c_str() << "] is not defined. No action is performed.")
		event->set2Managed();
	}

	DataBaseHelper::instance()->updateOccurredEvent(event);

	vWorkflows.clear();

	int iSize;

	iSize = definedEvent->getActions().size();

	for ( int i=0; i<iSize; i++)
	{
		WorkflowEvents::ScenarioEventAction* action = (WorkflowEvents::ScenarioEventAction*)definedEvent->getActions().at(i);
		if ( action->isProcessExecuteType() )
		{
			vWorkflows.push_back ( WorkflowAction(action->getValue()));
		}
	}

	WorkflowEvents::WaitingActivities* waitingActivities = DataBaseHelper::instance()->getWaitingForActivities(event->getId());
	if ( waitingActivities != NULL ) 
	{
		iSize = waitingActivities->size();
		for ( int i=0; i<iSize;i++)
		{
			WorkflowEvents::WaitingActivity* activity = (WorkflowEvents::WaitingActivity*)waitingActivities->at(i);

			if ( activity->is2Manage() )
			{
				activity->set2Managing();
				vWorkflows.push_back ( WorkflowAction(activity->getProcessId(), activity->getActivityName() ));
			}
		}
	}

	return event;
}

void EventsManager::setEvent2Managed(WorkflowEvents::OccurredEvent* occurredEvent)
{
	occurredEvent->set2Managed();

	WorkflowEvents::WaitingActivities* waitingActivities = DataBaseHelper::instance()->getWaitingForActivities(occurredEvent->getId());
	
	if ( waitingActivities != NULL )
	{
		int iSize = waitingActivities->size();
		for ( int i=0; i<iSize;i++)
		{
			WorkflowEvents::WaitingActivity* activity = (WorkflowEvents::WaitingActivity*)waitingActivities->at(i);
			activity->set2Managed();
			DataBaseHelper::instance()->updateWaitingActivity(activity);
		}
	}

	DataBaseHelper::instance()->updateOccurredEvent(occurredEvent);
}


