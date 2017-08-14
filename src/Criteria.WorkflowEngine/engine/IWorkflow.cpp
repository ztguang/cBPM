
#include "CommonDefines.h"

#include "IWorkflow.h"
using namespace WorkflowEngine::Criteria::Core;

IWorkflow::IWorkflow()
{
	_Status = STOPPED;
}

IWorkflow::~IWorkflow()
{
	//Don't remove. Is important for testing WorkFlow class destructor invocation.
	CM_CODEBLOCK(IWorkflow)
}
/*
Any IWorkflow::start()
{
	CM_CODEBLOCK(start)

    Any vRet;
	try
	{
		setStatus( STARTING );
        vRet = starting();
		setStatus( STARTED );
	}
	catch ( ... )
	{
		throw;
	}
    return vRet;
}

Any IWorkflow::stop()
{
	CM_CODEBLOCK(stop)
    Any vRet;
	try
	{
		setStatus( STOPPING );
		vRet = stopping();
		setStatus( STOPPED );
	}
	catch( ... )
	{
		throw;
	}
    return vRet;
}

Any IWorkflow::suspend()
{
    Any vRet;
	try
	{
		setStatus( SUSPENDING );
		vRet = suspending();
		setStatus( SUSPENDED );
	}
	catch( ... )
	{
		throw;
	}
    return vRet;
}
*/


int IWorkflow::start()
{
	CM_CODEBLOCK(start)

    int vRet;
	try
	{
		setStatus( STARTING );
        vRet = starting();
		setStatus( STARTED );
	}
	catch ( ... )
	{
		throw;
	}
    return vRet;
}

int IWorkflow::stop()
{
	CM_CODEBLOCK(stop)
    int vRet;
	try
	{
		setStatus( STOPPING );
		vRet = stopping();
		setStatus( STOPPED );
	}
	catch( ... )
	{
		throw;
	}
    return vRet;
}

int IWorkflow::suspend()
{
    int vRet;
	try
	{
		setStatus( SUSPENDING );
		vRet = suspending();
		setStatus( SUSPENDED );
	}
	catch( ... )
	{
		throw;
	}
    return vRet;
}

IWorkflow::WorkflowStatus IWorkflow::setStatus( WorkflowStatus status )
{
	CM_CODEBLOCK(setStatus)

	//TODO:
	/*
		i try-catch sono stati introdotti per individuare un'eccezione
		non gestita sul thread che esegue lo start.
	*/

	//TODO:
	//costantemente in errore sotto SUN.
    /*
	try
	{

		FastMutex::Lock locker(_mtxStatus);
	}
	catch ( ... )
	{
		CM_TRACE_ERROR( "Impossible to lock")
	}
	*/

    int we = gotoStatus( status, _Status );
	if ( we == 0 )
	{
		_Status = status;
	}
    else
	{
        //TODO: Throw exception
	}

	return _Status;
}

int IWorkflow::gotoStatus( WorkflowStatus newStatus, WorkflowStatus oldStatus )
{
    /*
    const String statusDescription[MAX_STATUS] = { "Stopping", "Stopped", "Starting", "Started", "Suspending", "Suspended" };

    const int statusTransition[MAX_STATUS][MAX_STATUS] =
    {
        //Stopping
        { JE_ALREADY_REQUEST_FOR_STOPPED, JE_ALREADY_STOPPED, JE_NOT_STARTED, JE_OK, JE_NOT_SUSPENDED, JE_OK },
        //Stopped
        { JE_OK, JE_ALREADY_STOPPED, JE_NOT_STARTED, JE_OK, JE_NOT_SUSPENDED, JE_OK },
        //Starting
        { JE_NOT_STOPPED, JE_OK, JE_ALREADY_REQUEST_FOR_STARTED, JE_ALREADY_REQUEST_FOR_STARTED, JE_NOT_SUSPENDED, JE_OK },
        //Started
        { JE_NOT_STOPPED, JE_OK, JE_OK, JE_ALREADY_STARTED, JE_NOT_SUSPENDED, JE_OK },
        //Suspending
        { JE_NOT_STARTED, JE_NOT_STARTED, JE_NOT_STARTED, JE_OK, JE_ALREADY_REQUEST_FOR_SUSPENDED,JE_ALREADY_REQUEST_FOR_SUSPENDED },
        //Suspended
        { JE_NOT_STARTED, JE_NOT_STARTED, JE_NOT_STARTED, JE_OK, JE_OK, JE_ALREADY_SUSPENDED }
    };

    return jeStatusTransition[newStatus][oldStatus];
    */

    return 0;
}

