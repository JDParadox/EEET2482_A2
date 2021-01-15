#pragma once

#pragma once

#include <iostream>

#include "Account.h"

class AccountLinkedList
{
	Account* head;

public:
	AccountLinkedList();
	AccountLinkedList(Account* account);
	~AccountLinkedList();

	friend ostream& operator<<(ostream& os, AccountLinkedList& list);

	void add(Account* account);
	//void removeTail(); 
	void displayAll();
	Account* findById(string id);
};