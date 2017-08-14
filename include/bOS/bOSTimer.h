#ifndef __BOS_TIMER_H__
#define __BOS_TIMER_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSTime.h"

namespace bOS
{
    namespace Utils
    {
        class BOS_API Timer
        {
            public:
    
                Timer();

                virtual ~Timer();

                void start();

				long stop();

				long getTicks();

            private:
				Time tmStart;
				long dMilliseconds;
        };
    }
};

#endif



