
#ifndef __BOS_THREAD_H__
#define __BOS_THREAD_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSRunnable.h"
using namespace bOS::Core;

namespace bOS
{
    namespace Core
    {
        class BOS_API Thread : public Runnable
        {
            public:

                /**
                 * Thread Priorities.
                 *
                 */
                enum ThreadPriority
                {
                    tpHigh = 10,
                    tpNormal = 5,
                    tpLow = 1
                };

                /**
                 * Thread States.
                 *
                 */
                enum ThreadState
                {
                    tsCreated,
                    tsRunning,
                    tsTerminated,
                    tsDetached
                };

                Thread( Runnable* runnable = NULL );

                virtual ~Thread();

                static void sleep( long millis );

                static void sleep( long millis, long nanos );

                static void yield();

                virtual void start();

                virtual void stop();

                virtual void join();

                virtual void setPriority( ThreadPriority priority );

                virtual ThreadPriority getPriority();

                virtual bool isRunning();

                virtual unsigned int getThreadID();

                static unsigned int getCurrentThreadID();

                //BOS_THREAD getHandle();       //ztg delete
                pthread_t getHandle();

                bool isDaemon() const;

                void setDaemon( bool bDaemon );

				static unsigned long getCurrentThreadId();

            protected:

                virtual void run();

                virtual void initialize();

                virtual void finalize();

            private:

                static Runnable*        m_Runnable;
                ThreadPriority          m_Priority;
                ThreadState             m_ThreadState;
                unsigned long           m_ThreadID;
                bool                    m_bDaemon;

                //BOS_THREAD              m_hThread;      //ztg delete
                pthread_t              m_hThread;

                void threadInit( ThreadPriority priority = tpNormal );
                void threadTerminate();

                static void* invokeRun(void* arg);

        };
    }
};

#endif


