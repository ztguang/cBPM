#ifndef _JNI_INVOKER_H_
#define _JNI_INVOKER_H_

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSString.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

namespace bOS
{
	namespace VM 
	{
		namespace Java
		{
			class BOS_API JniInvoker
			{
			public:
				JniInvoker();
				JniInvoker(const String& sClassPathVariableName);
				~JniInvoker();

				void createJVM();
				void addClassPath(const String& sPath);
				void addClassPathFromEnvironmentVariableName(const String& sClassPathVariableName);
				void execute(const String& sClassName, const String& sMethodName, int argLen, String sArgs[]);
				void destroyJVM();

			private:
				StringBuffer sClassPath;
			};
		}
	}
}

#endif //_JNI_INVOKER_H_