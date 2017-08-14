#ifndef _APPLICATION_MANAGER_H_
#define _APPLICATION_MANAGER_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "ApplicationFunction.h"
#include "ApplicationFunctionResult.h"
using namespace DataManager::Panorama::WorkflowApplicationsData;

namespace WorkflowEngine
{
	/**
	* Apre il soket di comunicazione con l'applicativo con cui deve comunicare
	* attraverso i parametri Porta ed indirizzo IP. Lancia le primitive di rete per 
	* per l'esecuzione dei comandi di comunicazione con l'applicativo esterno con cui
	* comunica e valuta il risultato delle stesse primitive. Al termine della 
	* valutazione restituisce all'engine il risultato della action che ha lanciato
	* l'application
	*
	* @code
	* @endcode
	* @sa
	* @param
	* @throws
	* @see
	* @return
	* @returns
	*/
	class ENGINE_API ApplicationManager
	{
	public:

		static ApplicationManager* instance();
		static void deinstance();

		/**
		* Accetta in ingresso la stringa xml che costituisce la API che vuole 
		* lanciare engine nella action di una sua task. Valuta dal file di Applications
		* i parametri del comando da eseguire. Apre il soket di comunicazione e 
		* lancia il comando di rete. al termine dell'esecuzione restituisce un valore 
		* di result alla action che lo ha attivato
		*
		* La struttura della API che viene lanciata è la seguente
		* @code
		* <FUNCTIONS>
		*	<FUNCTION NAME="Connect">
		*		<PARAMETERS>
		*			<PARAMETER NAME="host" TYPE="string" MANDATORY="YES">
		*				<VALUE>127.0.0.1</VALUE>
		*			</PARAMETER>
		*			<PARAMETER NAME="user" TYPE="string" MANDATORY="YES">
		*				<VALUE>mfarina</VALUE>
		*			</PARAMETER>
		*			<PARAMETER NAME="pwd" TYPE="string" MANDATORY="YES">
		*				<VALUE>mfarina</VALUE>
		*			</PARAMETER>
		*		</PARAMETERS>
		*		<RESULT>
		*			<PARAMETERS>
		*				<PARAMETER NAME="par2" TYPE="string">
		*					<VALUE>mamma</VALUE>
		*				</PARAMETER>
		*			</PARAMETERS>
		*		</RESULT>
		*	</FUNCTION>
		*	<FUNCTION NAME="two"></FUNCTION>
		* </FUNCTIONS>
		* @endcode
		*
		* La struttura del risultato di una primitiva di rete è
		* @code
		* <RESULT>
		*			<PARAMETERS>
		*				<PARAMETER NAME="par2" TYPE="string">
		*					<VALUE>mamma</VALUE>
		*				</PARAMETER>
		*			</PARAMETERS>
		* </RESULT>
		* @endcode
		*
		* @sa
		* @param
		* @throws
		* @see
		* @return ApplicationFunctionResult è la stringa xml che contiene il risutato della 
		* primitiva di rete
		* @returns
		*/
		ApplicationFunctionResult* execute (ApplicationFunction& );

	private:
		ApplicationManager();
		~ApplicationManager();

		static ApplicationManager* _instance;
	};
}

#endif //_APPLICATION_MANAGER_H_