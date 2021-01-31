// EEET2482_A2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

#include "Account.h"
#include "Guest.h"
#include "Regular.h"
#include "VIP.h"
#include "Item.h"

#include "ItemLinkedList.h"
#include "AccountLinkedList.h"

using namespace std;

Item parseItem(string s) {
	// Eats a string, returns an item
	string tempId = "N/A";
	string tempTitle = "N/A";
	string tempRentType = "N/A";
	string tempLoanType = "N/A";
	int tempStock = 0;
	double tempFee = 0;
	string tempGenre = "N/A";

	size_t found;

	// All it does it find the next comma, parse it as a value, deletes the rest.

	// Probably very bug prone, if the file format is wrong

	found = s.find(',');
	if (found != string::npos) {
		tempId = s.substr(0, found);
		s.erase(0, found + 1);
	}

	found = s.find(',');
	if (found != string::npos) {
		tempTitle = s.substr(0, found);
		s.erase(0, found+1);
	}

	found = s.find(',');
	if (found != string::npos) {
		tempRentType = s.substr(0, found);
		s.erase(0, found + 1);
	}

	found = s.find(',');
	if (found != string::npos) {
		tempLoanType = s.substr(0, found);
		s.erase(0, found + 1);
	}

	found = s.find(',');
	if (found != string::npos) {
		tempStock = stoi(s.substr(0, found));
		s.erase(0, found + 1);
	}

	if (tempRentType != "Game") {
		found = s.find(',');
		if (found != string::npos) {
			tempFee = stod(s.substr(0, found));
			s.erase(0, found + 1);
		}
		tempGenre = s;
	}
	else {
		tempFee = stod(s);
	}

	return Item(tempId, tempTitle, tempRentType, tempLoanType, tempStock, tempFee, tempGenre); // Returns the new item
}

void printDivider() {
	// Function prints a divider to the console.
	cout << "----------------------------" << endl;
}

void printMainMenu() {
	// Function prints main menu
	
	cout << "Welcome to Genie's video store" << endl;
	cout << "Enter an option below" << endl;
	cout << "1.Add a new item, update or delete an existing item" << endl;
	cout << "2.Add new customer or update an existing customer" << endl;
	cout << "3.Promote an existing customer" << endl;
	cout << "4.Rent an item" << endl;
	cout << "5.Return an item" << endl;
	cout << "6.Display all items" << endl;
	cout << "7.Display out-of-stock items" << endl;
	cout << "8.Display all customers:" << endl;
	cout << "9.Display group of customers" << endl;
	cout << "10.Search items or customers" << endl;
	cout << "Type 'Exit' to quit the program." << endl;
}

bool validateItemId(string id) {
	// Validate item id
	bool valid = true; // if valid
	bool letters = false; // If there's letters

	if (id.size() > 9) { // Can't be longer than 9 char
		cout << "Item IDs must follow the IXXX-YEAR format (too long)" << endl;
		valid = false;
	}
	else if (id.size() < 9) { // Can't be shorter than 9 char
		cout << "Item IDs must follow the IXXX-YEAR format (too short)" << endl;
		valid = false;
	}
	else {
		if (id[0] != 'I') { // Checks if first char is I
			cout << "Item IDs must begin with I" << endl;
			valid = false;
		}

		if (id[4] != '-') { // Checks if 5 char is a dash
			cout << "Item IDs must have a -" << endl;
			valid = false;
		}

		for (int i = 1; i < 4; i++) { // Checks if first numerical portion is numerical
			if (!(id[i] >= '0' && id[i] <= '9')) {
				valid = false;
				letters = true;
			}
		}

		for (int i = 5; i < 9; i++) { // Checks if year portion is numerical
			if (!(id[i] >= '0' && id[i] <= '9')) {
				valid = false;
				letters = true;
			}
		}

		if (letters) cout << "Item IDs must only contains number beyond 'I'" << endl; // if there's letters, print this
	}

	return valid;
}

bool validateAccId(string id) {
	// validate account id
	bool valid = true;
	bool letters = false;

	if (id.size() > 4) { // Can't be longer than 4 char
		cout << "Account IDs must follow the CXXX format (too long)" << endl;
		valid = false;
	}
	else if (id.size() < 4) { // Can't be shorter than 9 char
		cout << "Account IDs must follow the CXXX format (too short)" << endl;
		valid = false;
	}
	else {
		if (id[0] != 'C') { // Checks if first char is C
			cout << "Account IDs must begin with C" << endl;
			valid = false;
		}

		for (int i = 1; i < 4; i++) { // Checks if rest is numerical
			if (!(id[i] >= '0' && id[i] <= '9')) {
				valid = false;
				letters = true;
			}
		}

		if (letters) cout << "Account IDs must only contains number beyond 'C'" << endl; // has letter
	}

	return valid;
}

