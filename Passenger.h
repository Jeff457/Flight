#include <string>
using namespace std;

class Passenger
{
private:
	string firstName;
	string lastName;
	string membership;

	size_t reservation;
	size_t flightNumber;

public:
	Passenger() : firstName(""), lastName(""), membership(""), reservation(0), flightNumber(0) {}
	Passenger(string firstName, string lastName, string membership, size_t reservation, size_t flightNumber) {
		this->firstName = firstName;
		this->lastName = lastName;
		this->membership = membership;
		this->reservation = reservation;
		this->flightNumber = flightNumber;
	}

	size_t getReservationNumber() const { return reservation; }
	string getMembership() const { return membership; }
};
