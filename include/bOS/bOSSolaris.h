#ifndef _BOS_SOLARIS_H_
#define _BOS_SOLARIS_H_

//TO_BE_EXPORTED
#define _BOS_ON_SOLARIS_

#define BOS_API

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif 

#ifndef IT_USE_STD_IOSTREAM
#define IT_USE_STD_IOSTREAM
#endif

#define SLASH "/"

typedef int socket_type;
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/filio.h>
#include <stropts.h>
#include <arpa/inet.h>

#include <string>
#include <streambuf>
#include <ostream>
#include <stdexcept>
#include <sstream>

typedef size_t	SIZE_INT;

#endif //_BOS_SOLARIS_H_