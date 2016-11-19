#ifndef __BOS_SQL_CONNECTION_DATA_H__
#define __BOS_SQL_CONNECTION_DATA_H__

//TO_BE_EXPORTED

#include "bOS.h"

namespace bOS
{
	namespace SQL
	{
		class BOS_API SQLConnectionData
		{
		public:
			
			SQLConnectionData() {;}
			virtual ~SQLConnectionData() {;}

			virtual void init(SQLConnectionData*) = 0 ;
		};
	}
}


#endif //__BOS_SQL_CONNECTION_INFO_H__