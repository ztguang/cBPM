
#ifndef __FE_WORKFLOWEXCEPTION_H__
#define __FE_WORKFLOWEXCEPTION_H__

//TO_BE_EXPORTED


#include "bOS.h"
#include "bOSException.h"
using namespace bOS::Exception;

#define WE_NOT_FOUND                "Workflow not found"
#define WE_CANT_START_WORKFLOW      "Workflow cannot be started. Can't create thread!"


namespace WorkflowEngine
{
	namespace Criteria
	{
		namespace Core
		{
			/**
			* La classe deriva bOSException da bOS.
			* Ha la rsponsabilità di intercettare le eccezioni sollevate da WorkflowManager e di presentarne il messaggio.
			*
			* Le eccezioni intercettate vengono restituite all'interno del motore e non sono visibili dall'esterno.
			*
			* I messaggi delle eccezioni sono generate dal codice
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
			class ENGINE_API WorkflowException : public BaseException
			{
				public:

					WorkflowException(const String & message ) : BaseException( message ) {};

					WorkflowException() : BaseException( WE_NOT_FOUND ) {};

					WorkflowException( const String & message, const int lineNumber )
						: BaseException(message, lineNumber) {};

					virtual ~WorkflowException() {};
			};
		}
	}
}

#endif


