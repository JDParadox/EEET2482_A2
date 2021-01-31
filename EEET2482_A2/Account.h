#pragma once

#include <string>

#include "Item.h"
#include "ItemLinkedList.h"
using namespace std;

class Account 
	// Base class for all user accounts
{
public:

	// Constructors and destructors
	Account();
	Account(string id, string name, string address, string phone, string type); // Constructor for new accounts
	Account(string id, string name, string address, string phone, int numRented, int numReturned, string type); // Constructor for "existing" accounts
	~Account();

	// Getters
	string getId();;
	string getName();
	string getAddress();
	string getPhone();
	int getNumRented();
	int getNumReturned();
	string getType();
	ItemLinkedList* getList();

	// Setters
	void setId(string id);
	void setName(string name);
	void setAddress(string address);
	void setPhone(string phone);
	void setNumRented(int numRented);
	void setNumReturned(int numReturned);
	void setType(string type);
	void setList(ItemLinkedList list);

	// Methods
	bool renting(Item* item); // Method for renting item
	bool returning(Item* item); // Method for returning item
	bool addItem(Item* item); // System method for addding an item without changing any stock value for use during intial loading
	void printItems(); // Print all items

protected:
	string id;
	string name;
	string address;
	string phone;
	int numRented; // This is number of currently rented items
	int numReturned; // This is number of items returned in total over lifetime. Also VIP "points" since 1 successful return = 10 points
	ItemLinkedList rentList;
	string type; // Account type. Easier to check like this without more c++ libraries
};