bool isInt(string s) {
	// Checks if string can be converted to int

	bool valid = true;

	for (size_t i = 0; i < s.size(); i++) {
		if (!(s[i] >= '0' && s[i] <= '9')) {
			valid = false;
		}
	}

	if (valid) return true;
	else {
		cout << s << " is not a valid number" << endl;
		return false;
	}
}

bool isDouble(string s) {
	// Checks if string can be converted to double

	bool valid = true;
	int decCount = 0;

	for (size_t i = 0; i < s.size(); i++) {
		if (!(s[i] >= '0' && s[i] <= '9') &&  s[i] != '.') {
			valid = false;
		}
		else if (s[i] == '.') {
			decCount++;
		}
	}

	if (valid && decCount <= 1) return true;
	else {
		cout << s << " is not a valid number" << endl;
		return false;
	}
}

void itemCRUD(ItemLinkedList * list) {
	// For adding, editing, deleting items. Also for updating stock

	bool cancel; // Loop variable so user can cancel at any time

	string userInput;
	string newId = "N/A";
	string newTitle = "N/A";
	string newRentType = "N/A";
	string newLoanType = "N/A";
	int newStock = 0;
	double newRentFee = 0;
	string newGenre = "N/A";
	// New values. Used for all functions

	while (true) {
		cancel = false;
		newId = "N/A";
		newTitle = "N/A";
		newRentType = "N/A";
		newLoanType = "N/A";
		newStock = 0;
		newRentFee = 0;
		newGenre = "N/A";
		// Reset all values

		cout << "Enter an option below" << endl;
		cout << "1.Add a new item" << endl;
		cout << "2.Update an existing item" << endl;
		cout << "3.Update an existing item's stock" << endl;
		cout << "4.Delete an existing item" << endl;
		cout << "Type 'Exit' to return" << endl;
		cout << "Input: ";
		cin >> userInput;
		printDivider();

		// if user type exit, break and return to main menu
		if (userInput == "exit" || userInput == "Exit") {
			break;
		}

		else if (userInput == "1") {
			// Add item
			cout << "Current items" << endl;
			list->displayAllFormatted(); // item list
			printDivider();

			cout << "Adding a new item. Type 'Exit' at anytime to stop" << endl;

			if (!cancel) cout << "Please input the item's ID in the format of IXXX-YEAR:" << endl;
			while (!cancel) { // Loop for inputing ID
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else if (validateItemId(userInput)) { // validates
					if (list->findById(userInput) == NULL) {
						newId = userInput;
						break;
					}
					else {
						cout << "Item ID already exists" << endl;
					}
				}
				
			}

			if (!cancel) cout << "Please input the item's title:" << endl; 
			while (!cancel) { // Loop for inputing title. No validation since who knows what could be a video title?
				cout << "Input: ";
				cin.ignore();
				getline(cin, userInput);
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else {
					newTitle = userInput;
					break;
				}
			}

			if (!cancel) {
				cout << "Please select the item's type:" << endl;
				cout << "1.Game" << endl;
				cout << "2.Record" << endl;
				cout << "2.DVD" << endl;
			}
			while (!cancel) { // Loop for inputing rent type. Selection menu so can handle possible data easier
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else if (userInput == "1") {
					newRentType = "Game";
					break;
				}
				else if (userInput == "2") {
					newRentType = "Record";
					break;
				}
				else if (userInput == "3") {
					newRentType = "DVD";
					break;
				}
				else {
					cout << "Invalid option. Please try again" << endl;
				}
			}

			if (!cancel) {
				cout << "Please select the item's loan type:" << endl;
				cout << "1.2-day" << endl;
				cout << "2.1-week" << endl;
			}
			while (!cancel) { // Loop for inputing loan type. Selection menu so can handle possible data easier
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else if (userInput == "1") {
					newLoanType = "2-day";
					break;
				}
				else if (userInput == "2") {
					newLoanType = "1-week";
					break;
				}
				else {
					cout << "Invalid option. Please try again" << endl;
				}
			}

			if (!cancel) cout << "Please input the item's current stock:" << endl;
			while (!cancel) { // Loop for inputing stock.
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else if (isInt(userInput)) { // validates
					newStock = stoi(userInput);
					break;
				}
			}

			if (!cancel) cout << "Please input the item's rental fee:" << endl;
			while (!cancel) { // Loop for inputing fee.
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else if (isDouble(userInput)) { // validates
					newRentFee = stod(userInput);
					break;
				}
			}

			if (!cancel && (newRentType != "Game")) cout << "Please input the item's genre:" << endl; // If not game, input genre
			while (!cancel && (newRentType != "Game")) {
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else {
					newGenre = userInput;
					break;
				}
			}

			if (!cancel) {
				Item* newItem = new Item(newId, newTitle, newRentType, newLoanType, newStock, newRentFee, newGenre); // Create new item
				list->add(newItem); // Add item ptr to list
				cout << "The following item was added" << endl;
				cout << *newItem << endl;
				printDivider();
			}
			else {
				cout << "Add item canceled. Returning" << endl;
				printDivider();
			}
		}
		else if (userInput == "2") {
			// Edit item
			cout << "Current items" << endl;
			list->displayAllFormatted();
			printDivider();

			cout << "Please input the ID of the item you would like to edit. Type 'Exit' to cancel at anytime" << endl;
			while (!cancel) {
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else {
					Item* item = list->findById(userInput); // Tries to find item
					if (item != NULL) { // If item found
						printDivider();
						cout << "Editing item with ID " << item->getId() << endl;
						cout << *item << endl;

						if (!cancel) cout << "Please input the item's new title:" << endl;
						while (!cancel) { // New title loop
							cout << "Input: ";
							cin.ignore();
							getline(cin, userInput);
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else {
								newTitle = userInput;
								break;
							}
						}

						if (!cancel) {
							cout << "Please select the item's new type:" << endl;
							cout << "1.Game" << endl;
							cout << "2.Record" << endl;
							cout << "2.DVD" << endl;
						}
						while (!cancel) { // New type loop
							cout << "Input: ";
							cin >> userInput;
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else if (userInput == "1") {
								newRentType = "Game";
								break;
							}
							else if (userInput == "2") {
								newRentType = "Record";
								break;
							}
							else if (userInput == "3") {
								newRentType = "DVD";
								break;
							}
							else {
								cout << "Invalid option. Please try again" << endl;
							}
						}

						if (!cancel) {
							cout << "Please select the item's new loan type:" << endl;
							cout << "1.2-day" << endl;
							cout << "2.1-week" << endl;
						}
						while (!cancel) { // New loan type loop
							cout << "Input: ";
							cin >> userInput;
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else if (userInput == "1") {
								newLoanType = "2-day";
								break;
							}
							else if (userInput == "2") {
								newLoanType = "1-week";
								break;
							}
							else {
								cout << "Invalid option. Please try again" << endl;
							}
						}

						if (!cancel) cout << "Please input the item's new stock:" << endl;
						while (!cancel) { // New stock loop
							cout << "Input: ";
							cin >> userInput;
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else if (isInt(userInput)) {
								newStock = stoi(userInput);
								break;
							}
						}

						if (!cancel) cout << "Please input the item's new rental fee:" << endl;
						while (!cancel) { // New fee loop
							cout << "Input: ";
							cin >> userInput;
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else if (isDouble(userInput)) {
								newRentFee = stod(userInput);
								break;
							}
						}

						if (!cancel && (newRentType != "Game")) cout << "Please input the item's new genre:" << endl; // If is not game, new genre loop
						while (!cancel && (newRentType != "Game")) {
							cout << "Input: ";
							cin >> userInput;
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else {
								newGenre = userInput;
								break;
							}
						}

						if (!cancel) {
							// Sets new item atrributes
							item->setTitle(newTitle);
							item->setRentType(newRentType);
							item->setLoanType(newLoanType);
							item->setStock(newStock);
							item->setRentFee(newRentFee);
							item->setGenre(newGenre);
							cout << "The following item was successfully edited" << endl;
							cout << *item << endl;
							printDivider();
							break;
						}
					}
					else {
						cout << "Item not found. Please try again." << endl;
					}
				}
			}
		}
		else if (userInput == "3") {
		// Update stock. Similar to edit item except it's only the stock
		cout << "Current items" << endl;
		list->displayAllFormatted();
		printDivider();

		cout << "Please input the ID of the item you would like to edit. Type 'Exit' to cancel at anytime" << endl;
		while (!cancel) {
			cout << "Input: ";
			cin >> userInput;
			if (userInput == "exit" || userInput == "Exit") {
				cancel = true;
			}
			else {
				Item* item = list->findById(userInput);
				if (item != NULL) {
					printDivider();
					cout << "Editing item with ID " << item->getId() << endl;
					cout << *item << endl;

					if (!cancel) cout << "Please input the item's new stock:" << endl;
					while (!cancel) {
						cout << "Input: ";
						cin >> userInput;
						if (userInput == "exit" || userInput == "Exit") {
							cancel = true;
						}
						else if (isInt(userInput)) {
							newStock = stoi(userInput);
							break;
						}
					}

					if (!cancel) {
						item->setStock(newStock);
						cout << "The following item was successfully edited" << endl;
						cout << *item << endl;
						printDivider();
						break;
					}
				}
				else {
					cout << "Item not found. Please try again." << endl;
				}
			}
		}
		}
		else if (userInput == "4") {
			// Delete item
			cout << "Current items" << endl;
			list->displayAllFormatted();
			printDivider();

			cout << "Please input the ID of the item you would like to delete. Type 'Exit' to cancel at anytime" << endl;
			while (!cancel) {
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else {
					Item* item = list->findById(userInput); // Find item
					if (item != NULL) {
						cout << "You're about to delete the following item. Confirm? (y). Type 'Exit' to cancel" << endl; // Confirm deletion
						cout << *item << endl;

						while (!cancel) {
							cout << "Input: ";
							cin >> userInput;
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else if (userInput == "y") {
								list->remove(item); // This deletes the item itself, not just the linkedlist node
								cout << "The item has been removed" << endl;
								printDivider();
								cancel = true;
							}
						}
					}
					else {
						cout << "Item not found. Please try again." << endl;
					}
				}
			}
		}
		else {
			cout << "Invalid option. Please try again" << endl;
			printDivider();
		}
	}
}

