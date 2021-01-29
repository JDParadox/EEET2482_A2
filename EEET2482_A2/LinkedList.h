#pragma once

#include <iostream>

using namespace std;

class Node {
	int data;
	Node* next;

public:
	Node();
	Node(int i);

	Node* getNext();
	int getData();

	void setNext(Node* next);
	void setData(int i);
};

class LinkedList
{
	Node* head;

public:
	LinkedList();
	LinkedList(int i);

	virtual void displayAll() = 0;
};