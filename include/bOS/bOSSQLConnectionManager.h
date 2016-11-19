#ifndef __BOS_SQL_CONNECTIONMANAGER_H__
#define __BOS_SQL_CONNECTIONMANAGER_H__

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSMutex.h"

#include "bOSSQLConnection.h"
#include "bOSSQLConnectionPool.h"
#include "bOSSQLConnectionData.h"

namespace bOS
{
    namespace SQL
    {
        class BOS_API SQLConnectionManager 
        {
            public:

				enum DataBaseType
				{
					ODBC_INTERFACE,
					SQLITE3,
					MYSQL
				};

				SQLConnectionManager();
                virtual ~SQLConnectionManager();

				void init(DataBaseType dbt = ODBC_INTERFACE);

				virtual void createPool( SQLConnectionData*, unsigned int iMin, unsigned int iMax);

                virtual SQLConnection* get();
                virtual SQLConnection* get( unsigned int uiTimes, unsigned int uiMilliSeconds);
                virtual void release( SQLConnection* cn );

            protected:

                DataBaseType iDBType;
                unsigned int iMin;
                unsigned int iMax;

				SQLConnectionData* connectionData;
				SQLConnection* getNewConnection();

            private:
                
                SQLConnectionPool	vPool;
				bOS::Core::Mutex	mutex;
        };
    }
};

#endif //__BOS_SQL_CONNECTIONMANAGER_H__


