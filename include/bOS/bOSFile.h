#ifndef __BOS_FILE_H__
#define __BOS_FILE_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSString.h"

namespace bOS
{
    namespace IO
    {
        class BOS_API File
        {
            public:

                File(const char* acFileName);

                virtual ~File();

				const char* getFileName() { return sFileName.c_str();}

            protected:

            private:
				bOS::CoreString::String sFileName;

        };
    }
};

#endif //__BOS_FILESYSTEM_H__


