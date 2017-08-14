#ifndef _WIN_LIN_H
# define _WIN_LIN_H

// come from /opt/cBPM/criteria-lin/src/Criteria/Criteria.Libraries.bOS/bOSWin32.h

//ztg add
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <pthread.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

//ztg add   /opt/cBPM/criteria-lin/reference/cpp/include
#include <selfded.h>


#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>


#endif
