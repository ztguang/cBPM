#include "bOS.h"
#include "bOSSemaphore.h"
using namespace bOS::Core;

#include "bOSSynchronizationException.h"
#include "bOSDeadLockException.h"
#include "bOSAlreadyInitializedException.h"
using namespace bOS::Exception;

#define MAX_SEM_VALUE   32767

Semaphore::Semaphore( String Name, int initialCount, int maxCount )
{
    #ifdef _BOS_ON_WIN32_
        _isNamed = false;
        _Name = Name;
        const Char* _theName = NULL;
        if (Name != "")
        {
            _isNamed = true;
            _theName = Name.c_str();
        }
        if (maxCount == -1)
            maxCount = MAX_SEM_VALUE;
        m_hSemaphore = CreateSemaphore((LPSECURITY_ATTRIBUTES)NULL, initialCount, maxCount, _theName);
        if (m_hSemaphore == NULL)
        {
            throw SynchronizationException( NO_SEMAPHORE_AVAILABLE );
        }
        if (GetLastError() == ERROR_ALREADY_EXISTS)
            throw AlreadyInitializedException();
        _OwnerThread = ::GetCurrentThreadId();

    #else // _PFC_ON_SOLARIS_ _PFC_ON_HP_
        if (Name == "")
        {
            int nResult = sem_init( &m_hSemaphore, 0, initialCount );
            if ( nResult != 0 )
            {
                String msg = "Semaphore non created. " + String( strerror(errno) );
                throw SynchronizationException( msg );
            }
            _isNamed = false;
        }
        else
        {
            if ( Name.find( '/' ) != String::npos )
                throw SynchronizationException( "Wrong semaphore name" );
            // Prepend a slash in front of the name
            String s = "/" + Name;
            sem_ptr = sem_open( s.c_str(), O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR, 0 );
            //if ( (int)&m_hSemaphore == -1 )     //ztg delete
            if ( sem_ptr == SEM_FAILED )
            {
	            String msg = "Semaphore non created. " + String( strerror(errno) );
                throw SynchronizationException( msg );
            }
            _Name = s;
            _isNamed = true;
        }
        _OwnerThread = pthread_self();
    #endif
}

Semaphore::~Semaphore()
{
    #ifdef _BOS_ON_WIN32_
        if ( m_hSemaphore != NULL )
            CloseHandle(m_hSemaphore);
	#else // _PFC_ON_SOLARIS_ _PFC_ON_HP_
        if ( !_isNamed )
        {
            int nResult = sem_destroy( &m_hSemaphore );
            if ( nResult != 0 )
                throw SynchronizationException();
        }
        else
        {
            sem_close( &m_hSemaphore );
            unsigned long callingThread = pthread_self();
            if( callingThread == _OwnerThread )
            {
                int nResult = sem_unlink( _Name.c_str() );
                if ( nResult == -1)
                {
                    String msg = "Semaphore Unlink Failed. " + String( strerror(errno) );
                    throw SynchronizationException( msg );
                }
            }
        }
    #endif
}

void Semaphore::wait()
{
    #ifdef _BOS_ON_WIN32_
        DWORD nResult = WaitForSingleObject( m_hSemaphore, INFINITE );
        if (nResult == WAIT_FAILED)
            throw SynchronizationException();
        else if (nResult == WAIT_ABANDONED)
            throw DeadLockException();
	#else // _PFC_ON_SOLARIS_ _PFC_ON_HP_
        int nResult = sem_wait( &m_hSemaphore );
        if ( nResult != 0 )
            throw SynchronizationException();
    #endif
}

bool Semaphore::tryWait()
{
    #ifdef _BOS_ON_WIN32_
        DWORD nResult = WaitForSingleObject( m_hSemaphore, 0 );
        if (nResult == WAIT_FAILED)
            return false;
        return nResult == WAIT_OBJECT_0;
	#else // _PFC_ON_SOLARIS_ _PFC_ON_HP_
        int nResult = sem_trywait( &m_hSemaphore );
        if ( nResult == 0 )
            return true;
        else
            return false;
    #endif
}

void Semaphore::post()
{
    #ifdef _BOS_ON_WIN32_
        BOOL bDone = ReleaseSemaphore(m_hSemaphore, 1, (LPLONG)NULL);
        if ( !bDone )
            throw SynchronizationException();
        int errCode = GetLastError();
        //TODO: check this error
        //if ( errCode == ERROR_TOO_MANY_POSTS )
	#else // _PFC_ON_SOLARIS_ _PFC_ON_HP_
        int nResult = sem_post( &m_hSemaphore );
        if ( nResult != 0 )
        {
	        String msg = "Semaphore post failed. " + String( strerror(errno) );
      	    throw SynchronizationException( msg );
        }
    #endif
}


