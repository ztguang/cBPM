#ifndef _WAPI_ROLE_H_
#define _WAPI_ROLE_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

/**
* Restituisce tutti i ruoli definiti nel file di roles.
*
* @sa getRolesBykey
* @param Response struttua dati per la comunicazione di codice di errore e messaggio di errore.
* @throws
* @see
* @return	i roles.
* @code
*<ROLES>
*	<ROLE KEY="Administrator">
*		<NAME>Administrator</NAME>
*		<DESCRIPTION>myWorkflow Administrator</DESCRIPTION>
*		<USERS>
*			<USER KEY="ddematteo"></USER>
*		</USERS>
*	</ROLE>
*	<ROLE KEY="Developer">
*		<NAME>Developer</NAME>
*		<DESCRIPTION>myWorkflow Administrator</DESCRIPTION>
*		<USERS>
*			<USER KEY="mfarina"></USER>
*		</USERS>
*	</ROLE>	
*</ROLES>
* @endcode
* @returns
*/
extern "C" ENGINE_API char* getRoles(Response* response);

/**
* Restituisce il ruolo associato alla key passata
*
* @sa getRoles
* @param Response struttua dati per la comunicazione di codice di errore e messaggio di errore.
* @throws
* @see
* @return	il "role".
* @code
*<ROLE KEY="Administrator">
*	<NAME>Administrator</NAME>
*	<DESCRIPTION>myWorkflow Administrator</DESCRIPTION>
*	<USERS>
*		<USER KEY="ddematteo"></USER>
*	</USERS>
*</ROLE>
* @endcode
* @returns
*/
extern "C" ENGINE_API char* getRolesBykey(char* acRoleKey, Response* response);

/**
* Aggiunge un ruolo al file di roles.
*
* @sa updateRole deleteRole
* @param Response struttua dati per la comunicazione di codice di errore e messaggio di errore.
* @param il "role"
*<ROLE KEY="Administrator">
*	<NAME>Administrator</NAME>
*	<DESCRIPTION>myWorkflow Administrator</DESCRIPTION>
*	<USERS>
*		<USER KEY="ddematteo"></USER>
*	</USERS>
*</ROLE>
* @throws
* @see
* @return
* @code
* @endcode
* @returns
*/
extern "C" ENGINE_API void createRole(char* acRole, Response* response);

/**
* Modifica un ruolo del file di roles.
*
* @sa updateRole deleteRole
* @param Response struttua dati per la comunicazione di codice di errore e messaggio di errore.
* @param il "role"
*<ROLE KEY="Administrator">
*	<NAME>Administrator</NAME>
*	<DESCRIPTION>myWorkflow Administrator</DESCRIPTION>
*	<USERS>
*		<USER KEY="ddematteo"></USER>
*	</USERS>
*</ROLE>
* @throws
* @see
* @return
* @code
* @endcode
* @returns
*/
extern "C" ENGINE_API void updateRole(char* acRole, Response* response);

/**
* Elimina un ruolo del file di roles.
*
* @sa updateRole deleteRole
* @param Response struttua dati per la comunicazione di codice di errore e messaggio di errore.
* @param il "rolekey"
* @throws
* @see
* @return
* @code
* @endcode
* @returns
*/
extern "C" ENGINE_API void deleteRole(char* acRoleKey, Response* response);

/**
* Aggiunge un utente ad un ruolo del file di roles.
*
* @sa updateRole deleteRole
* @param Response struttua dati per la comunicazione di codice di errore e messaggio di errore.
* @param lo "user"
*<USER KEY="pluto">
*	<NAME>Daniele De Matteo</NAME>
*	<DESCRIPTION>Daniele De Matteo</DESCRIPTION>
*</USER>
* @param il "rolekey"
* @throws
* @see
* @return
* @code
* @endcode
* @returns
*/
extern "C" ENGINE_API void addUserToRole(char* acUser, char* acRoleKey, Response* response);

/**
* Aggiunge un utente ad un ruolo del file di roles.
*
* @sa updateRole deleteRole
* @param Response struttua dati per la comunicazione di codice di errore e messaggio di errore.
* @param lo "user"
*<USER KEY="pluto">
*	<NAME>Daniele De Matteo</NAME>
*	<DESCRIPTION>Daniele De Matteo</DESCRIPTION>
*</USER>
* @param il "rolekey"
* @throws
* @see
* @return
* @code
* @endcode
* @returns
*/
extern "C" ENGINE_API void removeUserFromRole(char* acUserKey, char* acRoleKey, Response* response);

/**
* Restituisce il ruolo a cui appartiene l'utente.
*
* @param acUser lo "user"
* @param Response struttua dati per la comunicazione di codice di errore e messaggio di errore.
* @throws
* @see
* @return
* @code
* @endcode
* @returns
*/
extern "C" ENGINE_API char* getRolesByUser(char* acUser, Response* response);


#endif