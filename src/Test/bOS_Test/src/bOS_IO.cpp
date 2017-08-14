#include "bOS/bOS.h"
#include "bOS/bOSFileSystem.h"
using namespace bOS::IO;

#include "bOS/bOSString.h"
using namespace bOS::CoreString;

void ls(const char* sDir, const char* acExt)
{
	FilesList vFiles;
	FileSystem::ls (sDir, vFiles, acExt);

	for ( int i=0; i<vFiles.size();i++)
	{
		cout << vFiles[i] << endl;
	}

}