#include <iostream>
#include <fstream>
#include <random>
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
	for (auto const& all : allFlights)
		cout << all << endl;

	// Testing addPassenger method below
	string pilot = "Pilot Club";
	string first = "First Class";
	string business = "Business Class";
	string economy = "Economy";
	int priority;

	for (int i = 0; i < 50; i++)
	{
		priority = rand() % 4;  // priority in the range 0 to 3
		if (priority == 0)
			allFlights[0].addPassenger(i, pilot);
		else if (priority == 1)
			allFlights[0].addPassenger(i, first);
		else if (priority == 2)
			allFlights[0].addPassenger(i, business);
		else if (priority == 3)
			allFlights[0].addPassenger(i, economy);
		else
			allFlights[0].addPassenger(i, pilot);
	}

	// Should display all 50 passengers (40 aboard + 10 waiting)
	vector<size_t> passengers = allFlights[0].getManifest();
	for (auto const& all : passengers)
		cout << all << endl;
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