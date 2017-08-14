#ifndef _BOS_DEFINES_H_
#define _BOS_DEFINES_H_

//TO_BE_EXPORTED
//#define NULL 0        //ztg delete

#include "bOSTypes.h"
using namespace bOS::Core;

#ifdef WIN32
    #include "bOSWin32.h"
#elif __SUNPRO_CC
    #include "bOSSolaris.h"
#elif __HP_aCC
	#include "bOSHp.h"
#endif

#endif //_BOS_DEFINES_H_

