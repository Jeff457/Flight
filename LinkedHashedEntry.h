#ifndef _LINKED_HASHED_ENTRY
#define _LINKED_HASHED_ENTRY

template<class KeyType, class ItemType>
class LinkedHashedEntry
{
private:
	KeyType key;  // Search key for Entry
	ItemType value;  // The entry itself
	LinkedHashedEntry* next;  // Point to the hashed entry

public:
	LinkedHashedEntry() : next(nullptr) {}
	LinkedHashedEntry(const KeyType& key, const ItemType& value) 
	{
		this->key = key;
		this->value = value;
		next = nullptr;
	}

	KeyType		       getKey()   const	{ return key;   }
	ItemType		   getValue() const { return value; }
	LinkedHashedEntry* getNext()  const { return next;  }

	void setNext(LinkedHashedEntry* next) { this->next = next; }
};

#endif