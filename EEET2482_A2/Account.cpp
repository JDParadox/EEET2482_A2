#pragma once

#include <string>

#include "Account.h"

Account::Account() {
	// Default constructor. Shouldn't be used.
	this->id = "N/A";
	this->name = "N/A";
	this->address = "N/A";
	this->phone = "N/A";
	this->numRented = 0;
	this->numReturned = 0;
	this->type = "N/A";
}

Account::Account(string id, string name, string address, string phone, string type) {
	// Constructor for new account
	this->id = id;
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->numRented = 0;
	this->numReturned = 0;
	this->type = type;
}

Account::Account(string id, string name, string address, string phone, int numRented, int numReturned, string type) {
	// Constructor for possibly existing account
	this->id = id;
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->numRented = numRented;
	this->numReturned = numReturned;
	this->type = type;
}

Account::~Account() {
}

string Account::getId() {
	return this->id;
}

string Account::getName() {
	return this->name;
}

string Account::getAddress() {
	return this->address;
}

string Account::getPhone() {
	return this->phone;
}

int Account::getNumRented() {
	return this->numRented;
}

int Account::getNumReturned() {
	return this->numReturned;
}

string Account::getType() {
	return this->type;
}

ItemLinkedList* Account::getList() {
	return &this->rentList;
}

void Account::setId(string id) {
	this->id = id;
}

void Account::setName(string name) {
	this->name = name;
}

void Account::setAddress(string address) {
	this->address = address;
}

void Account::setPhone(string phone) {
	this->phone = phone;
}

void Account::setNumRented(int numRented) {
	this->numRented = numRented;
}

void Account::setNumReturned(int numReturned) {
	this->numReturned = numReturned;
}

void Account::setType(string type) {
	this->type = type;
}

void Account::setList(ItemLinkedList list) {
	this->rentList = list;
}

bool Account::addItem(Item* item) {
	rentList.add(item);
	return true;
}

void Account::printItems() {
	rentList.displayAll();
}

bool Account::renting(Item* item) {
	// Adding item to the rentlist. Error handling is in main cpp
	rentList.add(item);
	item->setStock(item->getStock() - 1); // Lowers item stock
	this->numRented++; // Counts number of current items rented. Legacy code since getSize() was implemented for the LinkedList
	return true;
}

bool Account::returning(Item* item) {
	// Removing item from the rentlist. Error handling is in main cpp
	rentList.removeNode(item); // RemoveNode does not delete the actual item
	item->setStock(item->getStock() + 1); // Adds back stock
	this->numRented--; // Counts number of current items rented. Legacy code since getSize() was implemented for the LinkedList
	this->numReturned++; // Updates the number of successful returns
	return true;
}