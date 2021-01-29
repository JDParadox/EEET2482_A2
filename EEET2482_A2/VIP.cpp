#include "VIP.h"

VIP::VIP() : Account() {
	// Default constructor. Shouldn't be used.
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

VIP::VIP(string id, string name, string address, string phone) : Account(id, name, address, phone, "VIP") {
	// Constructor for new account
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

VIP::VIP(string id, string name, string address, string phone, int numRented, int numReturned) : Account(id, name, address, phone, numRented, numReturned, "VIP") {
	// Constructor for possibly existing account
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

VIP::VIP(Account* guest) : Account(guest->getId(), guest->getName(), guest->getAddress(), guest->getPhone(), guest->getNumRented(), guest->getNumReturned(), "regular") {
	this->rentList = guest->getList();
}

bool VIP::renting(Item* item) {
	return true;
}

bool VIP::returning(Item* item) {
	return true;
}