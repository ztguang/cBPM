#ifndef _WAPI_ACTIVITY_H_
#define _WAPI_ACTIVITY_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

/**
* Restituisce una stringa xml che costituisce il log attuale dell'attivit�
*
* @code
* @endcode
* @sa
* @param acUser � l'utente che ha richiesto la lista delle attivit�.
* @param xmlActivity � una stringa xml che contiene una activity di un processo
* @param Response � la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getActivityLog(char* xmlActivity, char* acUser, Response* response);

/**
* Restituisce una stringa xml che costituisce il log storico dell'attivit�
*
* @code
* @endcode
* @sa
* @param acUser � l'utente che ha richiesto la lista delle attivit�.
* @param xmlActivity � una stringa xml che contiene una activity di un processo
* @param Response � la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getActivityHistoryLog(char* xmlActivity, char* acUser, Response* response);

/**
* Restituisce una stringa xml che costituisce una collezione di activity di activity 
* tutte in stato fermo in attesa di attivit� manuali.
*
* @code
* @endcode
* @sa
* @param acUser � l'utente che ha richiesto la lista delle attivit�.
* @param Response � la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getActivityList(char* acUser, Response* response);

extern "C" ENGINE_API char* getAllActivityList(char* acUser, Response* response);

extern "C" ENGINE_API char* getAllMyActivityList(char* acUser, Response* response);

extern "C" ENGINE_API char* getActivityListByProcess(char* acProcessId,char* acUser, Response* response);

extern "C" ENGINE_API char* getActivitiesByProcess(char* acProcessId, Response* response);

/**
* Assegna ad una activity una collezione di attributi
*
* @code
* @endcode
* @sa
* @param Response � la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param xmlActivity � una stringa xml che contiene una activity di un processo
* @param xmlAttributes � una stringa xml che contiene la collezione di attributi 
* nella forma nome-valore che verr� assegnato alla activity
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* setActivityAttributes(char* xmlActivity, char* xmlAttributes, char* acUser, Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione di attributi associati 
* alla activity in questione
*
* @code
* @endcode
* @sa
* @param Response � la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param xmlActivity � una stringa xml che contiene una activity di un processo
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getActivityAttributes(char* xmlActivity, char* acUser, Response* response);

extern "C" ENGINE_API char* getAttributesFromActivity(char* acProcessId, char* acActivityName, Response* response);

/**
* Assegna ad una activity un proprietario 
*
* @code
* @endcode
* @sa
* @param Response � la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param xmlActivity � una stringa xml che contiene una activity di un processo
* @param sOwner � l'utenete a cui assegare la activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void acquireActivity(char* xmlActivity, char* sOwner, Response* response);

/**
* Assegna ad una activity un proprietario 
*
* @code
* @endcode
* @sa
* @param Response � la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param xmlActivity � una stringa xml che contiene una activity di un processo
* @param sOwner � l'utenete a cui assegare la activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void assignActivity(char* xmlActivity, char* sOwner, Response* response);


#endif


