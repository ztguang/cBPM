#ifndef __BOS_ResultSet_H__
#define __BOS_ResultSet_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSResultSetMetaData.h"
#include "bOSResultSetRecord.h"
#include "bOSResultSetField.h"

namespace bOS
{
    namespace SQL
    {
		class BOS_API ResultSet
        {
            public:

				ResultSet();
				virtual ~ResultSet();

                virtual bool eof()				= 0;
                virtual bool moveFirst()		= 0;
                virtual bool moveLast()			= 0;
                virtual bool moveNext()			= 0;
                virtual bool movePrevious()		= 0;
                virtual long getRecordCount()	= 0;

				void close();
				
				virtual ResultSetMetaData* getMetaData() = 0;
				virtual ResultSetRecord* getRecord() = 0;

				virtual bool bind(int col_no,char* buff,int buff_len) = 0;
				
            protected:

				//ResultSetRecords vRows;
                //int iRow;

            private:
        };
    }
};

#endif
