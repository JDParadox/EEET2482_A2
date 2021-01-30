#pragma once

#pragma once

#include <iostream>

#include "LinkedList.h"
#include "Account.h"

class AccountNode : public Node {
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
{
	AccountNode* head;
	size_t longestName;
	size_t longestAddress;
	size_t longestPhone;

public:
	AccountLinkedList();
	AccountLinkedList(Account* account);
	~AccountLinkedList();

	friend ostream& operator<<(ostream& os, AccountLinkedList& list);

	void add(Account* account);
	void remove(Account* account); // Deletes the account from memory too;
	void displayAll();
	void displayAllFormatted();
	void displayAllByTypeFormatted(string type);
	Account* findById(string id);
	Account* findByName(string name);
};