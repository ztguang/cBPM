#ifndef _SQL_SMART_CONNECTION_H_
#define _SQL_SMART_CONNECTION_H_

//TO_BE_EXPORTED
#include "bOS.h"

namespace bOS
{
    namespace SQL
    {
		class SQLConnectionManager;
		class SQLConnection;

		class BOS_API SQLSmartConnection
		{
		public:
			SQLSmartConnection();
			SQLSmartConnection(SQLConnectionManager*, SQLConnection*);
			virtual ~SQLSmartConnection();

			void init(SQLConnectionManager*, SQLConnection*);

			bool isConnectionOwner() { return bConnectionOwner;}

		private:
			SQLConnectionManager* manager;
			SQLConnection* connection;

			bool bConnectionOwner;
		};
	}
}

#endif //_SQL_SMART_CONNECTION_H_