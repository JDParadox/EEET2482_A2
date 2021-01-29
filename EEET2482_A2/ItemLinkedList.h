#pragma once

#include <iostream>

#include "LinkedList.h"
#include "Item.h"

class ItemNode : public Node {
	Item* data;
	ItemNode* next;

public:
	ItemNode();
	ItemNode(Item* item);

	ItemNode* getNext();
	Item* getData();

	void setNext(ItemNode* next);
	void setData(Item* item);
};

class ItemLinkedList : public LinkedList
{
	ItemNode* head;
	size_t longestTitle;

public:
	ItemLinkedList();
	ItemLinkedList(Item* item);
	~ItemLinkedList();

	friend ostream& operator<<(ostream& os, ItemLinkedList& list);

	void add(Item* item);
	//void removeTail(); 
	void displayAll();
	void displayAllFormatted();
	void displayOutOfStockFormatted();
	Item* findById(string id);
};