#include "CommonDefines.h"

#include "bOSMutex.h"
using namespace bOS::Core;

#include "bOSSynchronizationException.h"
using namespace bOS::Exception;


Mutex::Mutex( String Name )
{
	//setName(Name);

    pthread_mutexattr_init (&attr);
    if (pthread_mutex_init(&mutex, &attr))
    {
        //return RC_OBJECT_NOT_CREATED;
        throw SynchronizationException(RC_OBJECT_NOT_CREATED);
    }
/*
    m_hMtx = CreateMutex( NULL, FALSE, Name.c_str() );
    if ( m_hMtx == NULL )
	{
        throw SynchronizationException();
	}
*/
}

Mutex::~Mutex()
{
        if (pthread_mutex_destroy(&mutex) == EBUSY)
            //return RC_NOT_OWNER;
            throw SynchronizationException( RC_NOT_OWNER );
	/*
    if ( m_hMtx != NULL )
	{
        CloseHandle( m_hMtx );
	}
	*/
}

void Mutex::lock()
{
    if ( pthread_mutex_lock(&mutex))
        //return RC_LOCK_ERROR;
        throw SynchronizationException( RC_LOCK_ERROR );
/*
    DWORD nResult = WaitForSingleObject( m_hMtx, INFINITE );
    if (nResult == WAIT_FAILED)
	{
        throw SynchronizationException();
	}
*/
}

void Mutex::unlock()
{
    if ( pthread_mutex_unlock(&mutex))
        //return RC_UNLOCK_ERROR;
        throw SynchronizationException( RC_UNLOCK_ERROR );
/*
    BOOL bResult = ReleaseMutex( m_hMtx );
    if ( !bResult )
	{
        throw SynchronizationException();
	}
*/
}

bool Mutex::tryLock()
{
    if ( pthread_mutex_lock(&mutex))
        //return RC_LOCK_ERROR;
        throw SynchronizationException( RC_LOCK_ERROR );
/*
    DWORD nResult = WaitForSingleObject( m_hMtx, 0 );
    switch ( nResult )
    {
    case WAIT_OBJECT_0:
	    return true;
    case WAIT_TIMEOUT:
	    return false;
    default:
	    throw SynchronizationException();
    }
*/
}

String Mutex::getName()
{
    return sName;
}

void Mutex::setName( String Name )
{
    sName = Name;
}

