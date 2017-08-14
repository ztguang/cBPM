#ifndef __BOS_MUTEX_H__
#define __BOS_MUTEX_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSSmartLocker.h"

namespace bOS
{
    namespace Core
    {
        class BOS_API Mutex
        {
            public:

                typedef SmartLocker<Mutex> Lock;

                Mutex( String Name = "" );

                virtual ~Mutex();

                void lock();

                void unlock();

                bool tryLock();

                MUTEX getHandle();

				String getName();

                void setName( String Name );

            protected:

                //MUTEX m_hMtx;     //ztg delete
                pthread_mutexattr_t  attr;         //ztg add
                pthread_mutex_t      mutex;       //ztg add

				String   sName;

        };
    }
};

#endif



