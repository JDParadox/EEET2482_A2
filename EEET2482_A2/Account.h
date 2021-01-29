#pragma once

#include <string>

#include "Item.h"
#include "ItemLinkedList.h"
using namespace std;

class Account 
{
public:

	// Constructors and destructors
	Account();
	Account(string id, string name, string address, string phone, string type);
	Account(string id, string name, string address, string phone, int numRented, int numReturned, string type);
	~Account();

	// Getters
	string getId();;
	string getName();
	string getAddress();
	string getPhone();
	int getNumRented();
	int getNumReturned();
	string getType();
	ItemLinkedList getList();

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
	virtual bool renting(Item* item) = 0;
	virtual bool returning(Item* item) = 0;
	bool addItem(Item* item); // System method for addding an item without changing any stock value for use during intial loading
	void printItems();

protected:
	string id;
	string name;
	string address;
	string phone;
	int numRented; // This is number of currently rented items
	int numReturned; // This is number of items returned in total over lifetime
	ItemLinkedList rentList;
	string type;
};