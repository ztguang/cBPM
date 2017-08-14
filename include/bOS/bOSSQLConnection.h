#ifndef __BOS_SQL_CONNECTION_H__
#define __BOS_SQL_CONNECTION_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSSQLCommands.h"

namespace bOS
{
    namespace SQL
    {
        class ResultSet;

        class BOS_API SQLConnection 
        {
            public:
				
				SQLConnection();
                virtual ~SQLConnection();

                virtual bool isConnected() = 0;
                virtual long execute( const char* acSQL ) = 0;
				virtual long executePrepare( SQLCommands& ) = 0;
				virtual ResultSet* executeQuery( const char* acSQL ) = 0;
				virtual ResultSet* executeQuery(const char* acSQL,int iCursorType,bool bScrollable) = 0;

				//useful for retriving autoincrement field in "INSERT" SQL.
				virtual unsigned long getAutoIncrement() = 0;

				//Transaction Manager
				virtual bool supportTransaction() = 0;
                virtual void beginTrans() = 0;
                virtual void commit() = 0;
                virtual void rollback() = 0;
                
                virtual void setAutoCommit(bool bCommit = true);
				bool isAutoCommit();

				void setTimeout(int _timeout);
				int getTimeout();

            protected:

				bool bAutoCommit;
				int iTimeout;

            private:

				//open, close methods are invoked by ConnectionManager
                virtual void open() = 0;
                virtual void close() = 0;

                friend class SQLConnectionManager;
				friend class SQLSmartConnection;
				friend class SQLConnectionPoolEntry;
        };
    }
};

#endif //__BOS_SQL_CONNECTION_H__
