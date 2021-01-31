#pragma once

#include <iostream>
#include <fstream>
#include <string>

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

	int getSize();
	void add(Item* item);
	void remove(Item* item);
	void removeNode(ItemNode* node);
	void removeNode(Item* item);
	void displayAll();
	void displayAllFormatted();
	void displayOutOfStockFormatted();
	Item* findById(string id);
	Item* findByTitle(string title);

	void writeToStream(ofstream& fileStr);
	void writeIdToStream(ofstream& fileStr);
};