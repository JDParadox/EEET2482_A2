#pragma once

#include <string>

#include "Account.h"
#include "Item.h"

#include "ItemLinkedList.h"

#define MAXRENT 2

class Guest : public Account 
	// Guest subclass. Not sure actually need it anymore
{
public:
	// Constructors and destructors
	Guest();
	Guest(string id, string name, string address, string phone);
	Guest(string id, string name, string address, string phone, int numRented, int numReturned);

	// Getters

	// Setters

	// Methods

private:
};