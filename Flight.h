#include <string>
using namespace std;

#include "HashTable.h"
#include "Passenger.h"

#ifndef _FLIGHT
#define _FLIGHT


class Flight
{
private:
	int pilotClub,
		firstClass,
		businessClass,
		economy;

	size_t flightNumber;
	size_t departTime;
	size_t arriveTime;
	size_t mileage;

	string fromCity;
	string toCity;

	HashTable<size_t, Passenger> manifest;

public:
	Flight() : pilotClub(0), firstClass(0), businessClass(0), economy(0), flightNumber(0), departTime(0), arriveTime(0), mileage(0), fromCity(""), toCity("") {}
	Flight(const size_t& flightNumber, const size_t& departTime, const size_t& arriveTime, const size_t& mileage, const string& fromCity, const string& toCity);

	/** Adds passenger to manifest using reservation number. 
	@pre  Only have room for 27 economy passengers with a maximum total capacity of 40 passengers. */
	void addPassenger(const Passenger& passenger);
	
	/** Removes passenger from manifest.  */
	void removePassenger(const Passenger& passenger);
	
	/** Returns passenger information if on flight.
	@throw NotFoundException if the passenger is not on the flight. */
	Passenger findPassenger(const Passenger& passenger);

	/** Total distance between departure and arrival city. */
	void addMileage(const size_t& mileage) { this->mileage = mileage; };

	/** Returns a list of all passengers aboard flight */
	vector<Passenger> getManifest() const;

};

Flight::Flight(const size_t& flightNumber, const size_t& departTime, const size_t& arriveTime, const size_t& mileage, const string& fromCity, const string& toCity)
	: pilotClub(0), firstClass(0), businessClass(0), economy(0)
{
	this->flightNumber = flightNumber;
	this->departTime = departTime;
	this->arriveTime = arriveTime;
	this->mileage = mileage;
	this->fromCity = fromCity;
	this->toCity = toCity;
}  // end constructor

void Flight::addPassenger(const Passenger& passenger)
{
	string membership = passenger.getMembership();

	if (membership == "Pilot Club")
		pilotClub++;
	else if (membership == "First Class")
		firstClass++;
	else if (membership == "Business Class")
		businessClass++;
	else
		economy++;
	
	if (manifest.getTotalEntries() <= 40)
	{
		// Only have room for 27 in economy
		if (membership == "Economy" && economy > 27)
			throw exception();
		else
			manifest.add( passenger.getReservationNumber(), passenger );
	}
}  // end addPassenger

void Flight::removePassenger(const Passenger& passenger)
{
	try
	{
		manifest.remove( passenger.getReservationNumber() );
	}
	catch (NotFoundException&)
	{
		cout << "Unable to find passenger aboard flight " << flightNumber << endl;
	}
}  // end removePassenger

Passenger Flight::findPassenger(const Passenger& passenger)
{
	Passenger foundPassenger;

	try
	{
		foundPassenger = manifest.find( passenger.getReservationNumber() );
	}
	catch (const NotFoundException&)
	{
		cout << "Unable to find passenger aboard flight " << flightNumber << endl;
	}

	return foundPassenger;
}  // end findPassenger

vector<Passenger> Flight::getManifest() const
{
	return manifest.getAll();
}  // end getManifest

#endif