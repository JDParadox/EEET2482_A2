#pragma once

#include <string>

#include "Account.h"

#define MAXRENT 50 // This is temporary. Dynamic array later

class Regular : public Account
{
public:
	Regular();
	Regular(string id, string name, string address, string phone);
	Regular(string id, string name, string address, string phone, int numRented, int numReturned);

	// Getters

	// Setters

	// Methods
	bool renting(Item* item);
	bool returning(Item* item);

private:
	Item* rentList[MAXRENT];
};