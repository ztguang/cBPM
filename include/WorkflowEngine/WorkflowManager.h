#ifndef __FE_WORKFLOWMANAGER_H__
#define __FE_WORKFLOWMANAGER_H__

#include "IWorkflow.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			class WorkFlowThread;
			typedef vector<IWorkflow*> WorkflowList;
			//TO_BE_EXPORTED
			/**
			* Accoglie le richieste Engine e si occupa fisicamnte di istanziare 
			* gli oggetti che creano, distruggono e gestiscono i thread che costituiscono 
			* il workflow. Crea una lista di workflow ed una interfaccia di comunicazione 
			* con le classi che creano fisicamente i thread. 
			* Infine gestisce le eccezioni sollevate dal workflow.
			* 
			* La classe gestisce le istanze di workflow attive in esecuzione, ed espone i metodi necessari
			* alla selezione e alla manipolazione dell'istanza (find, start, stop, restart).
			*
			* WorkflowList ?il vettore che contiene tutte le istanze di workflow attive.
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
			class WorkflowManager
			{
				public:

					static WorkflowManager* instance();
					static void deinstance();
					
					/**
					* Aggiunge una istanza alla lista dei workflow.
					*
					* @code
					* @endcode
					* @sa
					* @param wf ?l'istanza di workflow da aggiungere di tipo Workflow (Puntatore)
					* @throws
					* @see
					* @return
					* @returns
					*/
					void add( IWorkflow* wf );

					/**
					* Rimuove una istanza dalla lista dei workflow.
					*
					* @code
					* @endcode
					* @sa
					* @param workflowID ?il numero di istanza da distruggere
					* @throws
					* @see
					* @return
					* @returns
					*/
    				void remove( const char* workflowID );
			        
					/**
					* Cerca una istanza all'interno della lista dei workflow.
					*
					* @code
					* @endcode
					* @sa
					* @param workflowID ?il numero di istanza da cercare
					* @throws
					* @see
					* @return IWorkflow* ?il contenuto del vettore di 
					* workflow attivi corrispondente all'istanza cercata 
					* (IWorkflow* ?il puntatore all'area di memoria che contiene il workflow cwrcato)
					* @returns
					*/
					IWorkflow* find( const char* workflowID );

					/**
					* Avvia una istanza dalla lista dei workflow.
					* lo start avviene chiamando un metodo della classe workflow che a sua volta
					* creer?il thread che realizza fisicamente lo start.
					*
					* @code
					* @endcode
					* @sa
					* @param workflowID ?il numero di istanza da startare
					* @throws
					* @see
					* @return IWorkflow* ?il puntatore all'area di memoria che contiene il workflow avviato
					* @returns
					*/
					IWorkflow* start( const char* workflowID );

					/**
					* Cessa una istanza dalla lista dei workflow.
					* lo stop avviene chiamando un metodo della classe workflow che a sua volta
					* distrugge il thread che realizza fisicamente il worflow.
					*
					* @code
					* @endcode
					* @sa
					* @param workflowID ?il numero di istanza da stoppare
					* @throws
					* @see
					* @return IWorkflow* ?il puntatore all'area di memoria che contiene il workflow da cessare
					* @returns
					*/
    				IWorkflow* stop( const char* workflowID );

					/**
					* Sospende una istanza dalla lista dei workflow.
					* la sospensione avviene chiamando un metodo della classe workflow che a sua volta
					* sospende il thread che realizza fisicamente il workflow.
					*
					* @code
					* @endcode
					* @sa
					* @param workflowID ?il numero di istanza da sospendere
					* @throws
					* @see
					* @return IWorkflow* ?il puntatore all'area di memoria che contiene il workflow da sospenere
					* @returns
					*/
    				IWorkflow* suspend( const char* workflowID );
			    	
					/**
					* Lancia le richieste per realizzare la partenza dei thread che implementano le
					* richieste provenenti dall'engine.
					*
					* @code
					* @endcode
					* @sa
					* @param IWorkflow* ?il puntatore all'area di memoria che contiene il workflow
					* @param bDetach ?il booleano che determina se il thread che si vuole lanciare
					* deve o meno essere sincronizzato
					* @throws
					* @see
					* @return WorkFlowThread* ?il thread di workflow lanciato (puntatore alla'area di memoria del thread creato)
					* @returns
					*/
    				WorkFlowThread* executeJob( IWorkflow* pWF, bool bDetach = true );

					/**
					* Resituisce il numero dei workflow attivi.
					* Opera sul vettore dei workflowlist
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
					int getWorkflowCount() { Mutex::Lock locker(mtxWFList); return wfList.size(); }

					WorkflowList getList();

				private:
				
					static WorkflowManager* _instance;
					WorkflowManager();

       				virtual ~WorkflowManager();


					WorkflowList    wfList;


					Mutex       mtxWFList;
					
			};
		}
	}
}

#endif 
