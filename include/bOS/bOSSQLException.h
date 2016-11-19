#ifndef __BOS_SQLEXCEPTION_H__
#define __BOS_SQLEXCEPTION_H__

//TO_BE_EXPORTED
#include "bOS.h"
#include "bOSException.h"

namespace bOS
{
    namespace SQL
    {
		#define SQL_FATAL_ERROR              "RDBMS unknown error. Please contact an administrator."
		#define SQL_UNKNOWN_DATABASE         "The database you are trying to connect to is not currently supported. Please switch to a supported database and try again."
		#define SQL_ALREADY_CONNECTED        "The connection you are trying to open it's already connected to the database. Please disconnect before connecting to a different database."
		#define SQL_NOT_CONNECTED            "The connection you are trying to use it's not connected to any database. Please connect before executing commands."
		#define SQL_CONNECTION_NOT_AVAILABLE "No Connection available. Please do increase the pool size."
		#define SQL_DRIVER_NOT_FOUND         "SQL Driver not found!"
		#define SQL_DATA_LOCKED              "A database lock has been encountered."
		#define SQL_FETCH_ERROR              "An error was encountered during a fetch operation."
		#define SQL_FIELD_NOT_FOUND          "ResultSet doesn't contain field with such name"
		#define SQL_STATEMENT_NOT_FOUND      "The statement was not found on this database. Please check the statement name and retry..."
		#define SQL_INVALID_STATEMENT        "The statement is invalid and could not be executed."
		#define SQL_INVALID_PARAMETER        "The parameter value cannot be set for output parameters or return values."
		#define SQL_PARAMETER_NOT_FOUND      "This statement does not contains the parameter. Please check the parameter name and retry."
		#define SQL_OUT_OF_MEMORY             "No more memory is available for this process."
        
		class BOS_API SQLException : public bOS::Exception::BaseException 
        {
            public:

                SQLException(const String & message ) : BaseException( message ) {};

                SQLException() : BaseException( SQL_FATAL_ERROR ) {};

                SQLException( const String & message, const int lineNumber ) 
                    : BaseException(message, lineNumber) {};

                virtual ~SQLException() {};
        };
    }
};

#endif


