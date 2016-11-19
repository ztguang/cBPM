#include "CommonDefines.h"

#include "bOS.h"

#include "bOSString.h"
using namespace bOS::CoreString;

#include "bOSCollection.h"
using namespace bOS::Collections;

Collection::Collection()
{
}

Collection::~Collection()
{
	this->removeAll();	
}

bool Collection::add(CollectionEntry* entry2Add)
{
	Mutex::Lock locker(mtxEntries);

	CollectionEntry* entry = NULL;

	unsigned int uiSize = vEntries.size();
	for ( unsigned int ui=0; ui<uiSize; ui++)
	{
		entry = vEntries.at(ui);

		if ( entry->equalTo (entry2Add) )
		{
			return false;
		}
	}

	vEntries.push_back(entry2Add);

	return true;
}

void Collection::append(CollectionEntry* entry)
{
	vEntries.push_back(entry);
}

CollectionEntry* Collection::get (CollectionEntry* entry2Found)
{
	Mutex::Lock locker(mtxEntries);

	CollectionEntry* entry = NULL;

	unsigned int uiSize = vEntries.size();
	for ( unsigned int ui=0; ui<uiSize; ui++)
	{
		entry = vEntries.at(ui);

		if ( entry->equalTo (entry2Found) )
		{
			return entry;
		}
	}

	return NULL;
}

CollectionEntry* Collection::operator[] (unsigned int ui)
{
	return this->at(ui);
}

CollectionEntry* Collection::at(unsigned int ui)
{
	Mutex::Lock locker(mtxEntries);

	unsigned uiSize=vEntries.size();

	if ( ui<uiSize)
	{
		return vEntries.at(ui);
	}

	return NULL;
}

CollectionEntry* Collection::nots_at(unsigned int ui)
{
	unsigned uiSize=vEntries.size();

	if ( ui<uiSize)
	{
		return vEntries.at(ui);
	}

	return NULL;
}


unsigned int Collection::size()
{
	Mutex::Lock locker(mtxEntries);

	return vEntries.size();
}

void Collection::clear()
{
	this->removeAll();
}

bool Collection::remove (CollectionEntry* entry)
{
	Mutex::Lock locker(mtxEntries);
	
	EntriesList::iterator iEntry;

    for( iEntry = vEntries.begin(); iEntry != vEntries.end(); iEntry++ )
    {
        if ( (*iEntry)->equalTo (entry) )
        {
            delete (*iEntry);
            vEntries.erase(iEntry);
            return true;
        }
    }

	return false;
}

bool Collection::update (CollectionEntry* entry)
{
	Mutex::Lock locker(mtxEntries);
	
	EntriesList::iterator iEntry;

    for( iEntry = vEntries.begin(); iEntry != vEntries.end(); iEntry++ )
    {
        if ( (*iEntry)->equalTo (entry) )
        {
            delete (*iEntry);
			(*iEntry) = entry;
            return true;
        }
    }

	return false;
}

void Collection::removeAll()
{
	Mutex::Lock locker(mtxEntries);

	unsigned int uiSize = vEntries.size();
	for ( unsigned int ui=0; ui<uiSize; ui++)
	{
		delete vEntries.at(ui);
	}

	vEntries.clear();
}

void Collection::lock()
{
	mtxEntries.lock();
}

void Collection::unlock()
{
	mtxEntries.unlock();
}
