#ifndef _BOS_RESULTSET_METADATA_H_
#define _BOS_RESULTSET_METADATA_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetColumn.h"

namespace bOS
{
	namespace SQL
	{
		typedef vector<ResultSetColumn*> Columns;

		class BOS_API ResultSetMetaData
		{
		public:
			ResultSetMetaData();
			virtual ~ResultSetMetaData();

			void setNumCols(int nrCols);
			int getColumnCount();
			void addColumn(ResultSetColumn*);
			ResultSetColumn* addColumn();

			ResultSetColumn* getColumn(unsigned int n);
			ResultSetColumn* getColumn(const char* acTitle);

			virtual void typeToString(int type,char* ret) = 0;
			virtual void nullableToString(int nullable,char* ret) = 0;

			virtual void clear();

		private:

			int iNumCols;
			Columns vColumns;
		};
	}
}

#endif