void userCRUD(AccountLinkedList * list) {
	// Handles adding new users and editing current users
	string userInput;
	bool cancel;
	string newType = "N/A";
	string newId = "N/A";
	string newName = "N/A";
	string newAddress = "N/A";
	string newPhone = "N/A";
	int newReturned = 0;
	while (true) {
		cancel = false;
		newId = "N/A";
		newName = "N/A";
		newAddress = "N/A";
		newPhone = "N/A";

		cout << "Enter an option below" << endl;
		cout << "1.Add a new acount" << endl;
		cout << "2.Update an existing account" << endl;
		cout << "Type 'Exit' to return" << endl;
		cout << "Input: ";
		cin >> userInput;
		printDivider();
		if (userInput == "exit" || userInput == "Exit") {
			break;
		}
		else if (userInput == "1") {
			// Add account

			cout << "Current accounts" << endl;
			list->displayAllFormatted();
			printDivider();

			cout << "Adding a new account. Type 'Exit' at anytime to stop" << endl;

			if (!cancel) {
				cout << "Please select the account type:" << endl;
				cout << "1.Guest" << endl;
				cout << "2.Regular" << endl;
				cout << "2.VIP" << endl;
			}
			while (!cancel) {
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else if (userInput == "1") {
					newType = "guest";
					break;
				}
				else if (userInput == "2") {
					newType = "regular";
					break;
				}
				else if (userInput == "3") {
					newType = "VIP";
					break;
				}
				else {
					cout << "Invalid option. Please try again" << endl;
				}
			}

			if (!cancel) cout << "Please input the account ID in the format of CXXX:" << endl;

			while (!cancel) {
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else if (validateAccId(userInput)) {
					if (list->findById(userInput) == NULL) {
						newId = userInput;
						break;
					}
					else {
						cout << "Account ID already exists" << endl;
					}
				}

			}

			if (!cancel) cout << "Please input the customer's name:" << endl;
			while (!cancel) {
				cout << "Input: ";
				cin.ignore();
				getline(cin, userInput);
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else {
					newName = userInput;
					break;
				}
			}

			if (!cancel) cout << "Please input the customer's address:" << endl;
			while (!cancel) {
				cout << "Input: ";
				getline(cin, userInput);
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else {
					newAddress = userInput;
					break;
				}
			}

			if (!cancel) cout << "Please input the customer's phone:" << endl;
			while (!cancel) {
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else {
					newPhone = userInput;
					break;
				}
			}

			if (!cancel) {
				Account* newAcc = new Guest();

				// Creates new account based on type input
				if (newType == "VIP"){
					delete newAcc;
					newAcc = new VIP(newId, newName, newAddress, newPhone);
					
				}
				else if (newType == "regular") {
					delete newAcc;
					newAcc = new Regular(newId, newName, newAddress, newPhone);
				}
				else {
					delete newAcc;
					newAcc = new Guest(newId, newName, newAddress, newPhone);
				}
				list->add(newAcc);
				cout << "The following account was added" << endl;
				cout << newAcc->getId() << " | " << newAcc->getName() << " | " << newAcc->getAddress() << " | " << newAcc->getPhone() << endl;
				printDivider();
				
				
			}
			else {
				cout << "Add account canceled. Returning" << endl;
				printDivider();
			}
		}
		else if (userInput == "2") {
			// Edit account
			cout << "Current accounts" << endl;
			list->displayAllFormatted();
			printDivider();

			cout << "Please input the ID of the account you would like to edit. Type 'Exit' to cancel at anytime" << endl;
			while (!cancel) {
				cout << "Input: ";
				cin >> userInput;
				if (userInput == "exit" || userInput == "Exit") {
					cancel = true;
				}
				else {
					Account* acc = list->findById(userInput);
					if (acc != NULL) {
						printDivider();
						cout << "Editing account with ID " << acc->getId() << endl;
						cout << acc->getId() << " | " << acc->getName() << " | " << acc->getAddress() << " | " << acc->getPhone() << " | " << acc->getNumReturned() << endl;
						
						if (!cancel) cout << "Please input the customer's new name:" << endl;
						while (!cancel) {
							cout << "Input: ";
							cin.ignore();
							getline(cin, userInput);
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else {
								newName = userInput;
								break;
							}
						}

						if (!cancel) cout << "Please input the customer's new address:" << endl;
						while (!cancel) {
							cout << "Input: ";
							//cin.ignore();
							getline(cin, userInput);
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else {
								newAddress = userInput;
								break;
							}
						}

						if (!cancel) cout << "Please input the customer's new phone:" << endl;
						while (!cancel) {
							cout << "Input: ";
							cin >> userInput;
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else {
								newPhone = userInput;
								break;
							}
						}

						if (!cancel) cout << "Please input the customer's new successful rentals:" << endl;
						while (!cancel) {
							cout << "Input: ";
							cin >> userInput;
							if (userInput == "exit" || userInput == "Exit") {
								cancel = true;
							}
							else if (isInt(userInput)) {
								newReturned = stoi(userInput);
								break;
							}
						}

						if (!cancel) {
							acc->setName(newName);
							acc->setAddress(newAddress);
							acc->setPhone(newPhone);
							acc->setNumReturned(newReturned);
							cout << "The following account was successfully edited" << endl;
							cout << acc->getId() << " | " << acc->getName() << " | " << acc->getAddress() << " | " << acc->getPhone() << " | " << acc->getNumReturned() << endl;
							printDivider();
							break;
						}
					}
					else {
						cout << "Account not found. Please try again." << endl;
					}
				}
			}
		}
		else {
			cout << "Invalid option. Please try again" << endl;
			printDivider();
		}
	}	
}

