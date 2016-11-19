#ifndef __BOS_RESULTSET_RECORD_H__
#define __BOS_RESULTSET_RECORD_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetField.h"

namespace bOS
{
    namespace SQL
    {
		typedef vector<ResultSetField*> ResultSetFieldList;

		class BOS_API ResultSetRecord
		{
		public:
			ResultSetRecord();
			virtual ~ResultSetRecord();

			void clear();
			ResultSetField* add(const char* acName);
			void add(ResultSetField*);
			int size();
			ResultSetField* at(int i);

		private:
			ResultSetFieldList vFields;
		};
	}
}

#endif //__BOS_RESULTSET_RECORD_H__