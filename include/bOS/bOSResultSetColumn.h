#ifndef _BOS_ResultSet_FIELD_H_
#define _BOS_ResultSet_FIELD_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

namespace bOS
{
	namespace SQL
	{
		class BOS_API ResultSetColumn
		{
		public:
			char title[51];
			int type;
			unsigned int size;
			int decim_size;
			int nullable; // 0: NOT-NULL,1: NULL,2: NOT-KNOWN

		};
	}
}

#endif //_BOS_ResultSet_FIELD_H_
