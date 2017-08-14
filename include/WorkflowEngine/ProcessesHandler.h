#ifndef _PROCESSES_HANDLER_H_
#define _PROCESSES_HANDLER_H_

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSMutex.h"

#include "bOSDateTime.h"

#include "WorkflowProcess.h"
using namespace DataManager::Panorama::WorkflowProcesses;

namespace DataManager
{
	namespace DataBase
	{
		class ProcessHandler
		{
		public:
			ProcessHandler(WorkflowProcess* process);
			~ProcessHandler();

			const char* getProcessId() {return process->getProcessId();}
			WorkflowProcess* getProcess() { return process;}
			void setProcess(WorkflowProcess* processValue) { process = processValue;}

			void incrementUser();
			bool decrementUser(bool bWithoutExpired);
			long getNrUser() { return lNrUsers;}

		private:

			long lNrUsers;
			WorkflowProcess* process;
			bOS::Utils::DateTime dtCreation;

			bool expired();
			const static int EXPIRED_SECONDS = 3600;

			friend class ProcessesHandler;
		};

		typedef vector<ProcessHandler*> ProcessHandlerList;

		class ProcessesHandler
		{
		public:
			ProcessesHandler();
			~ProcessesHandler();

			void addProcess(WorkflowProcess* process);
			void releaseProcess(const char* processId, bool bForceDeleteProcess);
			WorkflowProcess* loadProcess (const char* processId);

		private:
			ProcessHandler* getProcess(const char* processId);

			ProcessHandlerList vProcess;
			bOS::Core::Mutex mtxProcessList;
		};
	}
}

#endif //_PROCESSES_HANDLER_H_