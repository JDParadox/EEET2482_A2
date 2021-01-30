#include "ItemLinkedList.h"

ItemNode::ItemNode() {
	this->data = NULL;
	this->next = NULL;
}

ItemNode::ItemNode(Item* item) {
	this->data = item;
	this->next = NULL;
}

ItemNode* ItemNode::getNext() {
	return next;
}

Item* ItemNode::getData() {
	return data;
}

void ItemNode::setNext(ItemNode* next) {
	this->next = next;
}

void ItemNode::setData(Item* item) {
	this->data = item;
}

ItemLinkedList::ItemLinkedList() {
	this->head = NULL;
	this->longestTitle = 0;
}

ItemLinkedList::ItemLinkedList(Item* item) {
	ItemNode* newNode = new ItemNode(item);
	this->head = newNode;
	if (item->getTitle().length() > 0) {
		this->longestTitle = item->getTitle().length();
	}
	else {
		this->longestTitle = 0;
	}
	
}

ItemLinkedList::~ItemLinkedList() {
	ItemNode* currentPtr = head;
	if (currentPtr != NULL) {
		while (currentPtr != NULL) {
			ItemNode* oldPtr = currentPtr;
			currentPtr = currentPtr->getNext();

			delete oldPtr;
			oldPtr = NULL;
		}
	}
}

ostream& operator<<(ostream& os, ItemLinkedList& list)
{
	ItemNode* currentPtr = list.head;
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
	ItemNode* newNode = new ItemNode(item);
	if (item->getTitle().length() > this->longestTitle) {
		this->longestTitle = item->getTitle().length();
	}
	if (head == NULL || head->getData()->getId().compare(newNode->getData()->getId()) >= 0) {
		newNode->setNext(head);
		head = newNode;
		return;
	}
	else {
		ItemNode* currentPtr = head;
		while (currentPtr->getNext() != NULL && currentPtr->getNext()->getData()->getId().compare(newNode->getData()->getId()) < 0) {
			currentPtr = currentPtr->getNext();
		}
		newNode->setNext(currentPtr->getNext());
		currentPtr->setNext(newNode);
	}
}

void ItemLinkedList::displayAll() {
	ItemNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl; 
	else {
		while (currentPtr != NULL) {
			cout << currentPtr->getData()->getId() << " | " << currentPtr->getData()->getTitle() << " | " << currentPtr->getData()->getRentType() << " | " << currentPtr->getData()->getLoanType() << " | " << currentPtr->getData()->getStock() << " | " << currentPtr->getData()->getRentFee() << " | " << currentPtr->getData()->getGenre() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
}

void ItemLinkedList::displayAllFormatted() {
	ItemNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		cout.width(9);
		cout << "ID";
		cout << " | ";
		cout.width(longestTitle);
		cout << " Title";
		cout << " | ";
		cout.width(6);
		cout << "Type";
		cout << " | ";
		cout.width(6);
		cout << "Loan";
		cout << " | ";
		cout.width(6);
		cout << "Stock";
		cout << " | ";
		cout.width(7);
		cout << "Fee";
		cout << " | ";
		cout.width(6);
		cout << "Genre";
		cout << endl;
		while (currentPtr != NULL) {
			cout.width(9);
			cout << currentPtr->getData()->getId() << " | ";
			cout.width(longestTitle);
			cout << currentPtr->getData()->getTitle() << " | ";
			cout.width(6);
			cout << currentPtr->getData()->getRentType() << " | ";
			cout.width(6);
			cout << currentPtr->getData()->getLoanType() << " | ";
			cout.width(6);
			cout << currentPtr->getData()->getStock() << " | "; 
			cout.width(6);
			cout << currentPtr->getData()->getRentFee() << "$ | ";
			cout.width(6);
			cout << currentPtr->getData()->getGenre() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
}
void ItemLinkedList::displayOutOfStockFormatted() {
	ItemNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		cout.width(9);
		cout << "ID";
		cout << " | ";
		cout.width(longestTitle);
		cout << " Title";
		cout << " | ";
		cout.width(6);
		cout << "Type";
		cout << " | ";
		cout.width(6);
		cout << "Loan";
		cout << " | ";
		cout.width(6);
		cout << "Stock";
		cout << " | ";
		cout.width(7);
		cout << "Fee";
		cout << " | ";
		cout.width(6);
		cout << "Genre";
		cout << endl;
		bool noItems = true;
		while (currentPtr != NULL) {
			if (currentPtr->getData()->getStock() == 0) {
				noItems = false;
				cout.width(9);
				cout << currentPtr->getData()->getId() << " | ";
				cout.width(longestTitle);
				cout << currentPtr->getData()->getTitle() << " | ";
				cout.width(6);
				cout << currentPtr->getData()->getRentType() << " | ";
				cout.width(6);
				cout << currentPtr->getData()->getLoanType() << " | ";
				cout.width(6);
				cout << currentPtr->getData()->getStock() << " | ";
				cout.width(6);
				cout << currentPtr->getData()->getRentFee() << "$ | ";
				cout.width(6);
				cout << currentPtr->getData()->getGenre() << endl;
			}
			currentPtr = currentPtr->getNext();
		}
		if (noItems) cout << "There are currently no items out of stock" << endl;
	}
}

Item* ItemLinkedList::findById(string id) {
	int index = 0;
	ItemNode* currentPtr = head;
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

Item* ItemLinkedList::findByTitle(string title) {
	int index = 0;
	ItemNode* currentPtr = head;
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
		if (currentPtr->getData()->getTitle().compare(title) == 0) {
			//If element found return index
			return currentPtr->getData();
		}
		currentPtr = currentPtr->getNext();
		index++;
	}
	return NULL;
}