#define TRUE 1
#define FALSE 0

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef void *LPVOID;
typedef long *LPLONG;
typedef void *HANDLE;

#define WAIT_TIMEOUT                     258L    // dderror

#define WAIT_FAILED ((DWORD)0xFFFFFFFF)

#define STATUS_WAIT_0       ((DWORD   )0x00000000L)
#define WAIT_OBJECT_0       ((STATUS_WAIT_0 ) + 0 )

#define INFINITE            0xFFFFFFFF  // Infinite timeout
#define STATUS_ABANDONED_WAIT_0          ((DWORD   )0x00000080L)
#define WAIT_ABANDONED         ((STATUS_ABANDONED_WAIT_0 ) + 0 )
#define ERROR_ALREADY_EXISTS             183L


typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

