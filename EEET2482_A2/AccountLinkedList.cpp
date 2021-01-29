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
	AccountNode* currentPtr = head;
	AccountNode* newNode = new AccountNode(account);
	if (account->getName().length() > longestName) {
		this->longestName = account->getName().length();
	}
	if (account->getAddress().length() > longestAddress) {
		this->longestAddress = account->getAddress().length();
	}
	if (account->getPhone().length() > longestPhone) {
		this->longestPhone = account->getPhone().length();
	}

	if (currentPtr == NULL || currentPtr->getData()->getId().compare(newNode->getData()->getId()) > 0) {
		newNode->setNext(head);
		head = newNode;
	}

	else {
		while (currentPtr->getNext() != NULL && currentPtr->getData()->getId().compare(newNode->getData()->getId()) < 0 ) {
			currentPtr = currentPtr->getNext();
		}
		newNode->setNext(currentPtr->getNext());
		currentPtr->setNext(newNode);
	}
}

void AccountLinkedList::remove(Account* account) {
	AccountNode* temp = head;
	AccountNode* prev = NULL;

	if (temp != NULL && temp->getData() == account) {
		head = temp->getNext();
		delete temp;
		return;
	}
	
	while (temp != NULL && temp->getData() != account) {
		prev = temp;
		temp = temp->getNext();
	}

	if (temp == NULL) {
		return;
	}

	prev->setNext(temp->getNext());
	delete temp;

}

void AccountLinkedList::displayAll() {
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
	AccountNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
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

void AccountLinkedList::displayAllGuestFormatted() {
	AccountNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
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
			if (currentPtr->getData()->getType() == "guest") {
				empty = false;
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
		if (empty) cout << "No guest accounts found" << endl;
	}
}

void AccountLinkedList::displayAllVIPFormatted() {
	AccountNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
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
			if (currentPtr->getData()->getType() == "VIP") {
				empty = false;
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
		if (empty) cout << "No VIP accounts found" << endl;
	}
}

void AccountLinkedList::displayAllRegFormatted() {
	AccountNode* currentPtr = head;
	if (currentPtr == NULL) cout << "List is empty" << endl;
	else {
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
			if (currentPtr->getData()->getType() == "regular") {
				empty = false;
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
		if (empty) cout << "No regular accounts found" << endl;
	}
}

Account* AccountLinkedList::findById(string id) {
	int index = 0;
	AccountNode* currentPtr = head;
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