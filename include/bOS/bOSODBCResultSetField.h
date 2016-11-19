#ifndef _BOS_ODBC_ResultSet_FIELD_H_
#define _BOS_ODBC_ResultSet_FIELD_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetField.h"

namespace bOS
{
	namespace SQL
	{
		namespace ODBC
		{
			class BOS_API ODBCResultSetField : public bOS::SQL::ResultSetField
			{
			public:

				ODBCResultSetField(const char* acName);
				ODBCResultSetField(const char* acName, String& acValue);
				ODBCResultSetField(const char* acName, const char* acValue);
				ODBCResultSetField(const char* acName, long lValue);
				ODBCResultSetField(const char* acName, int iValue);
				//ODBCResultSetField( const ODBCResultSetField&);
				~ODBCResultSetField();
			};
		}
	}
}

#endif //_BOS_ODBC_ResultSet_FIELD_H_ 
