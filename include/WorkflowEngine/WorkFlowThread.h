#ifndef _WORKFLOW_THREAD_H_
#define _WORKFLOW_THREAD_H_

#include "WorkflowManager.h"
#include "IWorkflow.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			/**
			* La classe deriva thread da bOS.
			* Ha la rsponsabilit?di creare thread di esecuzione 
			* per ogni richiesta di workflow.
			*
			* 
			*
			* @code
			* @endcode
			* @sa
			* @param
			* @throws
			* @see
			* @return
			* @returns
			*/
			class WorkFlowThread : public Thread
			{
			public:
				WorkFlowThread(	WorkflowManager* manager, IWorkflow* workflow)
				{
					wManager=manager;
					wWF = workflow;
				}

				virtual ~WorkFlowThread() {;}

				void run();
				void finalize() {;}
				void terminate() {;}

				int getResult() { return resultValue;}

				void setWorkflowId(const char* lID);

			private:
				WorkflowManager* wManager;
				IWorkflow*       wWF;

				int resultValue;

				String workflowId;
			};
		}
	}
}

#endif //_WORKFLOW_THREAD_H_


