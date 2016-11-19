#ifndef __BOS_RUNNABLE_H__
#define __BOS_RUNNABLE_H__

//TO_BE_EXPORTED

#include "bOS.h"

namespace bOS
{
    namespace Core
    {
        class BOS_API Runnable 
        {
            public:

                virtual void run() = 0;
        };
    }
}

#endif


