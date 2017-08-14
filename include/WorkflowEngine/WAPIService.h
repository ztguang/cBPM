#ifndef _WAPI_SERVICE_H_
#define _WAPI_SERVICE_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

/**
* Consente di recuperare la lista dei servizi.
*
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati il codice di errore ed il messaggio di errore.
* @throws
* @see
* @return la lista dei servizi.
* @returns
*/
extern "C" ENGINE_API char* getServices( Response* response );

/**
* Consente di recuperare la lista dei servizi per un determinato utente.
*
* @sa
* @param acUser l'indentificativo dell'utente.
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati il codice di errore ed il messaggio di errore.
* @throws
* @see
* @return la lista dei servizi.
* @returns
*/
extern "C" ENGINE_API char* getServicesForUser(char* acUser, Response* response);

extern "C" ENGINE_API char* getServicesForExtendedAttribute(char* acUser, char* acAttributeName, char* acAttributeValue, Response* response);

extern "C" ENGINE_API char* getService(char* acUser, char* acServiceName, Response* response);

extern "C" ENGINE_API void addService(char* acService, Response* response);

extern "C" ENGINE_API void deleteService(char* acServiceName, Response* response);

#endif //_WAPI_SERVICE_H_