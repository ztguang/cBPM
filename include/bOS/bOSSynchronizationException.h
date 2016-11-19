#ifndef __BOS_SYNCHRONIZATIONEXCEPTION_H__
#define __BOS_SYNCHRONIZATIONEXCEPTION_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSException.h"

namespace bOS
{
    namespace Exception
    {
        #define NO_MUTEX_AVAILABLE      "The system lacked the necessary resources (other than memory) to initialize another mutex."
		#define NO_SEMAPHORE_AVAILABLE	"The system ..."

		#define RC_OBJECT_NOT_CREATED	"The system ... RC_OBJECT_NOT_CREATED"
		#define RC_NOT_OWNER	"The system ... RC_NOT_OWNER"
		#define RC_LOCK_ERROR	"The system ... RC_LOCK_ERROR"
		#define RC_UNLOCK_ERROR	"The system ... RC_UNLOCK_ERROR"


        class BOS_API SynchronizationException : public BaseException
        {
            public:

                SynchronizationException(const String & message ): BaseException( message ) {}

                SynchronizationException() : BaseException( NO_MUTEX_AVAILABLE ) {}

                SynchronizationException( const String & message, const int lineNumber )
                    : BaseException(message, lineNumber) {}

                virtual ~SynchronizationException() {}
        };
    }
};

#endif


