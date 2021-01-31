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

int ItemLinkedList::getSize() {
	// Get list size. Iterates and counts 
	ItemNode* temp;

	int size = 0;

	if (head == NULL) {
		return 0;
	}
	
	ItemNode* currentPtr = head;
	while (currentPtr != NULL) {
		if (currentPtr->getData() != NULL) {
			size++;
			currentPtr = currentPtr->getNext();
		}
		else { // In case node does not have data
			temp = currentPtr;
			currentPtr = currentPtr->getNext();
			removeNode(temp);
		}
	}

	return size;

}

void ItemLinkedList::add(Item* item) {
	// Adds item to list in sorted position

	ItemNode* newNode = new ItemNode(item);
	if (item->getTitle().length() > this->longestTitle) {
		this->longestTitle = item->getTitle().length(); // Checks if title is longer than recorded
	}

	// If list is empty or head is smaller
	if (head == NULL || head->getData()->getId().compare(newNode->getData()->getId()) >= 0) {
		newNode->setNext(head);
		head = newNode;
		return;
	}

	else {
		// Iterate until found smaller data id and then insert
		ItemNode* currentPtr = head;
		while (currentPtr->getNext() != NULL && currentPtr->getNext()->getData()->getId().compare(newNode->getData()->getId()) < 0) {
			currentPtr = currentPtr->getNext();
		}
		newNode->setNext(currentPtr->getNext());
		currentPtr->setNext(newNode);
	}
}

void ItemLinkedList::remove(Item* item) {
	//Remove from list and delete item
	ItemNode* temp;

	// If head is item, remove
	if (head != NULL && head->getData() == item) {
		temp = head;
		head = head->getNext();
		delete temp->getData(); // Deleting the item itself
		//temp->setData(NULL);
		delete temp;
		temp = NULL;
		return;
	}

	// Iterate until found and delete
	ItemNode* currentPtr = head;
	while (currentPtr != NULL) {
		//cout << id << " " << currentPtr->getData()->getId() << endl;
		if (currentPtr->getNext()->getData() == item) {
			// Find node before target
			temp = currentPtr->getNext();
			currentPtr->setNext(temp->getNext());
			delete temp->getData();
			delete temp;
			temp = NULL;
			return;
		}
		currentPtr = currentPtr->getNext();;
	}
}

void ItemLinkedList::removeNode(ItemNode* node) {
	// Remove from list. Does not delete item
	ItemNode* temp;

	// If head is item, remove
	if (head != NULL && head == node) {
		temp = head;
		head = head->getNext();
		delete temp;
		temp = NULL;
		return;
	}

	// Iterate until found and remove
	ItemNode* currentPtr = head;
	while (currentPtr != NULL) {
		if (currentPtr->getNext() == node) {
			// Find node before target
			temp = currentPtr->getNext();
			currentPtr->setNext(temp->getNext());
			delete temp;
			temp = NULL;
			return;
		}
		currentPtr = currentPtr->getNext();;
	}
}

void ItemLinkedList::removeNode(Item* item) {
	// Remove from list. Does not delete item
	ItemNode* temp;

	// If head is item, remove
	if (head != NULL && head->getData() == item) {
		temp = head;
		head = head->getNext();
		delete temp;
		temp = NULL;
		return;
	}

	// Iterate until found and remove
	ItemNode* currentPtr = head;
	while (currentPtr != NULL) {
		//cout << id << " " << currentPtr->getData()->getId() << endl;
		if (currentPtr->getNext()->getData() == item) {
			// Find node before target
			temp = currentPtr->getNext();
			currentPtr->setNext(temp->getNext());
			delete temp;
			temp = NULL;
			return;
		}
		currentPtr = currentPtr->getNext();;
	}
}

void ItemLinkedList::displayAll() {
	// Debug display
	ItemNode* currentPtr = head;
	ItemNode* temp;
	if (currentPtr == NULL) cout << "List is empty" << endl; 
	else {
		// Iterates and print all
		while (currentPtr != NULL) {
			if (currentPtr->getData() != NULL) { // If data is not NULL
				cout << currentPtr->getData()->getId() << " | " << currentPtr->getData()->getTitle() << " | " << currentPtr->getData()->getRentType() << " | " << currentPtr->getData()->getLoanType() << " | " << currentPtr->getData()->getStock() << " | " << currentPtr->getData()->getRentFee() << " | " << currentPtr->getData()->getGenre() << endl;
				currentPtr = currentPtr->getNext();
			}
			else { // If data is null, remove it
				temp = currentPtr;
				currentPtr = currentPtr->getNext();
				removeNode(temp);
			}
		}
	}
}

void ItemLinkedList::displayAllFormatted() {
	// Similar to display all and display formatted from AccountLinkedList
	ItemNode* currentPtr = head;
	ItemNode* temp;
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
			if (currentPtr->getData() != NULL) {
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
			else {
				temp = currentPtr;
				currentPtr = currentPtr->getNext();
				removeNode(temp);
			}
		}
	}
}
void ItemLinkedList::displayOutOfStockFormatted() {
	// Similar to display all and display formatted from AccountLinkedList
	ItemNode* currentPtr = head;
	ItemNode* temp;

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
			if (currentPtr->getData() != NULL) {
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
			else {
				temp = currentPtr;
				currentPtr = currentPtr->getNext();
				removeNode(temp);
			}
		}
		if (noItems) cout << "There are currently no items out of stock" << endl;
	}
}

Item* ItemLinkedList::findById(string id) {
	// Similar to find by id in AccountlinkedList
	int index = 0;
	ItemNode* currentPtr = head;

	while (currentPtr != NULL) {
		if (currentPtr->getData()->getId().compare(id) == 0) {
			//If element found return item
			return currentPtr->getData();
		}
		currentPtr = currentPtr->getNext();
	}
	return NULL;
}

Item* ItemLinkedList::findByTitle(string title) {
	// Similar to find by name in AccountlinkedList
	ItemNode* currentPtr = head;

	while (currentPtr != NULL) {
		//cout << id << " " << currentPtr->getData()->getId() << endl;
		if (currentPtr->getData()->getTitle().compare(title) == 0) {
			//If element found return item
			return currentPtr->getData();
		}
		currentPtr = currentPtr->getNext();
	}
	return NULL;
}

void ItemLinkedList::writeToStream(ofstream &fileStr) {
	// Write to fileStream
	ItemNode* currentPtr = head;
	ItemNode* temp;
	while (currentPtr != NULL) {
		if (currentPtr->getData() != NULL) {
			fileStr << currentPtr->getData()->getId() << "," << currentPtr->getData()->getTitle() << "," << currentPtr->getData()->getRentType() << "," << currentPtr->getData()->getLoanType() << "," << currentPtr->getData()->getStock() << "," << currentPtr->getData()->getRentFee();
			if (currentPtr->getData()->getRentType() != "Game") {
				fileStr << "," << currentPtr->getData()->getGenre();
			}
			fileStr << endl;
			currentPtr = currentPtr->getNext();
		}
		else {
			temp = currentPtr;
			currentPtr = currentPtr->getNext();
			removeNode(temp);
		}
	}
}

void ItemLinkedList::writeIdToStream(ofstream& fileStr) {
	// Write to fileStream
	ItemNode* currentPtr = head;
	ItemNode* temp;
	while (currentPtr != NULL) {
		if (currentPtr->getData() != NULL) {
			fileStr << currentPtr->getData()->getId() << endl;
			currentPtr = currentPtr->getNext();
		}
		else {
			temp = currentPtr;
			currentPtr = currentPtr->getNext();
			removeNode(temp);
		}
	}
}