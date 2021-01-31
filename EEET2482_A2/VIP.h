#pragma once

#include <string>

#include "Account.h"

class VIP : public Account
{
public:
	VIP();
	VIP(string id, string name, string address, string phone);
	VIP(string id, string name, string address, string phone, int numRented, int numReturned);
	VIP(Account* account); // Promote constructor

	// Getters

	// Setters

	// Methods
	/*bool renting(Item* item);
	bool returning(Item* item);*/
};