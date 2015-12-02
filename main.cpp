#include <iostream>
#include <fstream>
#include "HashTable.h"
#include "Flight.h"
using namespace std;

/** Opens file and creates Flight objects from file data. 
@param fileName  The file to open.
@param allFlights  Container that holds Flight objects.
@pre  File name is valid.
@post Flight objects created and held in vector allFlights.
@return  true  if file can be opened
		 false if it cannot								*/
bool openFlightData(const string& fileName, vector<Flight>& allFlights);

int main()
{
	vector<Flight> allFlights;
	string fileName = "Flights.txt";
	bool ableToOpen;

	do
	{
		ableToOpen = openFlightData(fileName, allFlights);
		if (!ableToOpen)
		{
			cout << fileName << " cannot be opened.  Enter another file name -->  ";
			getline(cin, fileName);
		}
	} while (!ableToOpen);

	// Displaying the flight data
	for (auto all : allFlights)
		cout << all << endl;

	allFlights.clear();
}  // end main

bool openFlightData(const string& fileName, vector<Flight>& allFlights)
{
	ifstream flightData(fileName);
	string fromCity, toCity;
	int flightNumber, departTime, arriveTime;

	if (flightData.fail())
		return false;
	else  // Able to open file for processing
	{
		while (!flightData.eof())
		{
			// Create new Flight objects using data from file
			Flight* flights = new Flight();  
			
			flightData >> flightNumber;
			flightData >> departTime;
			flightData >> arriveTime;
			flightData >> fromCity;
			flightData >> toCity;

			flights->addFlightNumber(flightNumber);
			flights->addDepartTime(departTime);
			flights->addArriveTime(arriveTime);
			flights->addOrigin(fromCity);
			flights->addDestination(toCity);

			// Add new Flight objects to vector
			allFlights.push_back(*flights);
			delete flights;
			flights = nullptr;
		}  // end while
		flightData.close();
	}  // end if
	return true;
}  // end openFlightData