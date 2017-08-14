#include "CommonDefines.h"

#include "jni.h"

#ifdef WIN32
	#define PATH_SEPARATOR ';'
#else
	#define PATH_SEPARATOR ':'
#endif

#define USER_CLASSPATH "."

#include "JniInvoker.h"
using namespace bOS::VM::Java;

#include "bOS.h"
#include "bOSSystem.h"
using namespace bOS::CoreSystem;

#include "Tracer.h"

JavaVM* jvm = 0;
JNIEnv* env = 0;

JniInvoker::JniInvoker()
{
}

JniInvoker::JniInvoker(const String& sClassPathVariableName)
{
	CM_CODEBLOCK(JniInvoker::JniInvoker)
	string sPath = System::getEnvironmentVariable(sClassPathVariableName);

	CM_TRACE_DEBUG("Adding [" << sClassPathVariableName << "] [" << sPath << "]")
	sClassPath.append(sPath);

}

JniInvoker::~JniInvoker()
{
	CM_CODEBLOCK(JniInvoker::~JniInvoker)
}

void JniInvoker::addClassPath(const String& sPath)
{
	CM_CODEBLOCK(JniInvoker::addClassPath)

	static bool bNotFirst = false;

	if ( bNotFirst )
	{
		sClassPath.append(PATH_SEPARATOR);
	}
	else
		bNotFirst = true;

	sClassPath.append(sPath);

}

void JniInvoker::addClassPathFromEnvironmentVariableName(const String& sClassPathVariableName)
{
	sClassPath.append(System::getEnvironmentVariable(sClassPathVariableName));
}

void JniInvoker::createJVM()
{
	CM_CODEBLOCK(JniInvoker::createJVM)

	if ( env != 0 )
	{
		return;
	}

	jint res;
#ifdef JNI_VERSION_1_6
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];

	String sPath = "-Djava.class.path=";
	sPath += sClassPath.getData();
    options[0].optionString = (char*)sPath.c_str();
    vm_args.version = 0x00010006;
    vm_args.options = options;
    vm_args.nOptions = 1;
    vm_args.ignoreUnrecognized = JNI_TRUE;
/* Create the Java VM */
	try
	{
		res = NULL;//JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	}
	catch ( ...)
	{
		CM_TRACE_ERROR("Unknow Err on JNI_CreateJavaVM")
	}
#else
    JDK1_1InitArgs vm_args;
    char classpath[1024];
    vm_args.version = 0x00010001;
    JNI_GetDefaultJavaVMInitArgs(&vm_args);
    /* Append USER_CLASSPATH to the default system class path */
    sprintf(classpath, "%s%c%s",
            vm_args.classpath, PATH_SEPARATOR, USER_CLASSPATH);
    vm_args.classpath = classpath;
/* Create the Java VM */
    res = JNI_CreateJavaVM(&jvm, &env, &vm_args);
#endif /* JNI_VERSION_1_2 */

    if (res < 0)
	{
		CM_TRACE_ERROR("Can't create Java VM\n")
		//TODO:
		//throw Exception
    }
	else
	{
		CM_TRACE_INFO("JVM Created!")
	}

}

void JniInvoker::execute(const String& sClassName, const String& sMethodName, int argLen, String sArgs[])
{
	CM_CODEBLOCK(JniInvoker::execute)

    jclass cls;
    cls = env->FindClass(sClassName.c_str());
    if (cls == 0)
	{
		CM_TRACE_ERROR("Can't find Prog class\n")
		//TODO:
		//throw Exception
    }

	jmethodID mid;
    mid = env->GetStaticMethodID(cls, sMethodName.c_str(), "([Ljava/lang/String;)V");
    if (mid == 0)
	{
		CM_TRACE_ERROR("Can't find Prog class\n")
		//TODO:
		//throw Exception
    }

    /*
	jstring jstr;
    jstr = env->NewStringUTF(" from C!");
    if (jstr == 0)
	{
		CM_TRACE_ERROR("Out of memory\n")
		//TODO:
		//throw Exception
    }
	*/

	jobjectArray args;
    args = env->NewObjectArray(argLen, env->FindClass("java/lang/String"), NULL);
    if (args == 0)
	{
		CM_TRACE_ERROR("Out of memory\n")
		//TODO:
		//throw Exception
    }
	for ( int i=0; i<argLen;i++)
	{
		env->SetObjectArrayElement(args, i, env->NewStringUTF(sArgs[i].c_str()));
	}

	try
	{
		env->CallStaticVoidMethod(cls, mid, args);
	}
	catch ( ... )
	{
		CM_TRACE_ERROR("Unknow error on CallStaticVoidMethod");
	}
}

void JniInvoker::destroyJVM()
{
	CM_CODEBLOCK(JniInvoker::destroyJVM)
	try
	{
		jvm->DestroyJavaVM();
	}
	catch ( ... )
	{
		CM_TRACE_ERROR("unknow error on DestroyJavaVM");
	}
}