void promoteMenu(AccountLinkedList* accountList) {
	// Handles account promotion
	string userInput;
	while (true) {
		accountList->displayAllFormatted();
		cout << "All customers:" << endl;
		cout << "Please input the ID of the customer you would like to promote. Type 'Exit' to return" << endl;
		cout << "Input: ";
		cin >> userInput;
		printDivider();
		if (userInput == "exit" || userInput == "Exit") {
			break;
		}
		else {
			Account* ptr = accountList->findById(userInput);
			if (ptr == NULL) {
				cout << "No customers found with that ID. Please try again" << endl;
			}
			else {
				if (ptr->getType() == "VIP") {
					cout << "The selected customer (" << ptr->getId() << ") is already at VIP status" << endl; // Already VIP. Can't upgrade
				}
				else {
					if (ptr->getNumReturned() >= 3) { // If successful rental is 3 or more
						if (ptr->getType() == "regular") {
							// Creates new VIP account
							Account* newAcc = new VIP(ptr);
							newAcc->setNumReturned(newAcc->getNumReturned() - 3); // Lowering num of successful returns so customer can't just be promoted twice
							
							accountList->add(newAcc); // Adds new VIP account to list
							cout << "The selected customer (" << ptr->getId() << ") has been promoted to VIP status" << endl;
							accountList->remove(ptr); // Remove old account

						}
						else if (ptr->getType() == "guest") {
							// Creates new regular account
							Account* newAcc = new Regular(ptr);
							newAcc->setNumReturned(newAcc->getNumReturned() - 3); // Lowering num of successful returns so customer can't just be promoted twice
							accountList->add(newAcc); // Adds new regular account to list
							cout << "The selected customer (" << ptr->getId() << ") has been promoted to regular status" << endl;
							accountList->remove(ptr);// Remove old account
						}
					}
					else {
						cout << "The selected customer (" << ptr->getId() << ") has not completed enough rentals" << endl;
					}
				}
			}
		}
	}
}

