#pragma once

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "LinkedList.h"
#include "Account.h"

class AccountNode : public Node {
	// Node child class to contain Accounts data. Implements Node base class. Might not actually be necessary
	Account* data;
	AccountNode* next;

public:
	AccountNode();
	AccountNode(Account* acc);

	AccountNode* getNext();
	Account* getData();

	void setNext(AccountNode* next);
	void setData(Account* acc);
};

class AccountLinkedList : public LinkedList
	// Sorted Linked list for accounts. Implements LinkedList base class
{
	AccountNode* head;
	size_t longestName; // Used for resizing the columns for display methods
	size_t longestAddress;
	size_t longestPhone;

public:
	AccountLinkedList();
	AccountLinkedList(Account* account);
	~AccountLinkedList();

	friend ostream& operator<<(ostream& os, AccountLinkedList& list);

	void add(Account* account); // add to the LinkedList (sorted)
	void remove(Account* account); // Deletes the account from memory too. Only used for promotion;
	void displayAll(); // Prints list. Mostly used for debug
	void displayAllFormatted(); // Prints with with columns.
	void displayAllByTypeFormatted(string type); // Prints list by type with columns.
	Account* findById(string id); // Finds and return account ptr using ID
	Account* findByName(string name); // Finds and return account ptr using name
	
	void writeToStream(ofstream& fileStr); // Writes the list to a fileStream
};