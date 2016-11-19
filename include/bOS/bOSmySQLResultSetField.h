#ifndef _BOS_MYSQL_ResultSet_FIELD_H_
#define _BOS_MYSQL_ResultSet_FIELD_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetField.h"

namespace bOS
{
	namespace SQL
	{
		namespace mySQL
		{
			class BOS_API mySQLResultSetField : public bOS::SQL::ResultSetField
			{
			public:

				mySQLResultSetField(const char* acName);
				mySQLResultSetField(const char* acName, String& acValue);
				mySQLResultSetField(const char* acName, const char* acValue);
				mySQLResultSetField(const char* acName, long lValue);
				mySQLResultSetField(const char* acName, int iValue);
				//ODBCResultSetField( const ODBCResultSetField&);
				~mySQLResultSetField();
			};
		}
	}
}

#endif //_BOS_MYSQL_ResultSet_FIELD_H_ 
