#include "CommonDefines.h"

#include "bOSProcess.h"
using namespace bOS::System;

#include "bOSRuntimeException.h"
using namespace bOS::Exception;


Process::Process()
{
    m_hProcess = 0;     // m_hProcess = NULL;
    m_ProcessID = 0;     // m_ProcessID = NULL;
    m_ThreadID = 0;      // m_ThreadID = NULL;
    m_processFileName = "";

    #ifdef _BOS_ON_WIN32_
        //retreive the current running process data
        m_hProcess = GetCurrentProcess();
        m_ProcessID = GetCurrentProcessId();
        m_ThreadID = GetCurrentThreadId();
        TCHAR moduleFileName[MAX_PATH];
        ::GetModuleFileName( NULL, moduleFileName, MAX_PATH );
        memset( moduleFileName, 0, MAX_PATH );
        m_processFileName = moduleFileName;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        m_hProcess = getpid();
        m_ProcessID = getpid();
        m_ThreadID = 0;
        m_processFileName = "";
    #endif
}

Process::Process(unsigned int pid)
{
    //m_hProcess = NULL;
    //m_ProcessID = NULL;
    //m_ThreadID = NULL;
    m_hProcess = 0;     // m_hProcess = NULL;
    m_ProcessID = 0;     // m_ProcessID = NULL;
    m_ThreadID = 0;      // m_ThreadID = NULL;
    m_processFileName = "";

    #ifdef _BOS_ON_WIN32_
        //retreive the current running process data
        m_hProcess = GetCurrentProcess();
        m_ProcessID = pid;
        m_ThreadID = GetCurrentThreadId();
        TCHAR moduleFileName[MAX_PATH];
        ::GetModuleFileName( NULL, moduleFileName, MAX_PATH );
        memset( moduleFileName, 0, MAX_PATH );
        m_processFileName = moduleFileName;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        m_hProcess = pid;
        m_ProcessID = pid;
        m_ThreadID = 0;
        m_processFileName = "";
    #endif
}

Process::~Process()
{
    //m_hProcess = NULL;
    //m_ProcessID = NULL;
    //m_ThreadID = NULL;
    m_hProcess = 0;     // m_hProcess = NULL;
    m_ProcessID = 0;     // m_ProcessID = NULL;
    m_ThreadID = 0;      // m_ThreadID = NULL;
    m_processFileName = "";

    //TODO::: Do we have to kill the process ???
}

unsigned int Process::getProcessID()
{
    #ifdef _BOS_ON_WIN32_
        return m_ProcessID;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        return m_ProcessID;
    #endif
}

unsigned int Process::getThreadID()
{
    #ifdef _BOS_ON_WIN32_
        return m_ThreadID;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        return m_ThreadID;
    #endif
}

void Process::createProcess( const String& processName, ProcessArguments args )
{
    // TODO
    //   - work if processName contains environment variables... $(HOME)/pippo.exe
    //   - work with shell scripts (sh, ksh, bat, cmd)

    #ifdef _BOS_ON_WIN32_
        PROCESS_INFORMATION _processInfo;
        STARTUPINFO         _startupInfo;
        WIN32_FIND_DATA     _findData;

        // Startup info come from this process
        GetStartupInfo( &_startupInfo );

        //Test if the processName exist
        if ( processName == "" )
        {
            throw RuntimeException( INVALID_PROCESS );
        }
        else
        {
            HANDLE handle = FindFirstFile( processName.c_str(), &_findData );
            if (handle == INVALID_HANDLE_VALUE)
                RuntimeException( INVALID_PROCESS );
            FindClose( handle );
        }

        //Setup process arguments...
        String commandLine = "";
        commandLine += processName + " ";
        for ( unsigned int i = 0; i < args.size(); i++ )
        {
            commandLine += args.at(i) + " ";
        }
        commandLine = commandLine.substr(0, commandLine.length() - 1 );

        BOOL bInheritHandles = FALSE;       //CREATE_NEW_CONSOLE
        DWORD dwCreationFlags = DETACHED_PROCESS | CREATE_NO_WINDOW;

        _startupInfo.hStdInput   = GetStdHandle(STD_INPUT_HANDLE);
        _startupInfo.hStdOutput  = GetStdHandle(STD_OUTPUT_HANDLE);
        _startupInfo.hStdError   = GetStdHandle(STD_ERROR_HANDLE);

        /*
		BOOL bRet = CreateProcess( processName.c_str(), (Char*)commandLine.c_str(), NULL, NULL,
                        bInheritHandles, dwCreationFlags, NULL, NULL, &_startupInfo, &_processInfo );
		*/
		BOOL bRet = CreateProcess( NULL, (Char*)commandLine.c_str(), NULL, NULL,
                        bInheritHandles, 0, NULL, NULL, &_startupInfo, &_processInfo );
        if ( !bRet )
        {
            throw RuntimeException( INVALID_PROCESS );
        }
        m_processFileName = processName;
        m_hProcess = _processInfo.hProcess;
        m_ProcessID = _processInfo.dwProcessId;
        m_ThreadID = _processInfo.dwThreadId;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        //Test if the processName is not blank
        if ( processName == "" )
            throw RuntimeException( INVALID_PROCESS );

        //TODO:: Verificare che il file esista

        pid_t pid = fork();
        if ( pid == 0 )
        {
            const char** argv;
            argv = (const char**) malloc( sizeof(char*) * (args.size() + 2) );

            //TODO:: If we dont have free memory it's really a big deal!!!

            memset( argv, '\0', sizeof(char*) * (args.size() + 2) );
            argv[0] = processName.c_str();
            for ( unsigned int i = 0; i < args.size(); i++ )
	        {
	            argv[ i + 1 ] = args[i].c_str();
	        }

            if ( execvp( processName.c_str(), (char*const*)argv ) == -1 )
            {
                throw RuntimeException( INVALID_PROCESS );
            }
        }
        else if ( pid == -1 )
        {
            throw RuntimeException( INVALID_PROCESS );
        }
        m_processFileName = processName;
        m_hProcess = pid;
        m_ProcessID = pid;
        m_ThreadID = 0;
    #endif
}

