#include "CommonDefines.h"

#include "bOSThread.h"
using namespace bOS::Core;

#include "bOSRuntimeException.h"
#include "bOSInterruptedException.h"

#include "bOSSynchronizationException.h"
using namespace bOS::Exception;

#include "bOSStringUtils.h"
using namespace bOS::CoreString;

Runnable* Thread::m_Runnable;

Thread::Thread( Runnable* runnable )
{
    m_Runnable      = runnable;
    m_Priority      = tpNormal;
    m_ThreadState   = tsCreated;
    m_ThreadID      = 0;
    //m_hThread       = NULL;           //ztg delete
    m_bDaemon       = false;

	m_bDaemon = false;
	m_Priority = tpNormal;
}

Thread::~Thread()
{
    if ( !m_bDaemon )
    {
        try
        {
            this->threadTerminate();
        }
        catch ( ... )
        {
            //No action...
        }
    }
}

void Thread::sleep( long millis )
{
	Thread::sleep( millis, 0 );
}

void Thread::sleep( long millis, long nanos )
{
    #ifdef _BOS_ON_WIN32_
	    if ( nanos > 500000 )
		    millis++;
	    if ( SleepEx(millis, TRUE) == WAIT_IO_COMPLETION )
		    throw RuntimeException(THREAD_INTERRUPTED);
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        struct timespec tv;
	    tv.tv_sec = millis/1000;
	    tv.tv_nsec = (millis% 1000)*1000000 + nanos;
	    if( nanosleep(&tv, 0) < 0 )
	    {
		    if (errno == EINTR)
			    throw InterruptedException();
            else
			    throw RuntimeException();
	    }
    #endif
}

void Thread::yield()
{
    #ifdef _BOS_ON_WIN32_
    //TODO:
    //SwitchToThread();
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        sched_yield();
    #endif
}

void Thread::start()
{
    /**
     * This method is synchronized for a number of reasons:
     * 1) It must check the state to ensure that it is not started multiple times
     * 2) It must set the threadId, which though imutable after the thread is started,
     *    could be obtained by the child thread before this thread regains control.
     */

	if ( m_ThreadState != tsCreated )
        throw RuntimeException(ILLEGAL_STATE);

    threadInit( m_Priority );
}

void Thread::stop()
{
    #ifdef _BOS_ON_WIN32_
        ExitThread(0);
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        pthread_exit( NULL );
    #endif
}

void Thread::join()
{
    #ifdef _BOS_ON_WIN32_
        DWORD nResult = WaitForSingleObjectEx( m_hThread, INFINITE, TRUE );
	    switch (nResult)
	    {
        case WAIT_IO_COMPLETION:
		    throw RuntimeException(THREAD_INTERRUPTED);
	    case WAIT_TIMEOUT:
	    case WAIT_OBJECT_0:
		    break;
	    default:
            {
                DWORD errorCode = GetLastError();
                throw RuntimeException( StringUtils::getErrorString( errorCode ) );
            }
            break;
	    }
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
	    //POSIX threads do not allow a timeout on pthread_join, so we have to
	    //use something else instead.
        pthread_join( m_hThread, NULL );
    #endif
}

void Thread::setPriority( ThreadPriority priority )
{
	if ( priority < tpLow || priority > tpHigh )
		throw RuntimeException(ILLEGAL_ARGUMENT);

	if ( m_Priority != priority )
	{
		m_Priority = priority;
		if ( m_ThreadState != tsTerminated )
		{
            #ifdef _BOS_ON_WIN32_
	            // Translate the priority into something meaningful for Win32
	            static int PriorityTable[10] =
	            { THREAD_PRIORITY_IDLE,
	              THREAD_PRIORITY_LOWEST,
	              THREAD_PRIORITY_BELOW_NORMAL,
	              THREAD_PRIORITY_BELOW_NORMAL,
	              THREAD_PRIORITY_NORMAL,
	              THREAD_PRIORITY_ABOVE_NORMAL,
	              THREAD_PRIORITY_ABOVE_NORMAL,
	              THREAD_PRIORITY_ABOVE_NORMAL,
	              THREAD_PRIORITY_HIGHEST,
	              THREAD_PRIORITY_TIME_CRITICAL
	            };
                BOOL bResult = SetThreadPriority( m_hThread, PriorityTable[m_Priority-1] );
                if ( !bResult )
                    throw RuntimeException();
            #endif

            #ifdef _BOS_ON_SOLARIS_
            #endif
		}
	}
}

