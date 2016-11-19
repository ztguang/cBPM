#include "CommonDefines.h"

#include "EventsManager.h"
using namespace WorkflowEngine;

#include "EventsManagerThread.h"
using namespace WorkflowEngine::Criteria::Core;

#include "OccurredEvent.h"
using namespace DataManager::Panorama::WorkflowEvents;

#include "DataBaseHelper.h"
#include "DBException.h"
using namespace DataManager::DataBase;

#include "Workflow.h"
#include "WorkflowException.h"

#include "Tracer.h"

int MAX_NR_EVENT_TO_MANAGE = 10;

EventsManagerThread::EventsManagerThread(EventsManager* manager)
{
	assert(manager!=NULL);

	eventsManager = manager;

	bIsAlive = true;
}

EventsManagerThread::~EventsManagerThread()
{
}

void EventsManagerThread::run()
{
	CM_CODEBLOCK(EventsManagerThread::run)

	while ( bIsAlive )
	{
		bool bManageEvent = true;
		int iNrEventManage=0;
		while ( (bManageEvent) && (iNrEventManage<MAX_NR_EVENT_TO_MANAGE) )
		{
			WorkflowEngine::WorkflowActionList vWorkflows;
			OccurredEvent* occurredEvent= EventsManager::instance()->getAnEvent2Manage(vWorkflows);
			iNrEventManage++;

			if ( occurredEvent == NULL )
			{
				bManageEvent = false;
			}
			else
			{
				int iSize = vWorkflows.size();

				for ( int i=0; i<iSize; i++)
				{
					WorkflowAction wfAction = vWorkflows.at(i);
					CM_TRACE_INFO("Creating Workflow[" << wfAction.getWorkflowName() << "]")

					const char* acProcessID = wfAction.getProcessId();
					if (  strcmp(acProcessID,"") == 0) 
					{
						WorkflowProcesses::WorkflowProcess process;
						acProcessID = DataBaseHelper::instance()->createProcess(wfAction.getWorkflowName().c_str(), process).c_str();
					}

					Workflow* wf = new Workflow(acProcessID);

					if ( wfAction.getActivityName().length() > 0 ) 
					{
						Common::FormalParameters& parameters = occurredEvent->getParameters();
						Common::FormalParameters newParam;
						newParam.addParameter(parameters);
						wf->setBeginTask (wfAction.getActivityName(),newParam);
					}

					WorkFlowThread* pThread = NULL;
					try
					{
						pThread = WorkflowManager::instance()->executeJob( wf, true );
					}
					catch ( WorkflowException&) 
					{
						//TODO
					}
				}

				EventsManager::instance()->setEvent2Managed(occurredEvent);

			}
		}

		Thread::sleep (2000);
	}
}

void EventsManagerThread::stopEventManager()
{
	bIsAlive= false;
}


