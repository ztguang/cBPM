
#ifndef __BOS_GUID_H__
#define __BOS_GUID_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSDateTime.h"

namespace bOS
{
    namespace Utils
    {
        class BOS_API UniqueID
        {
            public:
    
                virtual ~UniqueID();

                static String getNewValue();

            private:
				UniqueID();
                
        };
    }
};

#endif



