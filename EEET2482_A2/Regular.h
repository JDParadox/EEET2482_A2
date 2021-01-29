#pragma once

#include <string>

#include "Account.h"
#include "Guest.h"

class Regular : public Account
{
public:
	Regular();
	Regular(string id, string name, string address, string phone);
	Regular(string id, string name, string address, string phone, int numRented, int numReturned);
	Regular(Account* acc); // Promotion constructor

	// Getters

	// Setters

	// Methods
	bool renting(Item* item);
	bool returning(Item* item);
};