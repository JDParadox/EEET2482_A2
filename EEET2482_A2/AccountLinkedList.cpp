#include "AccountLinkedList.h"

AccountNode::AccountNode() {
	this->data = NULL;
	this->next = NULL;
}

AccountNode::AccountNode(Account* acc) {
	this->data = acc;
	this->next = NULL;
}

AccountNode* AccountNode::getNext() {
	return next;
}

Account* AccountNode::getData() {
	return data;
}

void AccountNode::setNext(AccountNode* next) {
	this->next = next;
}

void AccountNode::setData(Account* acc) {
	this->data = acc;
}

AccountLinkedList::AccountLinkedList() {
	this->head = NULL;
	this->longestName = 0;
	this->longestAddress = 0;
	this->longestPhone = 0;
}

AccountLinkedList::AccountLinkedList(Account* account) {
	AccountNode* newNode = new AccountNode(account);
	this->head = newNode;
	if (account->getName().length() > 0) {
		this->longestName = account->getName().length();
	}
	else {
		this->longestName = 0;
	}

	if (account->getAddress().length() > 0) {
		this->longestAddress = account->getAddress().length();
	}
	else {
		this->longestAddress = 0;
	}

	if (account->getPhone().length() > 0) {
		this->longestPhone = account->getPhone().length();
	}
	else {
		this->longestPhone = 0;
	}
}

AccountLinkedList::~AccountLinkedList() {
	AccountNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			AccountNode* oldPtr = currentPtr;
			currentPtr = currentPtr->getNext();

			delete oldPtr;
			oldPtr = NULL;
		}
	}
}

ostream& operator<<(ostream& os, AccountLinkedList& list)
{
	AccountNode* currentPtr = list.head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			os << currentPtr->getData()->getId() << " | " << currentPtr->getData()->getName() << " | " << currentPtr->getData()->getAddress() << " | " << currentPtr->getData()->getPhone() << " | " << currentPtr->getData()->getNumReturned() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
	return os;
}

void AccountLinkedList::add(Account* account) {
	// Adds account to linked list

	AccountNode* newNode = new AccountNode(account); // Creates new node with account

	// Sets new longest attributes
	if (account->getName().length() > longestName) {
		this->longestName = account->getName().length(); 
	}
	if (account->getAddress().length() > longestAddress) {
		this->longestAddress = account->getAddress().length();
	}
	if (account->getPhone().length() > longestPhone) {
		this->longestPhone = account->getPhone().length();
	}

	// If list is empty, or if head node's id is smaller than newNode's, set head to newNode
	if (head == NULL || head->getData()->getId().compare(newNode->getData()->getId()) > 0) {
		newNode->setNext(head);
		head = newNode;
	}

	else {
		AccountNode* currentPtr = head;
		
		// Iterate until next node's id is larger than newNode
		while (currentPtr->getNext() != NULL && currentPtr->getNext()->getData()->getId().compare(newNode->getData()->getId()) < 0 ) {
			currentPtr = currentPtr->getNext();
		}

		// Inserting newNode inbetween current and next node
		newNode->setNext(currentPtr->getNext()); // Set newNode's next to the next node
		currentPtr->setNext(newNode); // Set the current node's next to the new node
	}
}

void AccountLinkedList::remove(Account* account) {
	AccountNode* temp = head; // temp node
	AccountNode* prev = NULL; // prev node

	// If head node is the node to remove, set the head node to the next node, then delete the old head.
	if (temp != NULL && temp->getData() == account) {
		head = temp->getNext();
		delete temp;
		return;
	}
	
	// Iterate until it finds the target
	while (temp != NULL && temp->getData() != account) {
		prev = temp;
		temp = temp->getNext();
	}

	// If can't find it stops
	if (temp == NULL) {
		return;
	}

	// If found, delete it
	prev->setNext(temp->getNext());
	delete temp;

}

