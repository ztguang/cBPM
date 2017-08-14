#ifndef __BOS_SQL_CONNECTION_POOL_H__
#define __BOS_SQL_CONNECTION_POOL_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSMutex.h"

#include "bOSSQLConnection.h"
#include "bOSSQLException.h"

namespace bOS
{
    namespace SQL
    {
		class SQLConnection;

		class BOS_API SQLConnectionPoolEntry
        {
		public:
			SQLConnectionPoolEntry(SQLConnection*);
			virtual ~SQLConnectionPoolEntry();

			bool isFree();

			void setBusy();
			void setFree();

			SQLConnection* getConnection() { return connection;}

		private:
            bool	bFree;
            SQLConnection* connection;
        };

		typedef vector<SQLConnectionPoolEntry*> SQLConnectionPool;
    }
};

#endif //__BOS_SQL_CONNECTION_POOL_H__


