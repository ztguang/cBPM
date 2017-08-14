#ifndef _WAPI_USER_H_
#define _WAPI_USER_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

/**
* Controlla se la password corrisponde all'utente immesso.
*
* @code
* @endcode
* @sa
* @param acUserKey ?l'utente che ha richiesto la lista delle attivit?
* @param acPassword ?la password dell'utente.
* @param Response ?la struttra di comunicazione con l'esterno
* @throws
* @see
* @return	0 - Autenticazione OK
* @return	1 - Autenticazione KO
* @return	... da definire.
* @returns
*/
extern "C" ENGINE_API int authenticate(char* acUserKey, char* acPassword, Response* response);

/**
* Controlla se l'utente appartiene al ruolo.
*
* @code
* @endcode
* @sa
* @param acUserKey ?l'utente che ha richiesto la lista delle attivit?
* @param acRole ?il ruolo
* @param Response ?la struttra di comunicazione con l'esterno
* @throws
* @see
* @return	0 - Utente in ruolo
* @return	1 - Utente non n ruolo
* @return	... da definire.
* @returns
*/
extern "C" ENGINE_API int isInRole(char* acUserKey, char* acRole, Response* response);

/**
* Restituisce l'utente corrispondente alla userkey
*
* @code
* @endcode
* @sa
* @param acUserKey ?l'utente che ha richiesto la lista delle attivit?
* @param Response ?la struttra di comunicazione con l'esterno
* @throws
* @see
* @return	String Xml che rappresenta l'utente.
*<USER KEY="mfarina">
*		<NAME>Maurizio Farina</NAME>
*		<DESCRIPTION>Maurizio Farina</DESCRIPTION>
*	</USER>
* @returns
*/
extern "C" ENGINE_API char* getUser(char* acUserKey, Response* response);

/**
* Restituisce tutti gli utenti
*
* @code
* @endcode
* @sa
* @param Response ?la struttra di comunicazione con l'esterno
* @throws
* @see
* @return	String Xml che rappresenta l'utente.
*<USERS>
*<USER KEY="mfarina">
*		<NAME>Maurizio Farina</NAME>
*		<DESCRIPTION>Maurizio Farina</DESCRIPTION>
*</USER>
*...
*</USERS>
* @returns
*/
extern "C" ENGINE_API char* getUsers(Response* response);

/**
* Restituisce tutti gli utenti appartenenti ad un ruolo.
*
* @code
* @endcode
* @sa
* @param acRole ?il ruolo.
* @param Response ?la struttra di comunicazione con l'esterno
* @throws
* @see
* @return	String Xml che rappresenta l'utente.
*<USERS>
*<USER KEY="mfarina">
*		<NAME>Maurizio Farina</NAME>
*		<DESCRIPTION>Maurizio Farina</DESCRIPTION>
*</USER>
*...
*</USERS>
* @returns
*/
extern "C" ENGINE_API char* getUsersByRole(char* acRole, Response* response);

/**
* Aggiunge un utente.
*
* @code
* @endcode
* @sa
* @param 
* @param acUser Stringa Xml contenente le informazioni dell'utente.
*<USER KEY="mfarina">
*		<NAME>Maurizio Farina</NAME>
*		<DESCRIPTION>Maurizio Farina</DESCRIPTION>
*</USER>
* @param Response ?la struttra di comunicazione con l'esterno
* @throws
* @see
* @returns
*/
extern "C" ENGINE_API void createUser(char* acUser,Response* response);

/**
* Modifica un utente.
*
* @code
* @endcode
* @sa
* @param 
* @param acUser Stringa Xml contenente le informazioni dell'utente.
*<USER KEY="mfarina">
*		<NAME>Maurizio Farina</NAME>
*		<DESCRIPTION>Maurizio Farina</DESCRIPTION>
*</USER>
* @param Response ?la struttra di comunicazione con l'esterno
* @throws
* @see
* @returns
*/
extern "C" ENGINE_API void updateUser(char* acUser, Response* response);

/**
* Cancella un utente.
*
* @code
* @endcode
* @sa
* @param 
* @param acUserKey La userKey dell'utente da cancellare.

* @param Response ?la struttra di comunicazione con l'esterno
* @throws
* @see
* @returns
*/
extern "C" ENGINE_API void deleteUser(char* acUserKey, Response* response);

#endif


