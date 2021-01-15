#pragma once

#include <string>
#include <iostream>

using namespace std;

class Item
{
public:
	// Constructors and destructors
	Item();
	Item(string id, string title, string rentType, string loanType, int stock, double rentFee);
	Item(string id, string title, string rentType, string loanType, int stock, double rentFee, string genre);
	~Item();

	// Overloads
	friend ostream& operator<<(ostream& os, Item& item);
	
	// Getters
	string getId();
	string getTitle();
	string getRentType();
	string getLoanType();
	int getStock();
	double getRentFee();
	string getRentStatus();
	string getGenre();

	// Setters
	void setId(string id);
	void setTitle(string title);
	void setRentType(string rentType);
	void setLoanType(string loanType);
	void setStock(int stock);
	void setRentFee(double rentFee);
	void setRentStatus(string rentStatus);
	void setGenre(string genre);

	// Methods
	bool renting();
	bool returning();

	// LinkedList Node
	Item* getNext();
	void setNext(Item* next);

private:
	string id;
	string title;
	string rentType;
	string loanType;
	int stock;
	double rentFee;
	string rentStatus;
	string genre;

	// LinkedList attrs
	Item* next;
};