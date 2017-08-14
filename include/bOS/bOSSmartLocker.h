
#ifndef __BOS_SMARTLOCKER_H__
#define __BOS_SMARTLOCKER_H__

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSNullArgumentException.h"
using namespace bOS::Exception;

namespace bOS
{
    namespace Core
    {
        template<typename T> class BOS_API SmartLocker
        {
            public:

                SmartLocker( T& lock ) : m_Lock(lock), m_bLocked(false)
                {
                    if ( &lock == NULL )
					{
                        throw NullArgumentException();
					}
                    m_Lock.lock();
                    m_bLocked = true;
                }


                SmartLocker( T& lock, bool bInitialLock ) : m_Lock(lock), m_bLocked(false)
                {
                    if ( &lock == NULL ) 
					{
                        throw NullArgumentException();
					}

                    if (bInitialLock)
                    {
                        m_Lock.lock();
                        m_bLocked = true;
                    }
                }

                virtual ~SmartLocker()
                {
                    if (m_bLocked)
                    {
                        m_Lock.unlock();
                    }
                }

			private:

                void lock()
                {
	                if (!m_bLocked)
	                {
		                m_Lock.lock();
		                m_bLocked = true;
	                }
                }

                void unlock()
                {
                    if (m_bLocked)
                    {
                        m_Lock.unlock();
                        m_bLocked = false;
                    }
                }

                T&          m_Lock;
                bool        m_bLocked;
        };
    }
};

#endif



