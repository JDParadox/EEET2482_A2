#include "Guest.h"

Guest::Guest() : Account() {
	// Default constructor. Shouldn't be used.
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

Guest::Guest(string id, string name, string address, string phone) : Account(id, name, address, phone, "guest") {
	// Constructor for new account
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

Guest::Guest(string id, string name, string address, string phone, int numRented, int numReturned) : Account(id, name, address, phone, numRented, numReturned, "guest") {
	// Constructor for possibly existing account
	/*for (int i = 0; i < MAXRENT; i++) {
		this->rentList[i] = NULL;
	}*/
}

//bool Guest::renting(Item* item) {
//	rentList.add(item);
//	item->setStock(item->getStock()-1);
//}
//
//bool Guest::returning(Item* item) {
//	rentList.removeNode(item);
//	item->setStock(item->getStock() - 1);
//}

//bool Guest::addItem(Item* item) {
//	rentList.add(item);
//	//cout << item->getId() << " added to " << id << endl;
//	return true;
//	/*for (int i = 0; i < MAXRENT; i++) {
//		if (rentList[i] == NULL) {
//			rentList[i] = item;
//			return true;
//		}
//	}*/
//}