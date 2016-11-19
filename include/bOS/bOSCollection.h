#ifndef _BOS_COLLECTIONS_COLLECTION_H_
#define _BOS_COLLECTIONS_COLLECTION_H_

//TO_BE_EXPORTED
#include "bOS.h"

#include "bOSCollectionEntry.h"
#include "bOSMutex.h"
#include "bOSSmartLocker.h"

namespace bOS
{
	namespace Collections
	{
		//TODO: Gestire la mappa.
		typedef vector<CollectionEntry*> EntriesList; 


		class BOS_API Collection
		{
		public:

			typedef bOS::Core::SmartLocker<Collection> Lock;

			Collection();
			virtual ~Collection();

			bool add(CollectionEntry*);
			void append(CollectionEntry*);
			CollectionEntry* get(CollectionEntry*);
			bool remove(CollectionEntry*);
			bool update(CollectionEntry* entry);
			
			//no thread safe. nots_at is used in method which includes Lock invocation
			CollectionEntry* nots_at(unsigned int ui);
			unsigned int nots_size() {return vEntries.size();}

			CollectionEntry* operator[] (unsigned int ui);
			CollectionEntry* at(unsigned int ui);
			unsigned int size();
			void clear();

			void lock();
			void unlock();

			

		protected:
			void removeAll();

			EntriesList vEntries;
			bOS::Core::Mutex mtxEntries;

		};
	}
};

#endif //_BOS_COLLECTIONS_COLLECTION_H_