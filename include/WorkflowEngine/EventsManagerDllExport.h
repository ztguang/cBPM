#ifndef _EVENTS_MANAGER_DLL_EXPORT_H_
#define _EVENTS_MANAGER_DLL_EXPORT_H_

//TO_BE_EXPORTED

#ifdef EVENTSMANAGER_EXPORTS
	#define EVENTSMANAGER_API __declspec(dllexport)
#else
	#define EVENTSMANAGER_API __declspec(dllimport)
#endif

#endif //_EVENTS_MANAGER_DLL_EXPORT_H_