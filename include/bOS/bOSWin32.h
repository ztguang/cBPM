#ifndef _BOS_WIN32_H_
#define _BOS_WIN32_H_

//TO_BE_EXPORTED
//ztg delete        使用 linux代码，不使用 windows代码
//#define _BOS_ON_WIN32_

#ifdef _BOS_STATIC_LIBRARY
	#define BOS_API
#else
	#ifdef BOS_EXPORTS
		//#define BOS_API __declspec(dllexport)        //ztg delete
		//#define BOS_API __attribute__ ((visibility("default")))
		#define BOS_API
	#else
		#define BOS_API __declspec(dllimport)
	#endif
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef IT_USE_STD_IOSTREAM
#define IT_USE_STD_IOSTREAM
#endif

//ztg add
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <pthread.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#include <dlfcn.h>           /* For dlopen  RTLD_NOW | RTLD_GLOBAL */

//ztg add   /opt/cBPM/criteria-lin/reference/cpp/include
#include <selfded.h>

//include std window headers
//#include <process.h>      //ztg delete
//#include <windows.h>      //ztg delete
//#include <commctrl.h>      //ztg delete
//#include <shlobj.h>      //ztg delete
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <fstream>
#include <iostream>
#include <strstream>
#include <assert.h>
#include <time.h>
#include <errno.h>
#include <sys/timeb.h>
#include <algorithm>
#include <typeinfo>
#include <sys/wait.h>
#include <sys/time.h>

typedef int socket_type;
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

//ztg delete
//SOCKET
//#include <winsock2.h>
//typedef SOCKET socket_type;
//typedef int socklen_t;

//ztg delete
//#include <string>
//ztg add
#include <cstring>
#include <cstdarg>

#include <streambuf>
#include <ostream>
#include <stdexcept>
#include <sstream>

using namespace std;


//#define SLASH "\\"			//windows
#define SLASH "/"			//linux
//#define NEWLINE	"\n"	//windows
#define NEWLINE	"\r"		//linux

//ztg add
typedef void *HANDLE;

typedef HANDLE	MUTEX;
typedef HANDLE	BOS_THREAD;
typedef HANDLE	PROCESS;
typedef HANDLE  SEMAPHORE;
typedef int64_t longlong;

//
typedef size_t	SIZE_INT;

typedef unsigned long      UINT_PTR;
typedef UINT_PTR        SOCKET;

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

#endif //_BOS_WIN32_H_