void rentMenu(AccountLinkedList* accountList, ItemLinkedList* itemList) {
	// Rent items

	string userInput;
	bool cancel = false;

	cout << "Please input your account ID (case sensitive). Type 'Exit' at any time to return" << endl;
	while (!cancel) {
		cout << "Input:";
		cin >> userInput;
		if (userInput == "exit" || userInput == "Exit") {
			cancel = true;
		}
		else {
			Account* acc = accountList->findById(userInput);
			if (acc != NULL) {
				cout << "The following account is currently selected" << endl;
				cout << acc->getId() << " | " << acc->getName() << " | " << acc->getAddress() << " | " << acc->getPhone() << " | " << acc->getNumReturned() << endl; // Choose account to rent with. Real system should probably have some sort of login

				printDivider();

				cout << "Current items for rent" << endl;
				itemList->displayAllFormatted();
				cout << "Please input the item ID you would like to rent" << endl;

				while (!cancel) {
					cout << "Input: ";
					cin >> userInput;
					if (userInput == "exit" || userInput == "Exit") {
						cancel = true;
					}
					else {
						Item* item = itemList->findById(userInput);
						if (item != NULL) { // If item found
							cout << "You've selected the following item" << endl;
							cout << *item << endl;
							if (item->getStock() <= 0) { // If out of stock
								cout << "That item is currently out of stock. Please check again later" << endl;
								cancel = true;
							}
							else {
								if (acc->getType() == "guest" && acc->getList()->getSize() >= 2) { // If guest account has 2 or more items in the rentlist
									cout << "You've reached the rental limit of your guest account. Please return your currently rented items first" << endl;
									cancel = true;
								}
								else if (acc->getType() == "guest" && item->getLoanType() == "2-day") { // if guest tries to borrow 2-day items
									cout << "You cannot borrow 2-day items as a guest account" << endl;
									cancel = true;
								}
								else {
									bool free = false;
									if (acc->getType() == "VIP" && acc->getNumReturned() >= 10) { // If VIP has enough "points"
										cout << "As a VIP, you have successfully accumulated enough points to make a free rental. Would you like to use your points for this rental? (y/n)" << endl; // Checks if they want to rent for free
											while (!cancel) {
												cin >> userInput;
												if (userInput == "exit" || userInput == "Exit") {
													cancel = true;
												}
												else if (userInput == "y") {
													free = true;
													break;
												}
												else if (userInput == "n") {
													break;
												}
											}
									}

									printDivider();
									cout << "You're renting the following item" << endl; // Confirmation
									cout << *item << endl;
									if (free) {
										cout << "Total: 0 $ (Free)" << endl;
									}
									else {
										cout << "Total: " << item->getRentFee() << " $" << endl;
									}
									cout << "Confirm? (y/n). Type 'Exit' to return" << endl;
									while (!cancel) {
										while (!cancel) {
											cout << "Input: ";
											cin >> userInput;
											if (userInput == "exit" || userInput == "Exit") {
												cancel = true;
											}
											else if (userInput == "y") {
												acc->renting(item);
												if (free) acc->setNumReturned(acc->getNumReturned()-10); // If VIP used points, remove "points"
 												cout << "Thank you for using our services. Have a nice day" << endl;
												printDivider();
												cancel = true;
											}
											else if (userInput == "n") {
												cout << "Canceling rental. Returning" << endl;
												printDivider();
												cancel = true;
											}
										}
									}
								}
							}
						}
						else {
							cout << "No item was found with ID " << userInput << ". Please try again" << endl;
						}
					}
				}
			}
			else {
				cout << "No account was found with ID " << userInput << ". Please try again" << endl;
			}
		}

	}
}

