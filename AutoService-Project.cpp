#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

/*
(If your team is not familiar with creating a GUI or using databases, you can use the C++ text
based interface and files to handles your input and output.  Do not leave any team members
behind by choosing a solution that is beyond their skillset.)
Your company has been hired by a large car manufacturer to develop software to handle various
processes in their business.  There are currently five different car models with 3 variations of
each model with future cars designs being developed.  The car manufacturer wants a full stack
software solution for the following needs:
The manufacturing facilities (the plants that build the cars) are losing track of parts and
materials and need a software tool to track all the car parts and materials (e.g. glass, bolts,
chairs, steel) that have been purchased and received from suppliers.  They may have over 100
different suppliers.
Car dealerships need new software to order new cars from the car manufacturer. The dealerships
only have so much space in their lots, depending on how big of a dealership they own.
Repair shops, auto stores, and dealerships need to be able to order parts from the car
manufacturer to keep their stock from running out.
Customers need a way to order new and used cars directly from the car manufacturer that can
then be picked up at a local dealership.
*/

/*
------------------------------------------------------------------------------------------------
Minimum Requirements
Database
	5 car models
	3 variations each
Menu displays (TBD) submenus
	Manufacturing
		Cars
		Parts		(Engine components)
		Materials	(Glass, bolts, chairs, steel)
		Show supplier
	Dealership
		Order car from manufacturing (Update manufacturing inventory)
		Buying and selling
	Repair Shop, Auto Store, dealership
		Order parts from manufacturing (Update manufacturing inventory)
	Customer
		Order new/used cars from manufacturer (Update manufacturing inventory)
------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------
High Level Requirements (WIP):
"*" = Required
"~" = Extra/Implied?/Frivilous
"+" = Done
"/" = In progress
"-" = Note
	* Track all car parts and materials
		~ And cars in inventory?
		* That have been purchased and received
			- From suppliers
		~ Keep history for last X period
		~ Status of current item (shipping in/out, slated for use, available, unavailable)
			- If in use maybe include date to be used
	* Car dealerships need new software to order new cars from the car manufacturer
		~ Show cars
		~ Car status
		* Upper limit on space in lot
			- Allow users to set up their lot size
	* Repair shops, auto stores, and dealerships need to be able to order parts from the car
			manufacturer to keep their stock from running out
		~ Show inventory
		~ Show status of item
	* Customers need a way to order new and used cars directly from the car manufacturer
		~ Show diferent dealerships with different cars?
			- Give them locations?
	* Customers want manager to show cost of all parts, as well as, show profit to customers and repair/auto shops
		~ Show parts and cost
		~ Show profits
------------------------------------------------------------------------------------------------
*/

const string MANUFACTURING_FILE = "manufacturing_database";
const string DEALERSHIP_FILE = "manufacturing_database";
const string MAINTENANCE_FILE = "manufacturing_database";

struct car {
	string make, model;
	int vin, liscense;
};

class Company {

public:
	void manufacturing(ifstream& manufacturingInventoryIn, ofstream& manufacturingInventoryOut);
	void dealership(ifstream& dealershipInventoryIn, ofstream& dealershipInventoryOut);
	void maintenace(ifstream& maintenaceInventoryIn, ofstream& maintenaceInventoryOut);
	void customer();
	void manager(); //grad portion
} carCompany;

int verify_login(string username, string password, string role);


int main() {
	return 0;
}

int verify_login(string username, string password, string role) {
	int verify;

	if (username == "Bob" && password == "123" && role == "M") {
		verify = 1;
	} else if (username == "Joe" && password == "pass22" && role == "Dealership") {
		verify = 2;
	} else if (username == "Hendrick" && password == "Maintain@12" && role == "Maintenance") {
		verify = 3;
	} else if (username == "Dan" && password == "GimmeACar" && role == "Customer") {
		verify = 4;
	} else {
		verify = 0;
	}

	return verify;
}

/*
		Cars
		Parts		(Engine components)
		Materials	(Glass, bolts, chairs, steel)
		Show supplier
*/

void Company::manufacturing(ifstream& manufacturingInventoryIn, ofstream& manufacturingInventoryOut) {

	int count;
	int date;
	string item;

	int input = 0;
	while (true) {
		cout << "[0] Display" << endl;
		cout << "[1] Add" << endl;
		cout << "[2] Search" << endl;
		cin >> input;

		if (input == 0) {
			manufacturingInventoryIn.open(MANUFACTURING_FILE);

			cout << "Display items" << endl;
			if (manufacturingInventoryIn.is_open()) {
				cout << setw(20) << "Count" << setw(20) << "Date" << setw(20) << "Item" << endl;
				while (manufacturingInventoryIn >> count >> date >> item) {
					cout << setw(20) << count << setw(20) << date << setw(20) << item << endl;
				}
			}

			manufacturingInventoryIn.close();
		} else if (input == 1) {
			manufacturingInventoryOut.open(MANUFACTURING_FILE, ios::app);
			cout << "Adding items" << endl;
			cout << "Input stock" << endl;
			cin >> count;
			cout << "Input date" << endl;
			cin >> date;
			cout << "Input item" << endl;
			cin >> item;
			manufacturingInventoryOut << count << " " << date << " " << item;
			manufacturingInventoryOut.close();
		} else if (input == 2) {
			manufacturingInventoryIn.open(MANUFACTURING_FILE);
			string search;
			cout << "Searching for items" << endl;
			cout << "Item name:" << endl;
			cin >> search;

			if (manufacturingInventoryIn.is_open()) {
				cout << setw(20) << "Count" << setw(20) << "Date" << setw(20) << "Item" << endl;
				while (manufacturingInventoryIn >> count >> date >> item) {
					if (item == search) {
						cout << setw(20) << count << setw(20) << date << setw(20) << item << endl;
					}
				}
			}
			manufacturingInventoryIn.close();
		}
	}


}

void Company::dealership(ifstream& dealershipInventoryIn, ofstream& dealershipInventoryOut) {
	dealershipInventoryOut.open(DEALERSHIP_FILE);

	dealershipInventoryOut.close();
}

void Company::maintenace(ifstream& maintenaceInventoryIn, ofstream& maintenaceInventoryOut) {
	maintenaceInventoryOut.open(MAINTENANCE_FILE);

	maintenaceInventoryOut.close();
}

void Company::customer() {

}

void Company::manager() {

}