#pragma once

#include <iostream>

#include "Item.h"

class ItemLinkedList
{
	Item* head;

public:
	ItemLinkedList();
	ItemLinkedList(Item* item);
	~ItemLinkedList();

	friend ostream& operator<<(ostream& os, ItemLinkedList& list);

	void add(Item* item);
	//void removeTail(); 
	void displayAll();
	Item* findById(string id);
};