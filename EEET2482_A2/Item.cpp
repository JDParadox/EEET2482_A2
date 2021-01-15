#include "Item.h"

Item::Item() {
	// Default constructor. Shouldn't be used.
	this->id = "N/A";
	this->title = "N/A";
	this->rentType = "N/A";
	this->loanType = "N/A";
	this->stock = 0;
	this->rentFee = 0;
	this->rentStatus = "N/A";
	this->genre = "N/A";
}

Item::Item(string id, string title, string rentType, string loanType, int stock, double rentFee) {
	// Constructor for video games without genre
	this->id = id;
	this->title = title;
	this->rentType = rentType;
	this->loanType = loanType;
	this->stock = stock;
	this->rentFee = rentFee;
	if (stock <= 0) {
		this->rentStatus = "borrowed";
	}
	else {
		this->rentStatus = "available";
	}
	this->genre = "N/A";
}

Item::Item(string id, string title, string rentType, string loanType, int stock, double rentFee, string genre) {
	// Constructor for records and DVDs with genre 
	this->id = id;
	this->title = title;
	this->rentType = rentType;
	this->loanType = loanType;
	this->stock = stock;
	this->rentFee = rentFee;
	if (stock <= 0) {
		this->rentStatus = "borrowed";
	}
	else {
		this->rentStatus = "available";
	}
	this->genre = genre;
}

Item::Item(const Item& item) {
	this->id = item.id;
	this->title = item.title;
	this->rentType = item.rentType;
	this->loanType = item.loanType;
	this->stock = item.stock;
	this->rentFee = item.rentFee;
	this->rentStatus = item.rentStatus;
	this->genre = item.genre;
}

Item::~Item() {
}

ostream& operator<<(ostream& os, Item& item)
{
	os << item.getId() << " | " << item.getTitle() << " | " << item.getRentType() << " | " << item.getLoanType() << " | " << item.getStock() << " | " << item.getRentFee() << " | " << item.getGenre();
	return os;
}

string Item::getId() {
	return this->id;
}

string Item::getTitle() {
	return this->title;
}

string Item::getRentType() {
	return this->rentType;
}

string Item::getLoanType() {
	return this->loanType;
}

int Item::getStock() {
	return this->stock;
}

double Item::getRentFee() {
	return this->rentFee;
}

string Item::getRentStatus() {
	return this->rentStatus;
}

string Item::getGenre() {
	return this->genre;
}

void Item::setId(string id) {
	this->id = id;
}

void Item::setTitle(string title) {
	this->title = title;
}

void Item::setRentType(string rentType) {
	this->rentType = rentType;
}

void Item::setLoanType(string loanType) {
	this->loanType = loanType;
}

void Item::setStock(int stock) {
	this->stock = stock;
}

void Item::setRentFee(double rentFee) {
	this->rentFee = rentFee;
}

void Item::setRentStatus(string rentStatus) {
	this->rentStatus = rentStatus;
}

void Item::setGenre(string genre) {
	this->genre = genre;
}

void Item::setAll(string id, string title, string rentType, string loanType, int stock, double rentFee, string genre) {
	this->id = id;
	this->title = title;
	this->rentType = rentType;
	this->loanType = loanType;
	this->stock = stock;
	this->rentFee = rentFee;
	if (stock <= 0) {
		this->rentStatus = "borrowed";
	}
	else {
		this->rentStatus = "available";
	}
	this->genre = genre;
}

bool Item::renting() {
	if ((this->stock <= 0) || (this->rentType == "borrowed")) {
		return false;
	}
	else {
		this->stock--;
		if (this->stock <= 0) {
			this->rentStatus = "borrowed";
		}
		return true;
	}
}

bool Item::returning() {
	this->stock++;
	return true;
}

// LinkedList methods
Item* Item::getNext() {
	return this->next;
}

void Item::setNext(Item* next) {
	this->next = next;
}