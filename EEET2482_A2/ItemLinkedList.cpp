#include "ItemLinkedList.h"

Node::Node() {

}

Node::Node(Item* item) {
	this->data = item;
}

Node* Node::getNext() {
	return next;
}

Item* Node::getData() {
	return data;
}

void Node::setNext(Node* next) {
	this->next = next;
}

void Node::setData(Item* item) {
	this->data = item;
}

ItemLinkedList::ItemLinkedList() {
	this->head = NULL;
}

ItemLinkedList::ItemLinkedList(Item* item) {
	Node* newNode = new Node(item);
	this->head = newNode;
}

ItemLinkedList::~ItemLinkedList() {
	Node* currentPtr = head;
	if (currentPtr != NULL) {
		while (currentPtr != NULL) {
			Node* oldPtr = currentPtr;
			currentPtr = currentPtr->getNext();

			delete oldPtr;
			oldPtr = NULL;
		}
	}
}

ostream& operator<<(ostream& os, ItemLinkedList& list)
{
	Node* currentPtr = list.head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			os << currentPtr->getData()->getId() << " | " << currentPtr->getData()->getTitle() << " | " << currentPtr->getData()->getRentType() << " | " << currentPtr->getData()->getLoanType() << " | " << currentPtr->getData()->getStock() << " | " << currentPtr->getData()->getRentFee() << " | " << currentPtr->getData()->getGenre() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
	return os;
}

void ItemLinkedList::add(Item* item) {
	Node* currentPtr = head;
	Node* newNode = new Node(item);
	if (currentPtr == NULL) {
		head = newNode;
	}
	else {
		while (currentPtr->getNext() != NULL) {
			currentPtr = currentPtr->getNext();
		}
		currentPtr->setNext(newNode);
		currentPtr->getNext()->setNext(NULL);
	}
}

void ItemLinkedList::displayAll() {
	Node* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl; 
	else {
		while (currentPtr != NULL) {
			cout << currentPtr->getData()->getId() << " | " << currentPtr->getData()->getTitle() << " | " << currentPtr->getData()->getRentType() << " | " << currentPtr->getData()->getLoanType() << " | " << currentPtr->getData()->getStock() << " | " << currentPtr->getData()->getRentFee() << " | " << currentPtr->getData()->getGenre() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
}

Item* ItemLinkedList::findById(string id) {
	int index = 0;
	Node* currentPtr = head;
	/*if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			if (currentPtr->getId() == id) return currentPtr;
			else currentPtr = currentPtr->getNext();
		}
		return NULL;
	}*/

	while (currentPtr != NULL) {
		//cout << id << " " << currentPtr->getData()->getId() << endl;
		if (currentPtr->getData()->getId().compare(id) == 0) {
			//If element found return index
			return currentPtr->getData();
		}
		currentPtr = currentPtr->getNext();
		index++;
	}
	return NULL;
}