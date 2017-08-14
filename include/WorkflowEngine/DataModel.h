#ifndef _DATAMODEL_H_
#define _DATAMODEL_H_

//TO_BE_EXPORTED

#ifdef DATAMODEL_EXPORTS
    #define DATAMODEL_API __declspec(dllexport)
#else
    #define DATAMODEL_API __declspec(dllimport)
#endif

#endif //_DATAMODEL_H_