Thread::ThreadPriority Thread::getPriority()
{
    return m_Priority;
}

bool Thread::isRunning()
{
    return (m_ThreadState == tsRunning);
}

unsigned int Thread::getThreadID()
{
	// Even though the thread id is immutable, there is a possible race condition
	// between the creator thread setting the id and this thread executing.
	// By synchronizing, we ensure that we obtain the correct value as set by
	// Thread::start()
    return m_ThreadID;
}

unsigned int Thread::getCurrentThreadID()
{
    #ifdef _BOS_ON_WIN32_
        return GetCurrentThreadId();
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        return pthread_self();
    #endif
}

//BOS_THREAD Thread::getHandle()        //ztg delete
pthread_t Thread::getHandle()
{
    return m_hThread;
}

bool Thread::isDaemon() const
{
    return m_bDaemon;
}

void Thread::setDaemon( bool bDaemon )
{
	if ( m_ThreadState != tsCreated )
        throw RuntimeException(ILLEGAL_STATE);

	m_bDaemon = bDaemon;
}

void Thread::run()
{
}

void Thread::initialize()
{
}

void Thread::finalize()
{
}

void Thread::threadInit( ThreadPriority priority )
{
    #ifdef _BOS_ON_WIN32_
	    // Under Win32, we create the thread initially suspended.  This is so that we can set
	    // the thread HANDLE, and not have to synchromize access to the handle when the
	    // thread starts to execute.
        m_hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread::invokeRun,
                (void*)this, CREATE_SUSPENDED, &m_ThreadID);
        if ( m_hThread == INVALID_HANDLE_VALUE )
            throw RuntimeException();
        //Map our priority to the real system priority
        this->setPriority( priority );
        //Resume the thread
        if ( ResumeThread(m_hThread) == (DWORD)-1 )
            throw RuntimeException();
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        int nResult = 0;
	    //nResult = pthread_create( &m_hThread, NULL, (PTHREAD_START_ROUTINE)Thread::invokeRun, (void*)this );  //ztg delete
	    nResult = pthread_create( &m_hThread, NULL, Thread::invokeRun, (void*)this );
        if( nResult != 0 )
            throw RuntimeException();
        m_ThreadID = m_hThread;
		if ( m_bDaemon )
		{
			nResult = pthread_detach(m_hThread);
			if( nResult != 0 )
	            throw RuntimeException();
		}

    #endif
}

void Thread::threadTerminate()
{
    #ifdef _BOS_ON_WIN32_
        BOOL bTerminated = TerminateThread( (HANDLE)m_hThread, 0 );
        if ( !bTerminated )
        {
            DWORD errorCode = GetLastError();
            if ( errorCode != ERROR_INVALID_PARAMETER )
                throw SynchronizationException( StringUtils::getErrorString( errorCode ) );
        }
        if (m_hThread)
            CloseHandle( (HANDLE)m_hThread );
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
		int nResult = pthread_cancel( m_hThread );
			if( nResult != 0 )
			{
				if ( nResult != ESRCH )
					throw SynchronizationException( StringUtils::getErrorString( nResult ) );
			}
    #endif
}

void* Thread::invokeRun(void* arg)
{
    //arg is a pointer to the Thread object
	assert(arg);

	//Hold a reference to the Thread ptr for the duration of the thread.
    //Note, this reference is explicity released in cancel().
    //SmartPointer<Thread> rpThread = (Thread*)arg;

	try
	{

		if ( m_Runnable != NULL )
		{
			m_Runnable->run();
		}
		else
		{
			Thread* rpThread = (Thread*)arg;

			rpThread->m_ThreadState = tsRunning;
			rpThread->initialize();

			rpThread->run();
			rpThread->finalize();
			rpThread->m_ThreadState = tsTerminated;
		}
	}
	catch (...)
	{
		cout << "An unknow error occurred in Thread." << endl;
	}

    return NULL;
}

unsigned long Thread::getCurrentThreadId()
{
	#ifdef _BOS_ON_WIN32_
		return GetCurrentThreadId();
	#else
		return pthread_self();
	#endif

}

