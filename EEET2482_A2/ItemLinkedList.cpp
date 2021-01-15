#include "ItemLinkedList.h"

ItemLinkedList::ItemLinkedList() {
	this->head = NULL;
}

ItemLinkedList::ItemLinkedList(Item* item) {
	this->head = item;
}

ItemLinkedList::~ItemLinkedList() {

}

void ItemLinkedList::push(Item* item) {
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

void ItemLinkedList::display() {
	Item* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl; 
	else {
		while (currentPtr != NULL) {
			cout << currentPtr->getId() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
}