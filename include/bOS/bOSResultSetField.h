#ifndef _BOS_RESULT_SET_FIELD_H_
#define _BOS_RESULT_SET_FIELD_H_

//TO_BE_EXPORTED

#include "bOS.h"

#include "bOSString.h"
#include "bOSStringBuffer.h"
using namespace bOS::CoreString;

namespace bOS
{
	namespace SQL
	{
		enum FieldType
		{
			VARCHAR,
			NUMERIC, 
			INTEGER,
			AUTOINCREMENT,
			DATE
		};

		class BOS_API ResultSetField
		{
		public:
			ResultSetField(const char* acName);
			//ResultSetField(const char* acName, String& acValue, int iSize=0);	//ztg delete
			ResultSetField(const char* acName, String acValue, int iSize=0);

			ResultSetField(const char* acName, const char* acValue, int iSize = 0);
			ResultSetField(const char* acName, long lValue);
			ResultSetField(const char* acName, int iValue);

			virtual ~ResultSetField();

			void setAutoIncrement() { iType = AUTOINCREMENT;}

			String sName;
			int iType;
			StringBuffer sValue;
			int iSize;

		private:

		};
	}
}

#endif //_BOS_RESULT_SET_FIELD_H_