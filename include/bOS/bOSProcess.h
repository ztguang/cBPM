
#ifndef __BOS_PROCESS_H__
#define __BOS_PROCESS_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

namespace bOS
{
    namespace System
    {
        typedef vector<String> ProcessArguments;

        /**
         * A Process represents an EXE. More docs here...
         */
        class BOS_API Process
        {
            public:

                Process();

				Process(unsigned int pid);

                virtual ~Process();

                virtual unsigned int getProcessID();

                virtual unsigned int getThreadID();

                virtual void createProcess( const String& processName, ProcessArguments args );

                virtual String getProcessName();

                virtual int getExitCode();

                virtual bool isRunning();

                virtual int waitFor();

                virtual void destroyProcess();

				static void* getCurrentProcessId();

            protected:

                //PROCESS         m_hProcess;       //ztg delete
                unsigned int    m_hProcess;

                unsigned int    m_ProcessID;
                unsigned int    m_ThreadID;

                String          m_processFileName;
        };
    }
};

#endif


