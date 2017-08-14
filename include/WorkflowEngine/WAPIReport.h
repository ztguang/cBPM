#ifndef _WAPI_ACTIVITY_H_
#define _WAPI_ACTIVITY_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

/**
* Restituisce una stringa xml che costituisce una collezione di activity di activity 
* tutte in stato fermo in attesa di attività manuali.
*
* @code
* @endcode
* @sa
* @param acUser è l'utente che ha richiesto la lista delle attività.
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getReports(char* iProcessID, Response* response);

#endif //_WAPI_ACTIVITY_H_