void AccountLinkedList::displayAll() {
	// Display the whole list
	AccountNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
		while (currentPtr != NULL) {
			cout << currentPtr->getData()->getId() << " | " << currentPtr->getData()->getName() << " | " << currentPtr->getData()->getAddress() << " | " << currentPtr->getData()->getPhone() << " | " << currentPtr->getData()->getNumReturned() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
}

void AccountLinkedList::displayAllFormatted() {
	// Display list with columns
	AccountNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;

	else {

		//Prints top column with legends
		cout.width(4); // resizing
		cout << "ID";
		cout << " | ";
		cout.width(longestName);
		cout << " Name";
		cout << " | ";
		cout.width(longestAddress);
		cout << "Address";
		cout << " | ";
		cout.width(longestPhone);
		cout << "Phone";
		cout << " | ";
		cout.width(7);
		cout << "Rentals";
		cout << endl;

		//Prints the list
		while (currentPtr != NULL) {
			cout << currentPtr->getData()->getId() << " | ";
			cout.width(longestName);
			cout << currentPtr->getData()->getName() << " | ";
			cout.width(longestAddress);
			cout << currentPtr->getData()->getAddress() << " | ";
			cout.width(longestPhone);
			cout << currentPtr->getData()->getPhone() << " | ";
			cout.width(7);
			cout << currentPtr->getData()->getNumReturned() << endl;
			currentPtr = currentPtr->getNext();
		}
	}
}

void AccountLinkedList::displayAllByTypeFormatted(string type) {
	// Display list with columns by type

	AccountNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {

		//Prints top column with legends
		cout.width(4);
		cout << "ID";
		cout << " | ";
		cout.width(longestName);
		cout << " Name";
		cout << " | ";
		cout.width(longestAddress);
		cout << "Address";
		cout << " | ";
		cout.width(longestPhone);
		cout << "Phone";
		cout << " | ";
		cout.width(7);
		cout << "Rentals";
		cout << endl;
		bool empty = true;
		while (currentPtr != NULL) {

			//Prints the list
			if (currentPtr->getData()->getType() == type) { // Only print if it's the right type
				empty = false;
				cout.width(4);
				cout << currentPtr->getData()->getId() << " | ";
				cout.width(longestName);
				cout << currentPtr->getData()->getName() << " | ";
				cout.width(longestAddress);
				cout << currentPtr->getData()->getAddress() << " | ";
				cout.width(longestPhone);
				cout << currentPtr->getData()->getPhone() << " | ";
				cout.width(7);
				cout << currentPtr->getData()->getNumReturned() << endl;
			}
			currentPtr = currentPtr->getNext();
		}
		if (empty) cout << "No " << type << " accounts found" << endl;
	}
}

Account* AccountLinkedList::findById(string id) {
	// Find account by ID
	AccountNode* currentPtr = head;

	while (currentPtr != NULL) {
		if (currentPtr->getData()->getId().compare(id) == 0) {
			//If element found return account
			return currentPtr->getData();
		}
		currentPtr = currentPtr->getNext();
	}
	return NULL;
}

Account* AccountLinkedList::findByName(string name) {
	// Find account by name
	AccountNode* currentPtr = head;

	while (currentPtr != NULL) {
		if (currentPtr->getData()->getName().compare(name) == 0) {
			//If element found return account
			return currentPtr->getData();
		}
		currentPtr = currentPtr->getNext();
	}
	return NULL;
}

void AccountLinkedList::writeToStream(ofstream& fileStr) {
	// Writes to a fileStream
	AccountNode* currentPtr = head;
	AccountNode* temp;
	while (currentPtr != NULL) {
		if (currentPtr->getData() != NULL) {
			fileStr << currentPtr->getData()->getId() << "," << currentPtr->getData()->getName() << "," << currentPtr->getData()->getAddress() << "," << currentPtr->getData()->getPhone() << "," << currentPtr->getData()->getNumReturned() << ",";
			// Write customer data with comma delim

			// Writes account type. This is very inefficient, but accidentally made account type lowercase so, oops. Either I do this, or I try to fix everything else and cause untold number of bugs
			if (currentPtr->getData()->getType() == "guest") {
				fileStr << "Guest" << endl;
			}
			else if (currentPtr->getData()->getType() == "regular") {
				fileStr << "Regular" << endl;
			}
			else {
				fileStr << "VIP" << endl;
			}
			currentPtr->getData()->getList()->writeIdToStream(fileStr); // Writes the rentList to stream
			currentPtr = currentPtr->getNext();
		}
	}
}