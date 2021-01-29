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

	return Item(tempId, tempTitle, tempRentType, tempLoanType, tempStock, tempFee, tempGenre);
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

void itemCRUD() {
	while (true) {
		string userInput;
		cout << "Enter an option below" << endl;
		cout << "1.Add a new item" << endl;
		cout << "2.Update an existing item" << endl;
		cout << "3.Delete an existing item" << endl;
		cout << "Type 'Exit' to return" << endl;
		cout << "Input: ";
		cin >> userInput;
		printDivider();
		if (userInput == "exit" || userInput == "Exit") {
			break;
		}
		else if (userInput == "1") {
			// Add item
			cout << "Adding a new item. Type 'cancel' at anytime to stop" << endl;
		}
		else if (userInput == "2") {
			// Return item
			cout << 5;
		}
		else if (userInput == "3") {
			// Return item
			cout << 5;
		}
		else {
			cout << "Invalid option. Please try again" << endl;
			printDivider();
		}
	}
}

void userCRUD() {
	while (true) {
		string userInput;
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
			// Rent item
			cout << 4;
		}
		else if (userInput == "2") {
			// Return item
			cout << 5;
		}
		else {
			cout << "Invalid option. Please try again" << endl;
			printDivider();
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

	ifstream itemFileStr(itemFileName, ios::in); // Opens file. Checks if file is opened. Errors otherwise.
	if (!itemFileStr) {
		cerr << "Error opening file " << itemFileName << ". Program now exiting";
		return 1;
	}
	else {
		cout << itemFileName << " successfully loaded" << endl;
	}

	ifstream cusFileStr(cusFileName, ios::in); // Opens file. Checks if file is opened. Errors otherwise.
	if (!cusFileStr) {
		cerr << "Error opening file " << cusFileName << ". Program now exiting";
		return 1;
	}
	else {
		cout << cusFileName << " successfully loaded" << endl;
	}

	// Parse and loads the items into a dynamic array or linked list?
	//Item* itemList = new Item[1];
	ItemLinkedList itemList;

	string s1;
	while (getline(itemFileStr, s1)) {
		if (s1[0] != '#') {
			Item temp = parseItem(s1);
			Item *item = new Item();
			item->setAll(temp.getId(), temp.getTitle(), temp.getRentType(), temp.getLoanType(), temp.getStock(), temp.getRentFee(), temp.getGenre()); // Fix this later. This isn't very efficient
			itemList.add(item);
		}
	}

	//itemList.displayAll();

	// Loads the customers into a dynamic array or linked list?
	AccountLinkedList accountList;

	string s2;
	Account* currentPtr = NULL;
	while (getline(cusFileStr, s2)) {
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
				if (ptr != NULL) {
					currentPtr->addItem(ptr);
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

	//accountList.displayAll();
	accountList.displayAll();

	printDivider();

	while (true) {
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
			itemCRUD();
		}
		else if (userInput == "2") {
			// Account CRUD
			userCRUD();
		}
		else if (userInput == "3") {
			// Promote customer
			while (true) {
				accountList.displayAllFormatted();
				cout << "All customers:" << endl;
				cout << "Please input the ID of the customer you would like to promote. Type 'Exit' to return" << endl;
				cout << "Input: ";
				cin >> userInput;
				printDivider();
				if (userInput == "exit" || userInput == "Exit") {
					break;
				}
				else {
					Account* ptr = accountList.findById(userInput);
					if (ptr == NULL) {
						cout << "No customers found with that ID. Please try again" << endl;
					}
					else {
						if (ptr->getType() == "VIP") {
							cout << "The selected customer (" << ptr->getId() << ") is already at VIP status" << endl;
						}
						else {
							if (ptr->getNumReturned() >= 3) {
								if (ptr->getType() == "regular") {
									Account* newAcc = new VIP(ptr);
									newAcc->setNumReturned(newAcc->getNumReturned() - 3); // Lowering num of successful returns so customer can't just be promoted twice
									accountList.add(newAcc);
									cout << "The selected customer (" << ptr->getId() << ") has been promoted to VIP status" << endl;
									accountList.remove(ptr);

								}
								else if (ptr->getType() == "guest") {
									Account* newAcc = new Regular(ptr);
									newAcc->setNumReturned(newAcc->getNumReturned() - 3); // Lowering num of successful returns so customer can't just be promoted twice
									accountList.add(newAcc);
									cout << "The selected customer (" << ptr->getId() << ") has been promoted to regular status" << endl;
									accountList.remove(ptr);
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
		else if (userInput == "4") {
			// Rent item
			cout << 4;
		}
		else if (userInput == "5") {
			// Return item
			cout << 5;
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
					cout << "All customers:" << endl;
					accountList.displayAllGuestFormatted();
					printDivider();
				}
				else if (userInput == "2") {
					// Display display regular customers
					cout << "All customers:" << endl;
					accountList.displayAllRegFormatted();
					printDivider();
				}
				else if (userInput == "3") {
					// Display VIP customers
					cout << "All customers:" << endl;
					accountList.displayAllVIPFormatted();
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


	cout << "ASSIGNMENT 2 GROUP 9" << endl;
	cout << "s3694603,s3694603@rmit.edu.vn,Khoi,Dang" << endl;

	return 0;
}
