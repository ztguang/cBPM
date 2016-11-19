#ifndef __BOS_InterruptedException_H__
#define __BOS_InterruptedException_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSException.h"

namespace bOS
{
    namespace Exception
    {
        #define RUNTIME_ERROR       "A System runtime exception has occurred. Boh - you probably already knew that !"
        #define UNLOAD_FAILED       "Failed to unload the libary - Probably alread unloaded."
        #define ENV_DEFAULT_ERROR   "Error working with the registry : "
        #define INVALID_PROCESS     "The process specified in input does not refer to a valid process."
		#define OUT_OF_MEMORY           "No more memory is available for this process."
        #define NO_MEMORY_FOR_MUTEX     "Insufficient memory exists to initialize the mutex."
		#define THREAD_INTERRUPTED      "......................"
		#define ILLEGAL_ARGUMENT   "Illegal argument. Please contact an administrator."
		#define ILLEGAL_STATE       "Illegal state Exception. Please contact an administrator."
        #define CONCURRENT_MODIFY   "Concurrent modification exception. Please contact an administrator."


        class BOS_API InterruptedException : public BaseException 
        {
            public:

                InterruptedException(const String & message ): BaseException( message ) {}

                InterruptedException() : BaseException( RUNTIME_ERROR ) {}

                InterruptedException( const String & message, const int lineNumber ) 
                    : BaseException(message, lineNumber) {}

                virtual ~InterruptedException() {}
        };
    }
};

#endif


