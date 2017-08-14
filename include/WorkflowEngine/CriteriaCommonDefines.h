#ifndef _ENGINE_COMMON_DEFINES_H_
#define _ENGINE_COMMON_DEFINES_H_

// TO_BE_EXPORTED
#ifdef _CRITERIA_STATIC_LIBRARY
	#define ENGINE_API
#else
#ifdef ENGINE_EXPORTS
//	#define ENGINE_API __declspec(dllexport)        //ztg delete
    #define ENGINE_API __attribute__ ((__visibility__("default")))
#else
	#define ENGINE_API __declspec(dllimport)
#endif
#endif

typedef struct
{
	int iCode;
	char* sMsg;
} Response;

#endif //_ENGINE_COMMON_DEFINES_H_

