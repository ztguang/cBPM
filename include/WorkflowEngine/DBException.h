#ifndef _DB_EXCEPTION_H_
#define _DB_EXCEPTION_H_

//TO_BE_EXPORTED

#include "CriteriaCommonDefines.h"

#include "bOS.h"
#include "bOSException.h"
using namespace bOS::Exception;

namespace DataManager
{
	namespace DataBase
	{
		const String DB_UNKNOW_ERROR	= "Unknow Error";
		const String ENV_VAR_NOTDEFINED = "DB Environment Variable is not defined.";
		const String XFS_FILE_NOT_FOUND	= "Impossible to open DB. One or more file not found.";
		const String XFS_FILE_NOT_WRITE = "Impossible to write File.";

		const String DB_RECORD_NOT_FOUND	= "Impossible to find a record.";
		const String DB_RECORD_ALREADY_PRESENT = "Impossible to insert record. Unique Constraint.";

		const String DB_DIRECTORY_NOT_FOUND	= "Imposible to retrive Directory Infos.";

		class ENGINE_API DBException : public BaseException
		{
			public:

				DBException(const String & message ) : BaseException( message ) {};

				DBException() : BaseException( DB_UNKNOW_ERROR ) {};

				DBException( const String & message, const int lineNumber )
					: BaseException(message, lineNumber) {};

				virtual ~DBException() {};
		};
	}
}

#endif //_DB_EXCEPTION_H_

