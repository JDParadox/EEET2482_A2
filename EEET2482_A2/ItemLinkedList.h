#pragma once

#include <iostream>

#include "Item.h"

class Node {
	Item* data;
	Node* next;

public:
	Node();
	Node(Item* item);

	Node* getNext();
	Item* getData();

	void setNext(Node* next);
	void setData(Item* item);
};

class ItemLinkedList
{
	Node* head;

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