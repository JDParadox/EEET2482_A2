#include "ItemLinkedList.h"

ItemLinkedList::ItemLinkedList() {
	this->head = NULL;
}

ItemLinkedList::ItemLinkedList(Item* item) {
	this->head = item;
}

ItemLinkedList::~ItemLinkedList() {
	Item* currentPtr = head;
	if (currentPtr != NULL) {
		while (currentPtr != NULL) {
			Item* oldPtr = currentPtr;
			currentPtr = currentPtr->getNext();

			delete oldPtr;
			oldPtr = NULL;
		}
	}
}

ostream& operator<<(ostream& os, ItemLinkedList& list)
{
	Item* currentPtr = list.head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			os << currentPtr->getId() << " | " << currentPtr->getTitle() << " | " << currentPtr->getRentType() << " | " << currentPtr->getLoanType() << " | " << currentPtr->getStock() << " | " << currentPtr->getRentFee() << " | " << currentPtr->getGenre() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
	return os;
}

void ItemLinkedList::add(Item* item) {
	Item* currentPtr = head;
	if (currentPtr == NULL) {
		head = item;
	}
	else {
		while (currentPtr->getNext() != NULL) {
			currentPtr = currentPtr->getNext();
		}
		currentPtr->setNext(item);
		currentPtr->getNext()->setNext(NULL);
	}
}

void ItemLinkedList::displayAll() {
	Item* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl; 
	else {
		while (currentPtr != NULL) {
			cout << currentPtr->getId() << " | " << currentPtr->getTitle() << " | " << currentPtr->getRentType() << " | " << currentPtr->getLoanType() << " | " << currentPtr->getStock() << " | " << currentPtr->getRentFee() << " | " << currentPtr->getGenre() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
}

Item* ItemLinkedList::findById(string id) {
	int index = 0;
	Item* currentPtr = head;
	/*if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			if (currentPtr->getId() == id) return currentPtr;
			else currentPtr = currentPtr->getNext();
		}
		return NULL;
	}*/

	while (currentPtr != NULL) {
		cout << id << " " << currentPtr->getId() << endl;
		if (currentPtr->getId().compare(id) == 0) {
			//If element found return index
			return currentPtr;
		}
		currentPtr = currentPtr->getNext();
		index++;
	}
	return NULL;
}