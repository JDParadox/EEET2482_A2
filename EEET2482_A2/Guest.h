#pragma once

#include <string>

#include "Account.h"
#include "Item.h"

#include "ItemLinkedList.h"

#define MAXRENT 2

class Guest : public Account 
{
public:
	// Constructors and destructors
	Guest();
	Guest(string id, string name, string address, string phone);
	Guest(string id, string name, string address, string phone, int numRented, int numReturned);

	// Getters

	// Setters

	// Methods
	/*bool renting(Item* item);
	bool returning(Item* item);*/

private:
};