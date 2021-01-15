// EEET2482_A2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

#include "Account.h"
#include "Guest.h"
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
	cout << "Exit." << endl;
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

	itemList.displayAll();

	// Loads the customers into a dynamic array or linked list?
	AccountLinkedList accountList;

	string s2;
	Account* currentPtr = NULL;
	while (getline(cusFileStr, s2)) {
		if (s2[0] != '#') {
			if (s2[0] == 'C') {

				if (currentPtr != NULL) {
					accountList.add(currentPtr);
				}

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
				}
				else if (type == "Regular") {
					currentPtr = new Guest(tempId, tempName, tempAddress, tempPhone, numRented, numReturned);
				}
				else if (type == "VIP") {
					currentPtr = new Guest(tempId, tempName, tempAddress, tempPhone, numRented, numReturned);
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
				cout << "Invalid line";
			}
		}
			
	}

	//accountList.displayAll();

	//Account* ptr = accountList.findById("C001");

	/*Item* ptr = itemList.findById("I001-2001");
	if (ptr != NULL) {
		cout << "yes";
	}
	else {
		cout << "failed to find " << s2 << endl;
	}*/

	//string s1;
	//while (getline(itemFileStr, s1)) {
	//	if (s1[0] != '#') {
	//		Item temp = parseItem(s1);
	//		Item* item = new Item();
	//		item->setAll(temp.getId(), temp.getTitle(), temp.getRentType(), temp.getLoanType(), temp.getStock(), temp.getRentFee(), temp.getGenre()); // Fix this later. This isn't very efficient
	//		itemList.add(item);
	//	}
	//}

	printDivider();

	/*while (true) {
		string userInput;
		printMainMenu();
		cout << "Input: ";
		cin >> userInput;
		printDivider();
		if (userInput == "exit") {
			cout << "Program exiting" << endl;
			break;
		}
		else if (userInput == "1") {
			cout << "Option 1" << endl;
		}
	}*/

	// Cleanup code goes here


	cout << "ASSIGNMENT 2 GROUP 9" << endl;
	cout << "s3694603,s3694603@rmit.edu.vn,Khoi,Dang" << endl;

	return 0;
}
