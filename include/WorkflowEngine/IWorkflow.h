#ifndef __IWORKFLOW_H__
#define __IWORKFLOW_H__


//TO_BE_EXPORTED

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			/**
			* La classe offre una interfaccia per la gestione degli stati di workflow 
			* (si tratta di stati interni) 
			*
			* Lo stato ?identificato dal tipo enumerato WorkflowStatus
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
			class IWorkflow 
			{
				public:

					enum WorkflowStatus
					{
						STOPPING = 0,
						STOPPED,
						STARTING,
						STARTED,
						SUSPENDING,
						SUSPENDED,
						MAX_STATUS
					};

					IWorkflow();
					virtual ~IWorkflow();

					//Any start();
					//Any stop();
					//Any suspend();
					int start();
					int stop();
					int suspend();

					const char* getWorkflowID() { return workflowId.c_str();}

					void setWorkflowId(const char* ID) { workflowId = ID;}


				protected:

					WorkflowStatus setStatus( WorkflowStatus status );

					//virtual Any stopping() = 0;
					//virtual Any starting() = 0;
					//virtual Any suspending() = 0;
					virtual int stopping() = 0;
					virtual int starting() = 0;
					virtual int suspending() = 0;

				private:

					int gotoStatus( WorkflowStatus newStatus, WorkflowStatus oldStatus );

					WorkflowStatus  _Status;
					Mutex       _mtxStatus;

					String workflowId;
			};
		}
	}
}

#endif 
