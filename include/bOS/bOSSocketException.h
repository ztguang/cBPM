#ifndef _SOCKET_EXCEPTION_H_
#define _SOCKET_EXCEPTION_H_

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSException.h"

enum SocketError
{
	UNKNOW,
	TIMEOUT
};

namespace bOS
{
	namespace Net
	{
		class BOS_API SocketRunTimeException : public std::runtime_error
		{
		public:
			explicit SocketRunTimeException(const std::string &what);
			virtual const char * what() const throw();

			int errornumber() const throw() { return errnum_; }

			~SocketRunTimeException() throw () { }

			SocketError error;

			

		private:
			// this will serve as a message returned from what()
			mutable std::string msg_;
			int errnum_;
		};

		// exception class which designates logic (programming) errors with sockets
		class BOS_API SocketLogicException : public std::logic_error
		{
		public:
			explicit SocketLogicException(const std::string &what)
				: std::logic_error(what)
			{
			}
		};
	}
}

#endif //

