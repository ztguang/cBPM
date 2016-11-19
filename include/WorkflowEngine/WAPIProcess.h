#ifndef _WAPI_PROCESS_H_
#define _WAPI_PROCESS_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

extern "C" ENGINE_API char* PrepareProcessInstance( char* lProcess, char* acWorkflowName, Response* response );

/**
* Genera una istanza di processo a partire dal nome del modello.
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param sWorkflowName ?una stringa contiene il nome del modello del processo da istanziare
* @param sProcess ?la stringa contenente il processo creato
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* createNewProcessInstance(const char* acWorkflowName,  char* lProcess,Response* response );

extern "C" ENGINE_API void createWorkflowProcess( const char* acWorkflowName,char* lProcess,  Response* response );

/**
* Effettua la partenza di un processo che avvia la prima attivita 
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param iProcessID ?un intero che rappresenta l'istanza di un processo esistente
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void startProcessInstance(const char* iProcessID, Response* response );

/**
* Effettua la partenza di un processo che avvia la prima attivita 
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param iProcessID ?un intero che rappresenta l'istanza di un processo esistente
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void startProcessInSynchWay(const char* iProcessID, Response* response );

/**
* Assegna ad una istanza di processo una collezione di attributi
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param iProcessID ?un intero che rappresenta l'istanza di un processo esistente
* @param xml Attributes ?una stringa xml che contiene la collezione di attributi 
* nella forma nome-valore che verra assegnato alla activity
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* setProcessInstanceAttributes( const char* lProcessID, const char* xmlAttributes, Response* response);


/**
* Effettua la ripartenza di una istanza di processo che risultava ferma in uno stato 
* manuale a partire dalla activity specificata.
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param iProcessID ?un intero che rappresenta l'istanza di un processo esistente
* @param acStatus ?una stringa xml che contiene una activity del processo in corso
* dalla quale bisogna ripartire
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API void restartProcessInstance(char* iProcessID,char* acStatus,  Response* response );

extern "C" ENGINE_API void restartProcessInSynchWay(char* iProcessID,char* acStatus,  Response* response );


extern "C" ENGINE_API void UpdateProcessInstanceAttributes( char* lProcessID,char* xmlAttributes,  Response* response);

/**
* Restituisce una stringa xml che rappresenta la collezione di attributi associati 
* alla istanza di processo in questione
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param iProcessID ?un intero che rappresenta l'istanza di un processo esistente
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getProcessInstanceAttributes(char* lProcessID, Response* response);


/**
* Restituisce una stringa xml che costituisce una collezione di activity che a partire
* dalla activity in ingresso possono essere raggiunte con transizione di stato
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno nella quale vengono
* passati o il codice di errore con il messaggio di errore oppure il codice 0 ed
* il risultato della funzione o operazione sottoforma di stringa xml successivamente 
* da leggere ed interpretare.
* @param xmlActivity ?una stringa xml che contiene una activity di un processo
* @param iProcessID ?un intero che rappresenta l'istanza di un processo esistente
* @throws
* @see
* @return
* @returns
*/
extern "C" ENGINE_API char* getNextActivityList(char* lProcessID,char* acActivityName,  Response* response);

extern "C" ENGINE_API char* getActivityResultList(char* lProcessID, char* xmlActivity, Response* response);

extern "C" ENGINE_API long getNumberRunningWorkflow(Response* response);

extern "C" ENGINE_API char* getProcessInstance(char* lProcessID, Response* response);

extern "C" ENGINE_API char* getProcessHeader(char* lProcessID, Response* response);

extern "C" ENGINE_API char* getNewProcessHeader(char* lProcessID, Response* response);

extern "C" ENGINE_API char* getProcessStatus(char* lProcessID, Response* response);

extern "C" ENGINE_API char* getProcesses(Response* response);

extern "C" ENGINE_API char* getProcessAttribute(char* iProcessID, char* acAttributeName, Response* response );

extern "C" ENGINE_API char* LoadProcessInstance(char* lProcessID, Response* response);

#endif


