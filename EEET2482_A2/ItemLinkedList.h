#pragma once

#include "Item.h"

class ItemLinkedList
{
	Item* head;

public:
	ItemLinkedList();
	ItemLinkedList(Item* item);
	~ItemLinkedList();

	void push(Item* item);
	//void removeTail(); 
	void display();
};