void returnMenu(AccountLinkedList* accountList, ItemLinkedList* itemList) {
	// Return items. Similar to rent

	string userInput;
	bool cancel = false;

	cout << "Please input your account ID (case sensitive). Type 'Exit' at any time to return" << endl;
	while (!cancel) {
		cout << "Input:";
		cin >> userInput;
		if (userInput == "exit" || userInput == "Exit") {
			cancel = true;
		}
		else {
			Account* acc = accountList->findById(userInput);
			if (acc != NULL) {
				cout << "The following account is currently selected" << endl;
				cout << acc->getId() << " | " << acc->getName() << " | " << acc->getAddress() << " | " << acc->getPhone() << " | " << acc->getNumReturned() << endl;

				printDivider();

				cout << "Currently rented items" << endl;
				acc->getList()->displayAllFormatted();
				cout << "Please input the item ID you would like to return" << endl;

				while (!cancel) {
					cout << "Input: ";
					cin >> userInput;
					if (userInput == "exit" || userInput == "Exit") {
						cancel = true;
					}
					else {
						Item* item = acc->getList()->findById(userInput);
						if (item != NULL) {
							cout << "Would you like to return the following item? (y/n)" << endl;
							cout << *item << endl;
							while (!cancel) {
								cout << "Input: ";
								cin >> userInput;
								if (userInput == "exit" || userInput == "Exit") {
									cancel = true;
								}
								else if (userInput == "y") {
									acc->returning(item);
									cout << "Item returned. Thank you for using our services. Have a nice day" << endl;
									printDivider();
									cancel = true;
								}
								else if (userInput == "n") {
									cout << "Canceling return" << endl;
									printDivider();
									cancel = true;
								}
							}
						}
						else {
							cout << "No item was found with ID " << userInput << ". Please try again" << endl;
						}
					}
				}
			}
			else {
				cout << "No account was found with ID " << userInput << ". Please try again" << endl;
			}
		}

	}
}

