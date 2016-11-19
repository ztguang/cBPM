#ifndef __BOS_SEMAPHORE_H__
#define __BOS_SEMAPHORE_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

namespace bOS
{
    namespace Core
    {
        class BOS_API Semaphore
        {
            public:

                Semaphore( String Name = "", int initialCount = 0, int maxCount = -1 );
                virtual ~Semaphore();
                virtual void wait();
                bool tryWait();
                virtual void post();

            protected:

                //SEMAPHORE  m_hSemaphore;      //ztg delete
                sem_t  m_hSemaphore;
                sem_t *sem_ptr;

            private:

                bool                _isNamed;
                String		        _Name;
                unsigned long       _OwnerThread;

                //Not implemented
                Semaphore( const Semaphore& cs );
                Semaphore& operator= ( const Semaphore& cs );
        };
    }
};

#endif



