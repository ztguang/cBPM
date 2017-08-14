
#ifndef __FLOWENGINE_EXCEPTION_H__
#define __FLOWENGINE_EXCEPTION_H__

#define FILE_TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

enum ENGINE_API FE_ErrorCode
{
	FE_OK = 0,
    FE_BAD_ARGUMENT,                    //Engine Constructor instancied with no-valid DB session 
    FE_CONFIG_NOTREADEN,                //it's impossible to read configuration file. 
    FE_JOBM_NOTCREATED,                 //it's impossible to instance jobs manager

	FE_CONN_GETFREE,
	FE_CONN_ENDTRANS,
	FE_CONN_LETFREE,
	FE_DB_ERROR,
    FE_PROCESS_I_ID_NOTVALID,
	FE_PROCESS_T_NOTFOUND,
	FE_PROCESS_T_NORUN,
	FE_PROCESS_I_NOTFOUND,
	FE_PROCESS_I_TASK_BEGIN_NOTFOUND,
	FE_PROCESS_MOREONEERROR,
	FE_PROCESS_NOTASKPERERROR,
	FE_THREAD_NOTCREATED,	
	FE_MUTEX_NOTCREATED,
	FE_MUTEX_LOCK,
	FE_MUTEX_UNLOCK,
	FE_TRANSITION_NOTFOUND,
	FE_TASK_NOTFOUND,
    FE_JOBM_ERROR,
    FE_JOBM_JOB_JUST_PRESENT,
	FE_TASK_TYPE_NOTMANAGED,
	FE_TASK_TYPE_ERROR,
	FE_TASK_ACTIONTYPE_ERROR,
	FE_TASK_TASKACTION_NONE, //
    FE_TASK_TASKACTION_ERROR,
    FE_TASK_TASKACTION_INVALID,
    FE_TASK_TASKACTION_PROCESS_ERROR,
    FE_TASK_TASKACTION_DB_INVALID,
    FE_TASK_TASKACTION_DB_ERROR,
	FE_TASK_SUBFLOW_STOPPED_BY_TASK,
	FE_TASK_STOPPED_BY_WAINTING_EVENT,
	FE_RESULTCODE_NOTFOUND, 

	FE_TASK_MAIL_ERROR
};

const String FE_OK_DESC						="All Okey.";
const String FE_BAD_ARGUMENT_DESC				="Bad Argument: ";
const String FE_CONN_GETFREE_DESC				="Unable to get a free connection to DataBase.";
const String FE_CONN_LETFREE_DESC				="Unable to let a free connection to DataBase.";
const String FE_CONN_ENDTRANS_DESC 			="Unable to end transaction(commit/rollback).";
const String FE_DB_ERROR_DESC					="Impossible to perform DataBase Transaction.";
const String FE_PROCESS_T_NOTFOUND_DESC		="Impossible to load ProcessTemplate. Process Not Found.";
const String FE_PROCESS_T_NORUN_DESC			="Impossible to create ProcessInstance from a ProcessTemplate not Runnable.";
const String FE_PROCESS_I_NOTFOUND_DESC		="Impossible to load ProcessInstance. Process Not Found.";
const String FE_PROCESS_I_BEGIN_NOTFOUND_DESC	="Impossible to execute ProcessInstace. Begin Task not found.";
const String FE_THREAD_NOTCREATED_DESC 		="Impossible to create a new Thread.";

const String FE_MUTEX_NOTCREATED_DESC 			="Impossible to create a new Mutex.";
const String FE_MUTEX_LOCK_DESC 			    ="Impossible to lock Mutex.";
const String FE_MUTEX_UNLOCK_DESC 			    ="Impossible to unlock Mutex.";

const String FE_TRANSITION_NOTFOUND_DESC		="Impossible to found a transition for executing value.";
const String FE_TASK_NOTFOUND_DESC 			="Impossible to found the task.";
const String FE_JOBM_NOTCREATED_DESC 			="Impossible to create a Jobs Manager.";

const String FE_CONFIG_NOTREADEN_DESC		            ="To define.";
const String FE_PROCESS_I_ID_NOTVALID_DESC		        ="To define.";
const String FE_PROCESS_I_TASK_BEGIN_NOTFOUND_DESC	    ="To define.";
const String FE_PROCESS_MOREONEERROR_DESC		        ="To define.";
const String FE_PROCESS_NOTASKPERERROR_DESC				="To define.";
const String FE_JOBM_ERROR_DESC							="To define.";
const String FE_JOBM_JOB_JUST_PRESENT_DESC		        ="To define.";
const String FE_TASK_TYPE_NOTMANAGED_DESC		        ="To define.";
const String FE_TASK_TYPE_ERROR_DESC		            ="To define.";
const String FE_TASK_ACTIONTYPE_ERROR_DESC		        ="To define.";
const String FE_TASK_TASKACTION_NONE_DESC		        ="To define.";
const String FE_TASK_TASKACTION_ERROR_DESC		        ="To define.";
const String FE_TASK_TASKACTION_INVALID_DESC	        ="To define.";
const String FE_TASK_TASKACTION_PROCESS_ERROR_DESC	    ="To define.";
const String FE_TASK_TASKACTION_DB_INVALID_DESC			="To define.";
const String FE_TASK_TASKACTION_DB_ERROR_DESC	        ="To define.";

