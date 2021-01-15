#include "AccountLinkedList.h"

AccountLinkedList::AccountLinkedList() {
	this->head = NULL;
}

AccountLinkedList::AccountLinkedList(Account* account) {
	this->head = account;
}

AccountLinkedList::~AccountLinkedList() {
	Account* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			Account* oldPtr = currentPtr;
			currentPtr = currentPtr->getNext();

			delete oldPtr;
			oldPtr = NULL;
		}
	}
}

ostream& operator<<(ostream& os, AccountLinkedList& list)
{
	Account* currentPtr = list.head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			os << currentPtr->getId() << " | " << currentPtr->getName() << " | " << currentPtr->getAddress() << " | " << currentPtr->getPhone() << " | " << currentPtr->getNumReturned() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
	return os;
}

void AccountLinkedList::add(Account* account) {
	Account* currentPtr = head;
	if (currentPtr == NULL) {
		head = account;
	}
	else {
		while (currentPtr->getNext() != NULL) {
			currentPtr = currentPtr->getNext();
		}
		currentPtr->setNext(account);
		currentPtr->getNext()->setNext(NULL);
	}
}

void AccountLinkedList::displayAll() {
	Account* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			cout << currentPtr->getId() << " | " << currentPtr->getName() << " | " << currentPtr->getAddress() << " | " << currentPtr->getPhone() << " | " << currentPtr->getNumReturned() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
}

Account* AccountLinkedList::findById(string id) {
	Account* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			if (currentPtr->getId() == id) return currentPtr;
			else currentPtr = currentPtr->getNext();
		}
		return NULL;
	}
}