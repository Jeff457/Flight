#include <iostream>
#include "HashTable.h"
#include "Flight.h"
using namespace std;

int main()
{
	HashTable<int, int> firstHash;
	firstHash.add(0, 34242);
	firstHash.add(1, 1231231);
	firstHash.add(44, 121);

	HashTable<int, int> secondHash(firstHash);

	vector<int> getEm;
	getEm = secondHash.getAll();
	for (auto all : getEm)
		cout << all << endl;

}