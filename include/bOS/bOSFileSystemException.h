
#ifndef __BOS_FILESYSTEMEXCEPTION_H__
#define __BOS_FILESYSTEMEXCEPTION_H__

//TO_BE_EXPORTED

#include "bOS.h"
#include "bOSException.h"

namespace bOS
{
    namespace Exception
    {
        #define PATH_NOTFOUND            "Path Not Found."
		#define READ_ERROR				 "Impossible to read."

        class BOS_API FileSystemException : public BaseException 
        {
            public:

                FileSystemException(const String & message ): BaseException( message ) {}

                FileSystemException() : BaseException( PATH_NOTFOUND ) {}

                FileSystemException( const String & message, const int lineNumber ) 
                    : BaseException(message, lineNumber) {}

                virtual ~FileSystemException() {}
        };
    }
};

#endif