String Process::getProcessName()
{
    #ifdef _BOS_ON_WIN32_
        return m_processFileName;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        return m_processFileName;
    #endif
}

int Process::getExitCode()
{
    return this->waitFor();
}

bool Process::isRunning()
{
    #ifdef _BOS_ON_WIN32_
        DWORD dwExitCode;
        HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, (DWORD)m_ProcessID );
        if ( hProcess == NULL )
            return false;
        BOOL bRet = GetExitCodeProcess( hProcess, &dwExitCode );
        if ( !bRet )
            return false;
        CloseHandle( hProcess );
        //Check the exit code value
        return ( dwExitCode == STILL_ACTIVE );
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        int nStat = 0;
        pid_t pid = waitpid( (pid_t)m_hProcess, &nStat, WNOHANG );
        if ( pid == (pid_t)-1 )
            return false;

        if ( !WIFEXITED(nStat) || pid == 0 )
            return true;
        return false;
    #endif
}

int Process::waitFor()
{
    #ifdef _BOS_ON_WIN32_
        DWORD dwExitCode;
        HANDLE hProcess = OpenProcess( SYNCHRONIZE | PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION,
                                FALSE, (DWORD)m_ProcessID );
        if ( hProcess == NULL )
        {
            throw RuntimeException( INVALID_PROCESS );
        }
        DWORD result = WaitForSingleObject( hProcess, INFINITE );
        if ( result != WAIT_OBJECT_0 )
        {
            CloseHandle( hProcess );
            throw RuntimeException( INVALID_PROCESS );
        }
        BOOL bRet = GetExitCodeProcess( hProcess, &dwExitCode );
        CloseHandle( hProcess );
        return dwExitCode;
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        int nStat = 0;
        pid_t pid = waitpid( (pid_t)m_hProcess, &nStat, 0 );
        if ( pid <= 0 )
        {
            throw RuntimeException( INVALID_PROCESS );
        }
        if ( !WIFEXITED(nStat) )
        {
            throw RuntimeException( INVALID_PROCESS );
        }
        return WEXITSTATUS( nStat );
    #endif
}

void Process::destroyProcess()
{
    #ifdef _BOS_ON_WIN32_
        HANDLE hProcess = OpenProcess( PROCESS_TERMINATE, FALSE, (DWORD)m_ProcessID );
        if ( hProcess == NULL )
        {
            throw RuntimeException( INVALID_PROCESS );
        }
        BOOL bRet = TerminateProcess( m_hProcess, 0 );
        if ( !bRet )
        {
            CloseHandle( hProcess );
            throw RuntimeException( INVALID_PROCESS );
        }
        CloseHandle( hProcess );
	#else // _BOS_ON_SOLARIS_ _BOS_ON_HP_
        if ( kill( m_hProcess, SIGKILL ) )
        {
            throw RuntimeException( INVALID_PROCESS );
        }
    #endif
}

void* Process::getCurrentProcessId()
{
	#ifdef _BOS_ON_WIN32_
		return (void*)GetCurrentProcessId();
	#else
		return (void *)getpid();
	#endif
}
