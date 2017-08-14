#ifndef __BOS_ALREADYINITIALIZEEXCEPTION_H__
#define __BOS_ALREADYINITIALIZEEXCEPTION_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSException.h"

namespace bOS
{
    namespace Exception
    {
        class BOS_API AlreadyInitializedException : public BaseException
        {
            public:

                AlreadyInitializedException(const String & message ): BaseException( message ) {}

                AlreadyInitializedException() : BaseException() {}

                AlreadyInitializedException( const String & message, const int lineNumber )
                    : BaseException(message, lineNumber) {}

                virtual ~AlreadyInitializedException() {}
        };
    }
};

#endif


