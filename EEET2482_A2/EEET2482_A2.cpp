// EEET2482_A2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

#include "Account.h"
#include "Guest.h"
#include "Item.h"

#include "ItemLinkedList.h"

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

	string s;
	while (getline(itemFileStr, s)) {
		if (s[0] != '#') {

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
				s.erase(0, found + 1);
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

			Item item(tempId, tempTitle, tempRentType, tempLoanType, tempStock, tempFee, tempGenre);

			cout << item << endl;
			itemList.push(&item);
		}
	}

	itemList.display();

	//DEBUG
	/*Item i1("001", "hello world", "eh", "eh", 3, 1.99);
	Item i2("002", "hello world2", "eh", "eh", 3, 1.99);
	Item i3("003", "hello world2", "eh", "eh", 3, 1.99);
	Item i4("004", "hello world2", "eh", "eh", 3, 1.99);

	itemList.push(&i1);
	itemList.push(&i2);
	itemList.push(&i3);
	itemList.push(&i4);

	itemList.display();*/

	// Loads the customers into a dynamic array or linked list?
	Account** accountList = new Account*[1];

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
	/*delete[] itemList;
	itemList = NULL;*/

	delete[] accountList;
	accountList = NULL;


	cout << "ASSIGNMENT 2 GROUP 9" << endl;
	cout << "s3694603,s3694603@rmit.edu.vn,Khoi,Dang" << endl;

	return 0;
}
