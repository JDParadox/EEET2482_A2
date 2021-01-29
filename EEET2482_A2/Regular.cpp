#include "Regular.h"

Regular::Regular() : Account() {
	// Default constructor. Shouldn't be used.
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

Regular::Regular(string id, string name, string address, string phone) : Account(id, name, address, phone, "regular") {
	// Constructor for new account
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

Regular::Regular(string id, string name, string address, string phone, int numRented, int numReturned) : Account(id, name, address, phone, numRented, numReturned, "regular") {
	// Constructor for possibly existing account
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

Regular::Regular(Account* guest) : Account(guest->getId(), guest->getName(), guest->getAddress(), guest->getPhone(), guest->getNumRented(), guest->getNumReturned(), "regular") {
	this->rentList = guest->getList();
}

bool Regular::renting(Item* item) {
	return true;
}

bool Regular::returning(Item* item) {
	return true;
}