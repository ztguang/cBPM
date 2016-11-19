#ifndef __BOS_BASE_EXCEPTION_H__
#define __BOS_BASE_EXCEPTION_H__

#include "bOS.h"
#include "bOSString.h"
using namespace bOS::CoreString;

//TO_BE_EXPORTED

namespace bOS
{
	namespace Exception
	{
		class BOS_API BaseException
		{
			public:

				BaseException();

				BaseException( const String & message );

				BaseException( const String & message, const int lineNumber );

				virtual ~BaseException();

	            String getMessage();

		    protected:

			   String sMessage;

			private:
		};
    }
};

#endif

