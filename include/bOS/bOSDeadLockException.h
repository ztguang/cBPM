#ifndef __BOS_DEADLOCKEXCEPTION_H__
#define __BOS_DEADLOCKEXCEPTION_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSException.h"

namespace bOS
{
    namespace Exception
    {
        class BOS_API DeadLockException : public BaseException
        {
            public:

                DeadLockException(const String & message ): BaseException( message ) {}

                DeadLockException() : BaseException() {}

                DeadLockException( const String & message, const int lineNumber )
                    : BaseException(message, lineNumber) {}

                virtual ~DeadLockException() {}
        };
    }
};

#endif


