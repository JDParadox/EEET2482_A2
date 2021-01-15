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
}

Account::Account(string id, string name, string address, string phone) {
	// Constructor for new account
	this->id = id;
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->numRented = 0;
	this->numReturned = 0;
}

Account::Account(string id, string name, string address, string phone, int numRented, int numReturned) {
	// Constructor for possibly existing account
	this->id = id;
	this->name = name;
	this->address = address;
	this->phone = phone;
	this->numRented = numRented;
	this->numReturned = numReturned;
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

// LinkedList methods
Account* Account::getNext() {
	return this->next;
}

void Account::setNext(Account* next) {
	this->next = next;
}