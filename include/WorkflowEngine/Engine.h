#ifndef __ENGINE_CRITERIA_H__
#define __ENGINE_CRITERIA_H__
 
// TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

//Default Listener
#include "WorkflowListener.h"
using namespace WorkflowEngine::Criteria::Event::Listener;

#include "EventMaker.h"
using namespace WorkflowEngine::Criteria::Event;

#include "EngineException.h"
#include "WorkflowManager.h"
using namespace WorkflowEngine::Criteria::Core;

const String EVENT_FLOWENGINE_NAME = "Criteria";

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			class EventsManagerThread;

			/**
			*Accoglie le richieste di workflow presentate sottoforma di file xml e 
			*provvede ad istanziare le classi che successivamente eseguiranno la richesta 
			*nonch?a lanciare la richiesta direttamente o prelevandola da una serie di 
			*servizi esposti dai quali attingere.
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
			class ENGINE_API Engine
			{
				public:
				
					static Engine* instance();
					static void deinstance();
					
					//start process from id.
					/**
					* Smista la richiesta sul metodo execute con i parametri giusti.
					*
					* @code
					* @endcode
					* @sa
					* @param lProcessID ?l'identificativo del processo da startare
					* @throws
					* @see execute()
					* @return
					* @returns
					*/
					void startWorkFlow(const char* processID);


					//start process from id.
					/**
					* Smista la richiesta sul metodo execute con i parametri giusti.
					*
					* @code
					* @endcode
					* @sa
					* @param lProcessID ?l'identificativo del processo da startare
					* @throws
					* @see execute()
					* @return
					* @returns
					*/
					void startWorkFlowInSynchWay(const char* processID);


					//
					/**
					* Accetta in ingresso il numero di istanza di processo 
					* da eseguire, un booleano per il restart del processo ed una stringa 
					* xml che rappresenta la activity da cui partire e dopo aver 
					* effettuato i controlliche tale processo esista in crea una istanza 
					* di workflow, setta i parametri provenienti dall’ingresso e lancia 
					* l’esecuzione dell'istanza creata mediante workflow manager - executejob().
					*
					* @code
					* @endcode
					* @sa
					* @param lProcessID ?l'identificativo del processo da startare
					* @param bRestart il flag per la ripartenza del processo
					* @param *acStatus ?la activity da cui ripartire
					* @throws
					* @see
					* @return
					* @returns
					*/
					void execute(const char* processID, bool bRestart, const char *acStatus, bool bSynchWay);

					/*
						riparte da acStatus senza eseguirlo ed assegnando come uscita ResultCode
					*/
					void execute(const char* processID, bool bRestart, const char *acStatus, const char* acResultCode, bool bSynchWay);
					
					
					void restartWorkFlow(const char* processID);

					void restartWorkFlowInSynchWay(const char* processID);
			        
					/**
					* Smista la richiesta sul metodo execute con i parametri giusti.
					*
					* @code
					* @endcode
					* @sa
					* @param *acStatus ?la activity da cui ripartire
					* @throws
					* @see execute()
					* @return
					* @returns
					*/
					void restartWorkFlow(const char* processID, const char *acStatus);

					void restartWorkFlowInSynchWay(const char* processID, const char *acStatus);


					//return true if one or more workflow are running.
					/**
					* Richiede se ci sono workflow attivi.
					*
					* @code
					* @endcode
					* @sa
					* @param
					* @throws
					* @see
					* @return true if one or more workflow are running.
					* @returns
					*/
					unsigned long numberWorkflowRunning();

					/**
					* Restituisce la lista dei worwflow running
					*
					* @code
					* @endcode
					* @sa
					* @param
					* @throws
					* @see
					* @return la lista dei workflow running.
					* @returns
					*/
					std::vector<String> getWorkflowRunningList();
					
					/**
					* Restituisce un vettore contenente tutte le activity che sono accessibili
					* da un processo a partire dalla activity ferma in corso di esecuzione.
					*
					* Accetta in ingresso una request dalla quale estrae il processo associato e
					* in seguito recupera l'id di processo per poi chiedere al database dei processi
					* attivi la lista di activity da restituire.
					* 
					* @code
					* @endcode
					* @sa
					* @param idRequest ?il codice di richiesta
					* @throws
					* @see
					* @return Vettore di stringhe contenenti activity
					* @returns
					*/
					std::vector<String> getNextStatusList(unsigned long idRequest);



					//Application

					/**
					* Esegue un'Application API
					* @param acAPI La stringa XML rappresentante la API da eseguire.
					*/
					String executeApplicationApi(const char* acAPI);

				private:

					Engine();
			     
					virtual ~Engine();

					static Engine* _instance;

					EventMaker*        eProducer;

					WorkflowListener    wfListener;

					EventsManagerThread* eventsManagerThread;
			};
		}
	}
}

#endif //__ENGINE_CRITERIA_H__


