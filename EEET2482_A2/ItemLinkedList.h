#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "LinkedList.h"
#include "Item.h"

class ItemNode : public Node {
	// ItemNode subclass. Not sure if necessary

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
	//ItemLinkedList subclass. Sorted Linked List, to be more precise
{
	ItemNode* head;
	size_t longestTitle; // For formatting

public:
	ItemLinkedList();
	ItemLinkedList(Item* item);
	~ItemLinkedList();

	friend ostream& operator<<(ostream& os, ItemLinkedList& list);

	int getSize(); // get list size
	void add(Item* item); // Add item to list in sorted position
	void remove(Item* item); // Removes item from list and delete the item
	void removeNode(ItemNode* node); // Removes the node from list. Takes node param
	void removeNode(Item* item); // Removes the node from list. Takes item param
	void displayAll(); // Debug print
	void displayAllFormatted(); // Formatted print
	void displayOutOfStockFormatted(); // Formatted print for out of stock items
	Item* findById(string id); // Find by id
	Item* findByTitle(string title); // Find by title

	void writeToStream(ofstream& fileStr); // Write whole item to stream
	void writeIdToStream(ofstream& fileStr); // Write only id to stream (for Account::writeToStream)
};