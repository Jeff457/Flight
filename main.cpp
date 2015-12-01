#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "HashTable.h"
#include "Flight.h"
using namespace std;

int main()
{
	Passenger aPassenger("Jeff", "Stanton", "Pilot Club", 1234, 4576);
	Flight firstFlight(4576, 900, 1300, 150000, "TO", "LA");
	firstFlight.addPassenger(aPassenger);
	firstFlight.removePassenger(aPassenger);
}