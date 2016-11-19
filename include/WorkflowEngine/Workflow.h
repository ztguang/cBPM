#ifndef __WORKFLOW_H__
#define __WORKFLOW_H__

#include "WorkflowManager.h"

#include "EventMaker.h"

#include "EngineException.h"

#include "WorkflowProcess.h"
#include "Transition.h"
#include "Activity.h"
#include "FormalParameters.h"
#include "FormalParameter.h"
using namespace DataManager::Panorama;

#include "bOSMutex.h"
#include "bOSSemaphore.h"
#include "bOSSmartLocker.h"

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			//TODO: Collection senza distruttore. Utile Utile Utile
			typedef vector<WorkflowProcesses::Activity*> TaskList;
			/**
			* La classe manipola le istanze di workflow. Eredita da IWorkflow l'interfaccia che
			* implementata i metodi di azione di workflow (starting, stopped, suspending) e si completa
			* con i metodi che consentono la navigazione dell'istanza di processo, costruita da engine 
			* quando si espleta una nuova richiesta.
			*
			* Inoltre workflow ?la classe che lancia fisicamente le eccezioni che provengono dall'engine.
			* La classe ?in grado di lanciare eventi (eredita EventMaker):
			*
			* throwEvent( RestartedWorkflowEvent(this) );
			* throwEvent( StartedWorkflowEvent(this) );
			* throwEvent ( ManualWorkflowEvent ( this ) );
			* throwEvent ( EndWorkflowEvent ( this ) );
			* throwEvent ( ErrorWorkflowEvent ( this ) );
			* 
			* Gli eventi lanciati sono catturati dalle classi che ereditano WorkflowListener.
			* Allo stato attuale non sono gestiti classi di ascolto.
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
			class Workflow : public IWorkflow, public WorkflowEngine::Criteria::Event::EventMaker
			{
				public:

					Workflow();

					/**
					* Costruttore della classe a partire dall'istanza di processo (Puntatore).
					*
					* @code
					* @endcode
					* @sa
					* @param 
					* @throws
					* @see init()
					* @return
					* @returns
					*/
					Workflow( WorkflowProcesses::WorkflowProcess* pInstance );
				
					/**
					* Costruttore della classe a partire dall'istanza di processo (Puntatore)
					* e della activity da cui partire.
					*
					* @code
					* @endcode
					* @sa
					* @param task ?la acticity da cui partire con il processo
					* @throws
					* @see init()
					* @return
					* @returns
					*/
					Workflow( WorkflowProcesses::WorkflowProcess* pInstance, WorkflowProcesses::Activity* task);
			        
					/**
					* Costruttore della classe a partire dall'Id di processo.
					*
					* @code
					* @endcode
					* @sa
					* @param 
					* @throws
					* @see init()
					* @return
					* @returns
					*/
					Workflow( const char* processID );
					
					virtual ~Workflow();

					Workflow* operator=( Workflow* w );

					/**
					* Esegue la partenza di in workflow cercando da prima un task di 
					* start e lanciandone l'esecuzione.
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
					//Any starting();
					int starting();

					/**
					* Predisposizione.
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
					//Any stopping();
					int stopping();

					/**
					* Predisposizione.
					* 
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
					//Any suspending(); 
					int suspending(); 			        

					/**
					* Setta il disable del trattamento degli errori.
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
					void setNoErrorManaging();

					/**
					* Associa il processo come processo padre.
					* Setta atrue il parametro father.
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
					void setFather();
			        
					/**
					* Associa il processo come restarted.
					* Setta a true il parametro restart.
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
					void setRestart();
			        
					/**
					* Associa al processo l'activity da cui partire.
					*
					* @code
					* @endcode
					* @sa
					* @param status ?la stringa che contiene l'activity da cui partire
					* @throws
					* @see
					* @return
					* @returns
					*/
					void setBeginTask( String status);
					void setBeginTask( String status, String code);

					void setBeginTask(string status, Common::FormalParameters& parameters);
				
					/**
					* Setta il livello di nesting a cui si trova un processo.
					*
					* @code
					* @endcode
					* @sa
					* @param Level ?l'intero che indica il livello
					* @throws
					* @see
					* @return
					* @returns
					*/
					void setLevel( int level );
					int getLevel();

					/**
					* Associa il processo come processo figlio.
					* Setta a true il parametro bWorkflowChild.
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
					void setWorkflowChild();
					void setWorkflowChild(Workflow* wfFather);

					/**
					* Associa ad un processo figlio l'id del padre.
					*
					* @code
					* @endcode
					* @sa
					* @param lValue ?l'id del processo da associare come padre
					* @throws
					* @see
					* @return
					* @returns
					*/
					void setParentProcess(const char* value) { process->setParentProcess(value);}
					const char* getParentProcess() { return process->getParentProcess();}

					/**
					* Associa il nome del task che ha lanciato il processo figlio.
					*
					* @code
					* @endcode
					* @sa
					* @param sValue ?il nome della task da conservare
					* @throws
					* @see
					* @return
					* @returns
					*/
					void setTaskParentProcess(const char* value) {process->setTaskParentProcess(value);}
					const char* getTaskParentProcess() {return process->getTaskParentProcess();}
					
					/**
					* Setta a true il parametro bAnchor associato al exit di un sottoprocesso
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
					void setAnchor() { bAnchor = true;}
					
					/**
					* Restituisce una istanza di processo
					*
					* @code
					* @endcode
					* @sa
					* @param
					* @throws
					* @see
					* @return ProcessInstance (Puntatore)
					* @returns
					*/
					 WorkflowProcesses::WorkflowProcess* getProcess();
					
					/**
					* Restituisce lo stato di stop del workflow
					*
					* @code
					* @endcode
					* @sa
					* @param
					* @throws
					* @see
					* @return true se il workflow ?in stato stop
					* @returns
					*/
					bool isStoppedByTask();

					void setStatus(int st);
					int getStatus();

					/**/
					//Invocati da ProcessActionAttach
					void addAttribute2Process(WorkflowRelevantData::Attributes&);
					void addAttribute2Process(WorkflowRelevantData::Attribute&);

					WorkflowRelevantData::Attributes& getAttributes();

					void setExit2Manage() { process->setExit2Manage();}


				private:
			        
					enum WorkflowStatus
					{
						RUNNING,
						STOPPED_BY_MANUALTASK    
					} status;

					/**
					* Setta il workflow nello stato di running
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
					void init();
					

					/**
					* Esegue la navigazione dell'istanza di workflow individuando la task 
					* da eseguire e lanciandole l'esecuzione anche per la action associata.
					*
					* @code
					* @endcode
					* @sa
					* @param task ?la acticity da eseguire.
					* @throws
					* @see
					* @return
					* @returns
					*/
					int explore( WorkflowProcesses::Activity* task);

					
					/**
					* Setta il workflow nello stato di running
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
					TaskList getNextTask( WorkflowProcesses::Activity* task);
					

					/**
					* 
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
					void manageMessageFlows( WorkflowProcesses::Activity* task);

					/**
					* Setta il workflow nello stato di stopped by task
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
					void setStoppedByTask() {status = STOPPED_BY_MANUALTASK;}
					
					WorkflowManager*    wfm;
					WorkflowProcesses::WorkflowProcess*    process;
			        
					int     iRequestID;
					int     iLevel;
					bool    bError;
					bool    bFather;
					bool    bRestart;
					String  sBeginTask;
					String sCode;

					Common::FormalParameters eventParameters;

					//se valorizzato a true indica che i workflow in esecuzione
					//?stato generato da un task di pattern.
					//eliminata per modifica DataBase1.2 loading/saving process
					bool bWorkflowChild;

					//eliminata per modifica DataBase1.2 loading/saving process
					bool bWorkflowStoppedBySplitTask;

					/*
						Utilizzati per il task sub-flow ed il corrispondente exit.
					*/
					String parentProcess;
					bool bAnchor;

					bool checkResult(WorkflowProcesses::Transition* transition, WorkflowProcesses::Activity* task);

					//Add attribute al process
					/*
						Utilizzate per aggiungere le variabili definite a runtime(processid, level, etc...)
					*/
					void addAttribute2Process(const char* sName, int iValue);
					void addAttribute2Process(const char* sName, const char* acValue);

					//utilizzato per memorizzare gli attributi del processo prima che venga cancellato.
					WorkflowRelevantData::Attributes vAttributes;

					bOS::Core::Mutex mtxNrExecuted;

					bOS::Core::Semaphore smphWorkflowChildren;
					Workflow* wfFather;
			};
		}
	}
}

#endif //__WORKFLOW_H__