const String FE_UNKNOW_ERROR	="Unknow Error.";

namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			/**
			* La classe ha la rsponsabilit?di intercettare le eccezioni sollevate da 
			* Engine e di presentarne il messaggio.
			*
			* Le eccezioni intercettate vengono restituite all'esterno  del motore e 
			* vengono gestite dalle wapi per la visualizzazione dell'errore
			*
			* Gli errori appartengono ad un tipo enumerato
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

			class ENGINE_API EngineException : public bOS::Exception::BaseException
			{
			public:

				EngineException(int iCode, const char* acErrPlus="", const char* acAction="") : BaseException()
				{ 
					_errCode = iCode;

					sMessage=acAction;
					sMessage+=" ";
					sMessage+=getErrorDescription();
					sMessage+=String(".");
					sMessage+=String(acErrPlus);
				}

				virtual ~EngineException() {;}
				int getErrorCode() { return _errCode; }

			private:
				int _errCode;

				String getErrorDescription() 
				{
					switch ( _errCode ) 
					{
						case FE_OK:                             return FE_OK_DESC;
						case FE_BAD_ARGUMENT:                   return FE_BAD_ARGUMENT_DESC;
						case FE_CONFIG_NOTREADEN:               return FE_CONFIG_NOTREADEN_DESC;
						case FE_JOBM_NOTCREATED:                return FE_JOBM_NOTCREATED_DESC;
						case FE_CONN_GETFREE:                   return FE_CONN_GETFREE_DESC;
						case FE_CONN_ENDTRANS:                  return FE_CONN_ENDTRANS_DESC;
						case FE_CONN_LETFREE:                   return FE_CONN_LETFREE_DESC;
						case FE_DB_ERROR:                       return FE_DB_ERROR_DESC;
						case FE_PROCESS_I_ID_NOTVALID:          return FE_PROCESS_I_ID_NOTVALID_DESC;
						case FE_PROCESS_T_NOTFOUND:             return FE_PROCESS_T_NOTFOUND_DESC;
						case FE_PROCESS_T_NORUN:                return FE_PROCESS_T_NORUN_DESC;
						case FE_PROCESS_I_NOTFOUND:             return FE_PROCESS_I_NOTFOUND_DESC;
						case FE_PROCESS_I_TASK_BEGIN_NOTFOUND:  return FE_PROCESS_I_TASK_BEGIN_NOTFOUND_DESC;
						case FE_PROCESS_MOREONEERROR:           return FE_PROCESS_MOREONEERROR_DESC;
						case FE_PROCESS_NOTASKPERERROR:         return FE_PROCESS_NOTASKPERERROR_DESC;
						case FE_THREAD_NOTCREATED:              return FE_THREAD_NOTCREATED_DESC;
						case FE_MUTEX_NOTCREATED:               return FE_MUTEX_NOTCREATED_DESC;
						case FE_MUTEX_LOCK:                     return FE_MUTEX_LOCK_DESC;
						case FE_MUTEX_UNLOCK:                   return FE_MUTEX_UNLOCK_DESC;
						case FE_TRANSITION_NOTFOUND:            return FE_TRANSITION_NOTFOUND_DESC;
						case FE_TASK_NOTFOUND:                  return FE_TASK_NOTFOUND_DESC;
						case FE_JOBM_ERROR:                     return FE_JOBM_ERROR_DESC;
						case FE_JOBM_JOB_JUST_PRESENT:          return FE_JOBM_JOB_JUST_PRESENT_DESC;
						case FE_TASK_TYPE_NOTMANAGED:           return FE_TASK_TYPE_NOTMANAGED_DESC;
						case FE_TASK_TYPE_ERROR:                return FE_TASK_TYPE_ERROR_DESC;
						case FE_TASK_ACTIONTYPE_ERROR:          return FE_TASK_ACTIONTYPE_ERROR_DESC;
						case FE_TASK_TASKACTION_ERROR:          return FE_TASK_TASKACTION_ERROR_DESC;
						case FE_TASK_TASKACTION_NONE:			return FE_TASK_TASKACTION_NONE_DESC;
						case FE_TASK_TASKACTION_INVALID:        return FE_TASK_TASKACTION_INVALID_DESC;
						case FE_TASK_TASKACTION_PROCESS_ERROR:  return FE_TASK_TASKACTION_PROCESS_ERROR_DESC;
						case FE_TASK_TASKACTION_DB_INVALID:     return FE_TASK_TASKACTION_DB_INVALID_DESC;
						case FE_TASK_TASKACTION_DB_ERROR:       return FE_TASK_TASKACTION_DB_ERROR_DESC;
					
						default:
							return FE_UNKNOW_ERROR;
					}
				}
			};
		}
	}
}

#endif



