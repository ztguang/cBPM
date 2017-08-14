#ifndef _WAPI_LOGGER_H_
#define _WAPI_LOGGER_H_

#include "CriteriaCommonDefines.h"

//TO_BE_EXPORTED

/**
* Istanzia engine e database e predispone gli oggetti per la comunicazione
* di un client esterno verso il motore.
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void Logger(const char* acLog);

extern "C" ENGINE_API void LoggerLevel(const char* acTraceName, int iTraceLevel);

#endif


