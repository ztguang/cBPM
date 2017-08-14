#ifndef __APPLICATION_EXCEPTION_H__
#define __APPLICATION_EXCEPTION_H__

//TO_BE_EXPORTED
#include "CriteriaCommonDefines.h"
#include "CommonDefines.h"

#include "bOS.h"
#include "bOSException.h"
using namespace bOS::Exception;

#define APPLICATION_NOT_FOUND	"Application not found"
#define FUNCTION_NOT_FOUND      "Function not found"
#define TYPE_NOT_MANAGED		"Application Type not managed"

namespace WorkflowEngine
{
	/**
	* Eredita da base exception e gestisce le eccezioni sollevate da ApplicationManager.
	* Presenta il messaggio APPLICATION_NOT_FOUND
	* @code
	* @endcode
	* @sa
	* @param
	* @throws
	* @see
	* @return
	* @returns
	*/
	class ENGINE_API ApplicationException : public BaseException
	{
		public:

			ApplicationException(const String & message ) : BaseException( message ) {};

			ApplicationException() : BaseException( APPLICATION_NOT_FOUND ) {};

			ApplicationException( const String & message, const int lineNumber )
				: BaseException(message, lineNumber) {};

			virtual ~ApplicationException() {};
	};

	#define SOCKET_NOT_INITIALIZE       "Impossible to initialize sockets."

	/**
	* Eredita da base exception e gestisce le eccezioni sollevate da ApplicationManager.
	* Presenta il messaggio SOCKET_NOT_INITIALIZE
	* @code
	* @endcode
	* @sa
	* @param
	* @throws
	* @see
	* @return
	* @returns
	*/
	class ENGINE_API ChannelException : public BaseException
	{
		public:

			ChannelException(const String & message ) : BaseException( message ) {};

			ChannelException() : BaseException( SOCKET_NOT_INITIALIZE ) {};

			ChannelException( const String & message, const int lineNumber )
				: BaseException(message, lineNumber) {};

			virtual ~ChannelException() {};
	};

	#define LIBRARY_NOT_INITIALIZE				"Impossible to initialize dynamic library."
	#define INSTANCEAPPLICATION_NOT_INITIALIZE  "Impossible to initialize instance application from library."
	#define DELETEAPPLICATION_NOT_INITIALIZE	"Impossible to initialize delete application from library."
	#define EXECUTEAPPLICATIONAPI_NOT_INITIALIZE "Impossible to initialize execute application api from library."
	class ENGINE_API DynamicLibraryException : public BaseException
	{
		public:

			DynamicLibraryException(const String & message ) : BaseException( message ) {};

			DynamicLibraryException() : BaseException( LIBRARY_NOT_INITIALIZE ) {};

			DynamicLibraryException( const String & message, const int lineNumber )
				: BaseException(message, lineNumber) {};

			virtual ~DynamicLibraryException() {};
	};

	class ENGINE_API ProcessExecutionException : public BaseException
	{
		public:

			ProcessExecutionException(const String & message ) : BaseException( message ) {};

			ProcessExecutionException() : BaseException( LIBRARY_NOT_INITIALIZE ) {};

			ProcessExecutionException( const String & message, const int lineNumber )
				: BaseException(message, lineNumber) {};

			virtual ~ProcessExecutionException() {};
	};
}

#endif //__APPLICATION_EXCEPTION_H__


