#ifndef _WAPI_H_
#define _WAPI_H_

//TO_BE_EXPORTED

static String CRITERIA_VERSION = "1.0.0";


#include "CriteriaCommonDefines.h"


extern "C" ENGINE_API const char* Version();

/**
* Istanzia engine e database e predispone gli oggetti per la comunicazione
* di un client esterno verso il motore consentendo di valorizzare il nome
* del file di trace ed il livello del tracciamento.
*
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente
* da leggere ed interpretare.
* @param acTraceName il file di trace.
* @param iTraceLevel il livello del tracciamento
* @throws
* @return
* @returns
*/
extern "C" ENGINE_API void InitSession(Response* response);
extern "C" ENGINE_API void InitSessionWithParams(const char* acConfigFile, Response* response);
/**
* Provvede a deallocare gli oggetti creati per la comunicazione con il motore.
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
extern "C" ENGINE_API void EndSession(Response* response);

extern "C" ENGINE_API char* GetDirectory(char* acDirectory, Response* response);

extern "C" ENGINE_API char* GetScenarioExecutionDirectory(Response* response);

extern "C" ENGINE_API char* GetScenarioDBDirectory(Response* response);

extern "C" ENGINE_API char* GetCheckListFolder(Response* response);

#endif


