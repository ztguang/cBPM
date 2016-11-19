#ifndef _BOS_COLLECTIONS_ENTRY_H_
#define _BOS_COLLECTIONS_ENTRY_H_

//TO_BE_EXPORTED
#include "bOS.h"

namespace bOS
{
	namespace Collections
	{
		class BOS_API CollectionEntry
		{
		public:

			CollectionEntry() {;}
			virtual ~CollectionEntry() {;}

			virtual bool equalTo(CollectionEntry*) = 0;

		};
	}
};

#endif //_BOS_COLLECTIONS_ENTRY_H_