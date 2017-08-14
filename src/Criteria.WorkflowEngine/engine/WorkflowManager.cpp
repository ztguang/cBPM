#include "CommonDefines.h"

#include "WorkflowManager.h"
#include "WorkflowException.h"
#include "WorkFlowThread.h"
using namespace WorkflowEngine::Criteria::Core;

#include "bOSRuntimeException.h"
#include "bOSSynchronizationException.h"
using namespace bOS::Exception;

#include "bOSUniqueID.h"

WorkflowManager* WorkflowManager::_instance = NULL;

WorkflowManager* WorkflowManager::instance()
{
	if ( _instance == NULL )
	{
		_instance = new WorkflowManager();
	}

	return _instance;
}

void WorkflowManager::deinstance()
{
	if ( _instance != NULL )
	{
		delete _instance;
	}

	_instance=NULL;
}

WorkflowManager::WorkflowManager()
{
}

WorkflowManager::~WorkflowManager()
{
	WorkflowList::iterator iWL;    
	for ( iWL = wfList.begin(); iWL < wfList.end(); iWL++)
	{
		(*iWL)->stop();
		delete (*iWL);
	}
	wfList.clear();
}

WorkflowList WorkflowManager::getList()
{
	Mutex::Lock locker(mtxWFList);
	return wfList;
}

void WorkflowManager::add( IWorkflow* wf )
{
    Mutex::Lock locker(mtxWFList);
	wfList.push_back( wf );
}

void WorkflowManager::remove( const char* workflowID )
{
    Mutex::Lock locker(mtxWFList);

	WorkflowList::iterator iWL;
	for ( iWL = wfList.begin(); iWL < wfList.end(); iWL++ )
	{
		if ( strcmp((*iWL)->getWorkflowID(),workflowID) == 0  ) 
		{			
			delete (*iWL);
			wfList.erase( iWL );
			return;
		}
	}
    throw WorkflowException( WE_NOT_FOUND );
}

IWorkflow* WorkflowManager::find( const char* workflowID )
{
	IWorkflow* wf = NULL;
    Mutex::Lock locker(mtxWFList);

	WorkflowList::iterator iWL;    
	for ( iWL = wfList.begin(); iWL < wfList.end(); iWL++)
	{
		if ( strcmp((*iWL)->getWorkflowID(),workflowID) == 0 ) 
		{
			wf= (*iWL);
			break;
		}
	}	
	return wf;
}

IWorkflow* WorkflowManager::start( const char* workflowID )
{
	CM_CODEBLOCK(start)

	IWorkflow* wf = find( workflowID );

	if ( wf == NULL) 
	{
	    throw WorkflowException( WE_NOT_FOUND );
	}
    
    wf->start();

	return wf;
}

IWorkflow* WorkflowManager::stop( const char* workflowID )
{
	IWorkflow* wf = find( workflowID );
	if ( wf == NULL) 
	    throw WorkflowException( WE_NOT_FOUND );
    
    wf->stop();
	return wf;
}

IWorkflow* WorkflowManager::suspend( const char* workflowID )
{
	IWorkflow* wf = find( workflowID );
	if ( wf == NULL) 
	    throw WorkflowException( WE_NOT_FOUND );
    
    wf->suspend();
	return wf;
}

WorkFlowThread* WorkflowManager::executeJob( IWorkflow* pWF, bool bDetach )
{
	CM_CODEBLOCK(executeJob)

	WorkFlowThread* pThread = NULL;

	try 
	{
		pThread= new WorkFlowThread(this, pWF);

		//Setting WorkflowId
		{
			Mutex::Lock locker(mtxWFList);
			pThread->setWorkflowId(bOS::Utils::UniqueID::getNewValue().c_str());
		}
		
		if ( bDetach ) 
		{
			pThread->setDaemon(true);
			pThread->start();
		}
		else
			pThread->run();
			
		return pThread;
	}
    catch ( SynchronizationException& se)
    {
		delete pThread;
		CM_TRACE_ERROR( "Error on start Thread[" << se.getMessage() << "]")
	    throw WorkflowException( WE_CANT_START_WORKFLOW );
    }
    catch ( RuntimeException& se)
    {
		delete pThread;
		CM_TRACE_ERROR( "Error on start Thread[" << se.getMessage() << "]")
	    throw WorkflowException( WE_CANT_START_WORKFLOW );

	}
}



