#include "CommonDefines.h"

#include "ProcessesHandler.h"
using namespace DataManager::DataBase;

using namespace bOS::Core;

ProcessHandler::ProcessHandler(WorkflowProcess* processValue)
{
	CM_CODEBLOCK(ProcessHandler::ProcessHandler)
	process=processValue;
	lNrUsers=1;

	dtCreation = bOS::Utils::DateTime::getCurrentDateTime();
}

ProcessHandler::~ProcessHandler()
{
	CM_CODEBLOCK(ProcessHandler::~ProcessHandler)

	if ( process != NULL )
	{
		delete process;
		process = NULL;
	}
}

void ProcessHandler::incrementUser()
{
	CM_CODEBLOCK(ProcessHandler::incrementUser)

	lNrUsers++;
}

bool ProcessHandler::expired()
{
	if ( lNrUsers == 0) 
	{
		bOS::Utils::DateTime dt = bOS::Utils::DateTime::getCurrentDateTime();

		int iSeconds = dtCreation.secondsTo(dt);

		if ( iSeconds > ProcessHandler::EXPIRED_SECONDS )
			return true;
	}

	return false;

}

bool ProcessHandler::decrementUser(bool bWithoutExpired)
{
	CM_CODEBLOCK(ProcessHandler::decrementUser)

	//assert(lNrUsers>0);
	
	lNrUsers--;
	
	if ( bWithoutExpired )
	{
		delete process;
		process = NULL;
		return true;
	}
	else if (  this->expired() )
	{
		delete process;
		process = NULL;
		return true;
	}

	return false;
}


ProcessesHandler::ProcessesHandler()
{
	CM_CODEBLOCK(ProcessesHandler::ProcessesHandler)
}

ProcessesHandler::~ProcessesHandler()
{
	CM_CODEBLOCK(ProcessesHandler::~ProcessesHandler)

	Mutex::Lock locker(mtxProcessList);

	unsigned int uiSize = vProcess.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		delete vProcess.at(i);
	}
}

ProcessHandler* ProcessesHandler::getProcess(const char* processId)
{
	CM_CODEBLOCK(ProcessesHandler::getProcess)

	Mutex::Lock locker(mtxProcessList);

	unsigned int uiSize = vProcess.size();
	for ( unsigned int i=0; i<uiSize; i++)
	{
		ProcessHandler* handler = vProcess.at(i);

		if ( strcmp(handler->getProcessId(),processId)== 0 ) 
		{
			return handler;
		}
	}

	return NULL;
}

void ProcessesHandler::addProcess(WorkflowProcess* process)
{
	CM_CODEBLOCK(ProcessesHandler::addProcess)

	Mutex::Lock locker(mtxProcessList);
	vProcess.push_back(new ProcessHandler(process));
}

void ProcessesHandler::releaseProcess(const char* processId, bool bDeleteProcess)
{
	CM_CODEBLOCK(ProcessesHandler::releaseProcess)

	Mutex::Lock locker(mtxProcessList);

	bool bNotEnd = true;

	while ( bNotEnd )
	{
		bNotEnd = false;

		ProcessHandlerList::iterator i= vProcess.begin();
		//modify by mfarina on 11/08/2009
		//for ( ; (i!=vProcess.end()) && (!bNotEnd); i++)
		for ( ; i!=vProcess.end(); i++)
		{
			ProcessHandler* handler = *i;

			if ( strcmp(handler->getProcessId(),processId)==0 ) 
			{
				if (handler->decrementUser(bDeleteProcess) )
				{
					CM_TRACE_DEBUG("Process[" << processId << " removed from processlist.")
					delete handler;
					vProcess.erase (i);
					bNotEnd = true;
					break;
				}
			}
			else if ( handler->expired() )
			{
				CM_TRACE_DEBUG("Process[" << processId << " removed from processlist.")
				delete handler;
				vProcess.erase (i);
				bNotEnd = true;
				break;
			}
		}
	}
}

WorkflowProcess* ProcessesHandler::loadProcess (const char* processId)
{
	CM_CODEBLOCK(ProcessesHandler::loadProcess)

	ProcessHandler* handler = this->getProcess(processId);

	Mutex::Lock locker(mtxProcessList);
	if ( handler != NULL )
	{
		handler->incrementUser();
		return handler->getProcess();
	}

	return NULL;
}