int main(int argc, char* argv[])
{
	if (argc < 3) {
		cout << "No input files supplied. Exiting" << endl;
		return 1;
	}

	string itemFileName = argv[1]; // Reads filename from cmdline
	string cusFileName = argv[2]; // Reads filename from cmdline

	ifstream itemFileStr(itemFileName); // Opens file. Checks if file is opened. Errors otherwise.
	if (!itemFileStr) {
		cerr << "Error opening file " << itemFileName << ". Program now exiting";
		return 1;
	}
	else {
		cout << itemFileName << " successfully loaded" << endl;
	}

	ifstream cusFileStr(cusFileName); // Opens file. Checks if file is opened. Errors otherwise.
	if (!cusFileStr) {
		cerr << "Error opening file " << cusFileName << ". Program now exiting";
		return 1;
	}
	else {
		cout << cusFileName << " successfully loaded" << endl;
	}

	ItemLinkedList itemList;

	string s1;
	while (getline(itemFileStr, s1)) { // Parse items into the list
		if (s1[0] != '#') {
			Item temp = parseItem(s1);
			Item *item = new Item();
			item->setAll(temp.getId(), temp.getTitle(), temp.getRentType(), temp.getLoanType(), temp.getStock(), temp.getRentFee(), temp.getGenre()); // Fix this later. This isn't very efficient
			itemList.add(item);
		}
	}

	AccountLinkedList accountList;

	string s2;
	Account* currentPtr = NULL;
	while (getline(cusFileStr, s2)) { // Parse accounts and rented items into a list;
		if (s2[0] != '#') {
			if (s2[0] == 'C') {

				string tempId = "N/A";
				string tempName = "N/A";
				string tempAddress = "N/A";
				string tempPhone = "N/A";
				int numRented = 0;
				int numReturned = 0;
				string type = "N/A";

				size_t found;

				found = s2.find(',');
				if (found != string::npos) {
					tempId = s2.substr(0, found);
					s2.erase(0, found + 1);
				}

				found = s2.find(',');
				if (found != string::npos) {
					tempName = s2.substr(0, found);
					s2.erase(0, found + 1);
				}

				found = s2.find(',');
				if (found != string::npos) {
					tempAddress = s2.substr(0, found);
					s2.erase(0, found + 1);
				}

				found = s2.find(',');
				if (found != string::npos) {
					tempPhone = s2.substr(0, found);
					s2.erase(0, found + 1);
				}

				found = s2.find(',');
				if (found != string::npos) {
					numReturned = stoi(s2.substr(0, found));
					s2.erase(0, found + 1);
				}

				type = s2;

				if (type == "Guest") {
					currentPtr = new Guest(tempId, tempName, tempAddress, tempPhone, numRented, numReturned);
					accountList.add(currentPtr);
				}
				else if (type == "Regular") {
					currentPtr = new Regular(tempId, tempName, tempAddress, tempPhone, numRented, numReturned);
					accountList.add(currentPtr);
				}
				else if (type == "VIP") {
					currentPtr = new VIP(tempId, tempName, tempAddress, tempPhone, numRented, numReturned);
					accountList.add(currentPtr);
				}
			}
			else if ((s2[0] == 'I') && (currentPtr != NULL)){
				Item* ptr = itemList.findById(s2);
				if (ptr != NULL) { // If item found add to account rentlist. Otherwise do nothing
					currentPtr->addItem(ptr); // This does not change stock
				}
				else {
					cout << "failed to find " << s2 << endl;
				}
			}
			else {
				cout << "Invalid line. Skipping";
			}
		}
			
	}

	//Closing after loading
	itemFileStr.close();
	cusFileStr.close();

	printDivider();

	while (true) { // Top loop
		string userInput;
		printMainMenu();
		cout << "Input: ";
		cin >> userInput;
		printDivider();
		if (userInput == "exit" || userInput == "Exit") {
			cout << "Program exiting" << endl;
			break;
		}
		else if (userInput == "1") {
			// Items CRUD
			itemCRUD(&itemList);
		}
		else if (userInput == "2") {
			// Account CRUD
			userCRUD(&accountList);
		}
		else if (userInput == "3") {
			// Promote customer
			promoteMenu(&accountList);
			
		}
		else if (userInput == "4") {
			// Rent item
			rentMenu(&accountList, &itemList);
		}
		else if (userInput == "5") {
			// Return item
			returnMenu(&accountList, &itemList);
		}
		else if (userInput == "6") {
			// Display all items
			cout << "All items:" << endl;
			itemList.displayAllFormatted();
			printDivider();
		}
		else if (userInput == "7") {
			// Display out-of-stock items
			cout << "Ttems currently out of stock:" << endl;
			itemList.displayOutOfStockFormatted();
			printDivider();
		}
		else if (userInput == "8") {
			// Display all customers
			cout << "All customers:" << endl;
			accountList.displayAllFormatted();
			printDivider();
		}
		else if (userInput == "9") {
			// Display groups of customers
			while (true) {
				cout << "Enter an option below" << endl;
				cout << "1.Display all Guest accounts" << endl;
				cout << "2.Display all Regular accounts" << endl;
				cout << "3.Display all VIP accounts" << endl;
				cout << "Type 'Exit' to return" << endl;
				cout << "Input: ";
				cin >> userInput;
				printDivider();
				if (userInput == "exit" || userInput == "Exit") {
					break;
				}
				else if (userInput == "1") {
					// Display guests customers
					cout << "Guest customers:" << endl;
					accountList.displayAllByTypeFormatted("guest");
					printDivider();
				}
				else if (userInput == "2") {
					// Display display regular customers
					cout << "Regular customers:" << endl;
					accountList.displayAllByTypeFormatted("regular");
					printDivider();
				}
				else if (userInput == "3") {
					// Display VIP customers
					cout << "VIP customers:" << endl;
					accountList.displayAllByTypeFormatted("VIP");
					printDivider();
				}
				else {
					cout << "Invalid option. Please try again" << endl;
					printDivider();
				}
			}
		}
		else if (userInput == "10") {
			// Search for items or customers
			while (true) {
				cout << "Enter an option below" << endl;
				cout << "1.Search for an item by ID" << endl;
				cout << "2.Search for an item by Title" << endl;
				cout << "3.Search for a customer by ID" << endl;
				cout << "4.Search for a customer by Name" << endl;
				cout << "Type 'Exit' to return" << endl;
				cout << "Input: ";
				cin >> userInput;
				printDivider();
				if (userInput == "exit" || userInput == "Exit") {
					break;
				}
				else if (userInput == "1") {
					cout << "Please input the item's ID (Case-Sensitive): ";
					cin >> userInput;
					printDivider();
					Item* found = itemList.findById(userInput);
					if (found != NULL) {
						cout << "Item Found" << endl;
						cout << *found << endl;
					}
					else {
						cout << "No item found with ID " << userInput << ". Please try again" << endl;
					}
					printDivider();
				}
				else if (userInput == "2") {
					string title;
					cout << "Please input the item's title (Case-Sensitive): ";
					cin.ignore();
					getline(cin, title);
					printDivider();
					Item* found = itemList.findByTitle(title);
					if (found != NULL) {
						cout << "Item Found" << endl;
						cout << *found << endl;
					}
					else {
						cout << "No items found with title " << title << ". Please try again" << endl;
					}
					printDivider();
				}
				else if (userInput == "3") {
					cout << "Please input the customer's ID (Case-Sensitive): ";
					cin >> userInput;
					printDivider();
					Account* found = accountList.findById(userInput);
					if (found != NULL) {
						cout << "Customer Found" << endl;
						cout << found->getId() << " | " << found->getName() << " | " << found->getAddress() << " | " << found->getPhone() << " | " << found->getNumReturned() << endl;
					}
					else {
						cout << "No customers found with ID " << userInput << ". Please try again" << endl;
					}
					printDivider();
				}
				else if (userInput == "4") {
					string name;
					cout << "Please input the customer's name (Case-Sensitive): ";
					cin.ignore();
					getline(cin, name);
					printDivider();
					Account* found = accountList.findByName(name);
					if (found != NULL) {
						cout << "Customer Found" << endl;
						cout << found->getId() << " | " << found->getName() << " | " << found->getAddress() << " | " << found->getPhone() << " | " << found->getNumReturned() << endl;
					}
					else {
						cout << "No customers found with name " << name << ". Please try again" << endl;
					}
					printDivider();
				}
				else {
					cout << "Invalid option. Please try again" << endl;
					printDivider();
				}
			}
			
		}
		else {
			cout << "Invalid option. Please try again" << endl;
			printDivider();
		}
	}

	// Cleanup code goes here

	// Load files and write files

	ofstream itemOutFileStr(itemFileName, ios::trunc); // Opens file. Checks if file is opened. Errors otherwise.
	if (!itemOutFileStr) {
		cerr << "Error opening file " << itemFileName << ". Program now exiting";
		return 1;
	}
	else {
		itemList.writeToStream(itemOutFileStr); // pass stream to write function
		cout << itemFileName << " successfully written" << endl;
	}

	ofstream cusOutFileStr(cusFileName, ios::trunc); // opens file. checks if file is opened. errors otherwise.
	if (!cusOutFileStr) {
		cerr << "error opening file " << cusFileName << ". program now exiting";
		return 1;
	}
	else {
		accountList.writeToStream(cusOutFileStr); // pass stream to write function
		cout << cusFileName << " successfully written" << endl;
	}
	

	// Close files
	itemOutFileStr.close();
	cusOutFileStr.close();

	cout << "ASSIGNMENT 2 GROUP 9" << endl;
	cout << "s3694603,s3694603@rmit.edu.vn,Khoi,Dang" << endl;

	return 0;
}
