
#ifndef __BOS_NULLARGUMENTEXCEPTION_H__
#define __BOS_NULLARGUMENTEXCEPTION_H__

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSException.h"

namespace bOS
{
    namespace Exception
    {
        #define NULL_POINTER            "Null pointer Exception"

        class BOS_API NullArgumentException : public BaseException 
        {
            public:

                NullArgumentException(const String & message ): BaseException( message ) {}

                NullArgumentException() : BaseException( NULL_POINTER ) {}

                NullArgumentException( const String & message, const int lineNumber ) 
                    : BaseException(message, lineNumber) {}

                virtual ~NullArgumentException() {}
        };
    }
};

#endif











