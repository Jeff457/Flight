#include "LinkedHashedEntry.h"
#include "NotFoundException.h"
#include <vector>

#ifndef _HASH_TABLE
#define _HASH_TABLE

const int TABLE_SIZE = 41;

template<class KeyType, class ItemType>
class HashTable
{
private:
	LinkedHashedEntry<KeyType, ItemType>** table;
	int itemCount;

	// Compute hashed index into the array using ( (prime * key + prime) % LARGE_PRIME ) % TABLE_SIZE
	int getHashIndex(const KeyType& key) const;

	/** Copies entries over from existing hash table.
	@post  Duplicate Hash Table; since copied items have the same key, they will have the same hashed index. */
	void copyHashTable(const HashTable<KeyType, ItemType>& aHashTable);

public:
	HashTable();
	HashTable(const HashTable& aHashTable);
	~HashTable();

	HashTable<KeyType, ItemType>& operator=(const HashTable<KeyType, ItemType>& aHashTable);

	/** Retrieves an item with a given search key.
	@post  If the retrieval is successful, the item is returned.
	@param key  The search key of the item to be retrieved.
	@return  The item associated with the search key.
	@throw NotFoundException if the item does not exist. */
	ItemType find(const KeyType& key) const;

	/** Retrieves all items in the hash table. */
	vector<ItemType> getAll() const;

	/** Returns the number of entries in the Hash Table. */
	int getTotalEntries() const { return itemCount; }

	/** Inserts an item into the HashTable according to the item's search key. */
	void add(const KeyType& key, const ItemType& value);
	
	/** Removes an item with the given search key from the hash table. 
	@throw NotFoundException if the item does not exist. */
	void remove(const KeyType& key);

	/** Sets itemCount to 0.  */
	void clear();

};

//==============================
//		Implementation
//==============================


//==============================
//		Private Methods
//==============================

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getHashIndex(const KeyType& key) const
{
	return ( ( ( 17 * key + 5 ) % 997) % TABLE_SIZE );
}  // end getHashCode

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::copyHashTable(const HashTable<KeyType, ItemType>& aHashTable)
{
	for (int i = 0; i < aHashTable.getTotalEntries(); i++)
	{
		if (aHashTable[i] == nullptr)
			continue;
		else
			table[i] = aHashTable[i];
	}
}  // end copyHashTable


//==============================
//		Public Methods
//==============================

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable()
{
	table = new LinkedHashedEntry<KeyType, ItemType>*[TABLE_SIZE];
	itemCount = 0;
	for (size_t i = 0; i < TABLE_SIZE; i++)
		table[i] = nullptr;
}  // end constructor

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(const HashTable& aHashTable) : itemCount(0)
{
	*this = aHashTable;
}  // end copy constructor

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>& HashTable<KeyType, ItemType>::operator=(const HashTable<KeyType, ItemType>& aHashTable)
{
	if (this == &aHashTable)
		return *this;

	if (itemCount != 0)
	{
		clear();
		delete[] table;
		table = nullptr;
	}

	if (aHashTable.getTotalEntries() == 0)
	{
		table = new LinkedHashedEntry<KeyType, ItemType>*[TABLE_SIZE];
		itemCount = 0;
	}
	else
	{
		table = new LinkedHashedEntry<KeyType, ItemType>*[TABLE_SIZE];
		itemCount = aHashTable.getTotalEntries();
		copyHashTable(aHashTable);
	}
}  // end overloaded = operator

template<class KeyType, class ItemType>
ItemType HashTable<KeyType, ItemType>::find(const KeyType& key) const
{
	int hashIndex = getHashIndex(key);
	if (table[hashIndex] == nullptr)
		throw NotFoundException();
	else
	{
		LinkedHashedEntry<KeyType, ItemType>* entry = table[hashIndex];
		return entry->getValue();
	}
}  // end get

template<class KeyType, class ItemType>
vector<ItemType> HashTable<KeyType, ItemType>::getAll() const
{
	vector<ItemType> entries;

	for (size_t i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i] == nullptr)
			continue;
		else
		{
			LinkedHashedEntry<KeyType, ItemType>* entry = table[i];
			entries.push_back( entry->getValue() );
		}
	}

	return entries;
}  // end getAll

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::add(const KeyType& key, const ItemType& value)
{
	// Create entry to add to hash table
	LinkedHashedEntry<KeyType, ItemType>* entryToAddPtr = new LinkedHashedEntry<KeyType, ItemType>(key, value);
	
	// Compute the hashed index into the array
	int hashIndex = getHashIndex(key);
	
	// Add the entry to the chain at hashIndex
	if (table[hashIndex] == nullptr)
		table[hashIndex] = entryToAddPtr;
	else
	{
		LinkedHashedEntry<KeyType, ItemType>* entry = table[hashIndex];
		while (entry->getNext() != nullptr)
			entry = entry->getNext();
		entry->setNext( entryToAddPtr );
	}

	itemCount++;
}  // end put

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::remove(const KeyType& key)
{
	// Compute the hashed index into the array
	int hashIndex = getHashIndex(key);
	if (table[hashIndex] != nullptr)
	{
		LinkedHashedEntry<KeyType, ItemType>* prevEntry = nullptr;
		LinkedHashedEntry<KeyType, ItemType>* entryToRemove = table[hashIndex];
		while (entryToRemove->getNext() != nullptr && entryToRemove->getKey() != key)
		{
			prevEntry = entryToRemove;
			entryToRemove = entryToRemove->getNext();
		}
		if (entryToRemove->getKey() == key)  // Found item
		{
			if (prevEntry == nullptr)  // First node in the chain
			{
				LinkedHashedEntry<KeyType, ItemType>* nextEntry = entryToRemove->getNext();
				delete entryToRemove;
				entryToRemove = nullptr;
				table[hashIndex] = nextEntry;
			}  // end if
			else  // Attach previous node to entryToRemove's successor
			{
				LinkedHashedEntry<KeyType, ItemType>* next = entryToRemove->getNext();
				delete entryToRemove;
				entryToRemove = nullptr;
				prevEntry->setNext(next);
			}  // end else
			itemCount--;
		}  // end if
	}  // end if
	else
		throw NotFoundException();
}  // end remove

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::clear()
{
	itemCount = 0;
}  // end clear

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::~HashTable()
{
	for (size_t i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i] != nullptr)
		{
			LinkedHashedEntry<KeyType, ItemType>* prevEntry = nullptr;
			LinkedHashedEntry<KeyType, ItemType>* entry = table[i];
			while (entry != nullptr)
			{
				prevEntry = entry;
				entry = entry->getNext();
				delete prevEntry;
				prevEntry = nullptr;
			}
		}  // end if
	}  // end if
	delete[] table;
	table = nullptr;
}  // end destructor

#endif