#pragma once

#include <string>

#include "Item.h"

using namespace std;

class Account 
{
public:

	// Constructors and destructors
	Account();
	Account(string id, string name, string address, string phone);
	Account(string id, string name, string address, string phone, int numRented, int numReturned);
	~Account();

	// Getters
	string getId();;
	string getName();
	string getAddress();
	string getPhone();
	int getNumRented();
	int getNumReturned();

	// Setters
	void setId(string id);
	void setName(string name);
	void setAddress(string address);
	void setPhone(string phone);
	void setNumRented(int numRented);
	void setNumReturned(int numReturned);

	// Methods
	virtual bool renting(Item* item) = 0;
	virtual bool returning(Item* item) = 0;

protected:
	string id;
	string name;
	string address;
	string phone;
	int numRented; // This is number of currently rented items
	int numReturned; // This is number of items returned in total over lifetime
};