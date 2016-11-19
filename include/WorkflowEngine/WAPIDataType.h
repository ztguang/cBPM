#ifndef _WAPI_DATA_TYPE_H_
#define _WAPI_DATA_TYPE_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

/**
* Controlla se la password corrisponde all'utente immesso.
*
* @code
* @endcode
* @sa
* @param acUserKey è l'utente che ha richiesto la lista delle attività.
* @param acPassword è la password dell'utente.
* @param Response è la struttra di comunicazione con l'esterno
* @throws
* @see
* @return	0 - Autenticazione OK
* @return	1 - Autenticazione KO
* @return	... da definire.
* @returns
*/
extern "C" ENGINE_API char* getDataTypes(Response* response);

extern "C" ENGINE_API char* getDataType(char* acDataType, Response* response);




#endif //_WAPI_DATA_TYPE_H_