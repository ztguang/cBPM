#include "Event.h"
#include "ScenarioEventAction.h"
#include "EventActions.h"
#include "EventConsumerPolicy.h"
#include "EventContext.h"
#include "EventInvocationPolicy.h"
#include "EventPolicies.h"
#include "Events.h"
#include "EventsDefinition.h"
#include "ManagedEventElement.h"
#include "WaitingEvent.h"
#include "OccurredEvent.h"
using namespace DataManager::Panorama::WorkflowEvents;

String XMLEventsDefinition::MAIN_NODE		= "EventsDefinition";

/************************************************************/
String XMLEventContext::MAIN_NODE 			= "Context";
String XMLEventContext::NAME_ATTRIBUTE		= "Name";

/************************************************************/
String XMLEvents::MAIN_NODE					= "Events";

/************************************************************/
String XMLEvent::MAIN_NODE 					= "Event";
String XMLEvent::ID_ATTRIBUTE				= "Id";

/************************************************************/
String XMLOccurredEvent::MAIN_NODE 			= "OccurredEvent";

/************************************************************/
String XMLWaitingEvent::MAIN_NODE 			= "WaitingEvent";

/************************************************************/
String XMLEventActions::MAIN_NODE			= "Actions";

/************************************************************/
String XMLScenarioEventAction::MAIN_NODE 			= "Action";
String XMLScenarioEventAction::TYPE_ATTRIBUTE		= "Type";
String XMLScenarioEventAction::ID_ATTRIBUTE			= "Id";
String XMLScenarioEventAction::PROCESSEXECUTE_TYPE	= "ProcessExecute";

/************************************************************/
String XMLEventPolicies::MAIN_NODE = "Policies";

/************************************************************/
String XMLEventConsumerPolicy::MAIN_NODE 				= "ConsumerPolicy";
String XMLEventConsumerPolicy::TYPE_ATTRIBUTE	= "Type";

/************************************************************/
String XMLEventInvocationPolicy::MAIN_NODE 			= "InvocationPolicy";
String XMLEventInvocationPolicy::TYPE_ATTRIBUTE	= "Type";

/************************************************************/
String XMLEventSource::MAIN_NODE					= "Source";
String XMLEventSource::TYPE_ATTRIBUTE		= "Type";
String XMLEventSource::NAME_ATTRIBUTE		= "Name";
String XMLEventSource::DATETIME_ATTRIBUTE	= "DateTime";

String XMLEventSource::WORKFLOW_TYPE = "Workflow";
String XMLEventSource::USER_TYPE	 = "User";
String XMLEventSource::SYSTEM_TYPE	 = "System";

/************************************************************/
String XMLManagedEventElement::MAIN_NODE					= "Managed";
String XMLManagedEventElement::DATETIME_ATTRIBUTE	= "DateTime";

String XMLManagedEventElement::STATUS_ATTRIBUTE	= "Status";

String XMLManagedEventElement::MANAGED_STATUS		= "Managed";
String XMLManagedEventElement::UNMANAGED_STATUS	= "Unmanaged";
String XMLManagedEventElement::MANAGING_STATUS		= "Managing";

/************************************************************/
String XMLWaitingActivity::MAIN_NODE						= "WaitingActivity";
String XMLWaitingActivity::PROCESSID_ATTRIBUTE		= "ProcessId";
String XMLWaitingActivity::NAME_ATTRIBUTE			= "Name";
String XMLWaitingActivity::DATETIME_ATTRIBUTE		= "DateTime";

/************************************************************/
String XMLWaitingActivities::MAIN_NODE					= "WaitingActivities";



