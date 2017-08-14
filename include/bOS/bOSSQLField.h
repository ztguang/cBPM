#ifndef _BOS_SQL_FIELD_H_
#define _BOS_SQL_FIELD_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

namespace bOS
{
	namespace SQL
	{
		class SQLField;
		typedef vector<SQLField> SQLFieldList;

		union FieldValue
		{
			char sValue[65535];
			long lValue;
			int iValue;
		};

		

		class BOS_API SQLField
		{
		public:
			
			enum FieldType
			{
				NONE,
				LONG,
				INT,
				STRING,
				NUMBER,
				DATE,
				LONGTEXT
			};

			SQLField(const char* acName, String& acValue);
			SQLField(const char* acName, const char* acValue);
			SQLField(const char* acName, long lValue);
			SQLField(const char* acName, int iValue);
			SQLField( const SQLField&);
			virtual ~SQLField();

			String sName;
			FieldType iType;
			unsigned int size;
			int decim_size;
			int nullable; // 0: NOT-NULL,1: NULL,2: NOT-KNOWN

			String getValue();
			FieldValue uValue;

		private:

		};
	}
}

#endif //_SQL_FIELD_H_ 
