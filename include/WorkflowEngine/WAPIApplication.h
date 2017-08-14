#ifndef _WAPI_APPLICATION_H_
#define _WAPI_APPLICATION_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

/**
* Esegue una Application Api
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param acAPI è una stringa xml che contiene l'Application APi da eseguire
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* executeApi(char* acAPI, Response* response);

extern "C" ENGINE_API char* getApplications(Response* response);

extern "C" ENGINE_API char* getApplicationForExtendedAttribute(char* acAttributeName, char* acAttributeValue, Response* response);

#endif