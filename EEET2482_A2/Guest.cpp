#include "Guest.h"

Guest::Guest() : Account() {
	// Default constructor. Shouldn't be used.
	for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}
}

Guest::Guest(string id, string name, string address, string phone) : Account(id, name, address, phone) {
	// Constructor for new account
	for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}
}

Guest::Guest(string id, string name, string address, string phone, int numRented, int numReturned) : Account(id, name, address, phone, numRented, numReturned) {
	// Constructor for possibly existing account
	for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}
}

bool Guest::renting(Item* item) {
	return true;
}

bool Guest::returning(Item* item) {
	return true;
}