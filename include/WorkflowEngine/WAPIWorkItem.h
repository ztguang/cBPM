#ifndef _WAPI_WORKITEM_H_
#define _WAPI_WORKITEM_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

/**
* Assegna ad una activity in stato di WorkItem una collezione di attributi
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param xmlActivity è una stringa xml che contiene una activity di un processo
* @param xml Attributes è una stringa xml che contiene la collezione di attributi 
* nella forma nome-valore che verrà assegnato alla activity
* @param acOwner è l'utenete proprietario dela activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* setWorkItemAttributes(char* xmlActivity, char* xmlAttributes, char* acOwner, Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione di attributi associati 
* ad una activity in stato di workItem.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param xmlActivity è una stringa xml che contiene una activity di un processo
* @param xml Attributes è una stringa xml che contiene la collezione di attributi 
* nella forma nome-valore che verrà assegnato alla activity
* @param acOwner è l'utenete proprietario dela activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getWorkItemAttributes(char* xmlActivity, char* acOwner,Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione activity in stato di workItem
* che sono assegnate all'utente specificato.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param acOwner è l'utenete roprietario dela activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getWorkItemList(char* acOwner, Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione activity in stato di workItem
* che sono assegnate all'utente specificato. Le activity restituite sono quelle con l'attributo
* speciale NOTIFY.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param acOwner è l'utenete roprietario dela activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getWorkItemListByNotify(char* acOwner, Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione activity in stato di workItem
* che sono assegnate all'utente specificato e che sono i fase di esecuzione.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param acOwner è l'utenete roprietario dela activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getWorkItemListRunning(char* acOwner, Response* response);

extern "C" ENGINE_API char* getWorkItemListRunningNoNotify(char* acOwner, Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione activity in stato di workItem
* che sono assegnate all'utente specificato e che sono in stato di quiescenza.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param acOwner è l'utenete roprietario dela activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getWorkItemListNoRunning(char* acOwner, Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione activity in stato di workItem
* che sono assegnate all'utente specificato e che sono in stato di quiescenza per un determinato Process.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param acOwner è l'utenete roprietario dela activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getWorkItemListNoRunningByProcess(char* lProcessID,char* acOwner, Response* response);

extern "C" ENGINE_API char* getWorkItemListRunningByProcess(char* lProcessID, char* acOwner, Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione activity in stato di workItem
* che sono assegnate all'utente specificato e che sono state completate.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param acOwner è l'utenete roprietario dela activity in questione
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getWorkItemListCompleted(char* acOwner, Response* response);

/**
* Porta il workitem dallostato di stop a quello di running.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param sOwner è l'utenete roprietario dela activity in questione
* @param xmlActivity è una stringa xml che contiene una activity di un processo
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void doWorkItem(char* xmlActivity, char* acOwner, Response* response);

/**
* Porta il workitem dallostato di running a quello di Completed.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param sOwner è l'utenete roprietario dela activity in questione
* @param xmlActivity è una stringa xml che contiene una activity di un processo
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void completeWorkItem(char* xmlActivity, char* acOwner,char* acResultCode, Response* response);

extern "C" ENGINE_API void completeWorkItemSynch(char* xmlActivity, char* acOwner, char* acResultCode, Response* response);

/**
* Porta il workitem dallostato di running a quello di stop.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param sOwner è l'utenete roprietario dela activity in questione
* @param xmlActivity è una stringa xml che contiene una activity di un processo
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void stopWorkItem(char* xmlActivity, char* acOwner,Response* response);

/**
* Cambia il proprietario del workitem.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param sOwner è l'utenete che sarà il nuovo roprietario dela activity in questione
* @param xmlActivity è una stringa xml che contiene una activity di un processo
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void reassignWorkItem(char* xmlActivity, char* sOwner, Response* response);

/**
* Cancella il proprietario del workitem roportandolo nello stato di activity.
*
* @code
* @endcode
* @sa
* @param Response è la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param sOwner è l'utenete roprietario dela activity in questione
* @param xmlActivity è una stringa xml che contiene una activity di un processo
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void releaseWorkItem(char* xmlActivity,Response* response);

#endif


