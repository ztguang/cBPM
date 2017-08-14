
#ifndef __BOS_FILESYSTEM_H__
#define __BOS_FILESYSTEM_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSString.h"
#include "bOSStringBuffer.h"

namespace bOS
{
    namespace IO
    {
		typedef BOS_API vector<bOS::CoreString::String> FilesList;

		enum FileAttribute 
        {
            Exists      = 0x01,
	        RegularFile = 0x02,
	        Directory   = 0x04,
	        Hidden      = 0x08,
			ReadOnly    = 0x10 
        };

        class BOS_API FileSystem
        {
            public:

                FileSystem();

                virtual ~FileSystem();

				static void ls(const bOS::CoreString::String& sDir, FilesList& files, const char* acExtension);

				//deprecated
				static bOS::CoreString::String getStringFile(const bOS::CoreString::String& sFile);

				static void getStringFileBinary(const char* acFile, bOS::CoreString::StringBuffer& );

				static void getStringFile(const char* acFile, bOS::CoreString::StringBuffer&);

				//static void saveStringFile(const char* acFile, bOS::CoreString::String&);	//ztg delete
				static void saveStringFile(const char* acFile, bOS::CoreString::String);

				static bOS::CoreString::String getFileName(const bOS::CoreString::String& sPath, bool bRemoveExtention=false);

				static int getFileAttributeFlags( const bOS::CoreString::String& sFile );

				static bool existFile(const bOS::CoreString::String& sFile);
				
				static void deleteFile(const bOS::CoreString::String& sFile);

            protected:

            private:

        };
    }
};

#endif //__BOS_FILESYSTEM_H__


