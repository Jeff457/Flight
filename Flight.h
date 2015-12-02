#include <string>
using namespace std;

#include "HashTable.h"
#include "Passenger.h"

#ifndef _FLIGHT
#define _FLIGHT


class Flight
{
	friend ostream& operator<<(ostream& out, const Flight& flights);

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

	/** Add flight number, departure & arrival times, origin & destination cities. */
	void addFlightNumber(const size_t& newFlightNumber) { flightNumber = newFlightNumber; }
	void addDepartTime  (const size_t& departureTime)	{ departTime = departureTime;	  }
	void addArriveTime  (const size_t& arrivalTime)		{ arriveTime = arrivalTime;		  }
	void addOrigin      (const string& from)		    { fromCity = from;				  }
	void addDestination (const string& to)				{ toCity = to;					  }

	/** Total distance between departure and arrival city. */
	void addMileage(const size_t& mileage) { this->mileage = mileage; };
	
	/** Adds passenger to manifest using reservation number. 
	@pre  Only have room for 27 economy passengers with a maximum total capacity of 40 passengers. */
	void addPassenger(const Passenger& passenger);

	/** Retrieves flight data. */
	size_t getFlightNumber() const { return flightNumber; }
	size_t getDepartTime() const   { return departTime;	  }
	size_t getArriveTime() const   { return arriveTime;   }
	size_t getMileage() const	   { return mileage;	  }
	string getOrigin() const	   { return fromCity;	  }
	string getDestination() const  { return toCity;		  }

	/** Returns a list of all passengers aboard flight */
	vector<Passenger> getManifest() const;

	/** Returns passenger information if on flight.
	@throw NotFoundException if the passenger is not on the flight. */
	Passenger findPassenger(const Passenger& passenger) const;

	/** Removes passenger from manifest.  */
	void removePassenger(const Passenger& passenger);
};


//==============================
//		Implementation
//==============================

//==============================
//		Friend Methods
//==============================

ostream& operator<<(ostream& out, const Flight& flights)
{
	out << "Flight Number: " << flights.getFlightNumber();
	out << "\nDeparture Time: " << flights.getDepartTime();
	out << "\nArrival Time: " << flights.getArriveTime();
	out << "\nTotal Mileage: " << flights.getMileage();
	out << "\nDeparting From: " << flights.getOrigin();
	out << "\nDestination: " << flights.getDestination();
	out << endl;

	return out;
}  // end overloaded << operator


//==============================
//		Public Methods
//==============================

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
	manifest.remove( passenger.getReservationNumber() );
}  // end removePassenger

Passenger Flight::findPassenger(const Passenger& passenger) const
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