#include "LinkedList.h"

Node::Node()
{
    this->data = 0;
    this->next = NULL;
}

Node::Node(int i)
{
    this->data = i;
    this->next = NULL;
}

Node* Node::getNext()
{
    return next;
}

int Node::getData()
{
    return this->data;
}

void Node::setNext(Node* next)
{
    this->next = next;
}

void Node::setData(int i)
{
    this->data = data;
}

LinkedList::LinkedList()
{
    this->head = NULL;
}

LinkedList::LinkedList(int i)
{
    Node *node = new Node(i);
    head = node;
}
