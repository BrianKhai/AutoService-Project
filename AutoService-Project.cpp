
#include <iostream>
#include <string>
#include <fstream>

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

struct car {
	string make, model;
	int vin, liscense;
};

class Company {
	void manufacturing();
	void dealership();
	void maintenace();
	void customer();
	void manager(); //grad portion
};


int verify_login(string username, string password, string role) {
	int verify;

	if (username == "Bob" && password == "ManuFact!2" && role == "Manufacturer") {
		verify = 1;
	}
	else if (username == "Joe" && password == "pass22" && role == "Dealership") {
		verify = 2;
	}
	else if (username == "Hendrick" && password == "Maintain@12" && role == "Maintenance") {
		verify = 3;
	}
	else if (username == "Dan" && password == "GimmeACar" && role == "Customer") {
		verify = 4;
	}
	else {
		verify = 0;
	}

	return verify;
}

int main() {
	string Username;
	string Password;
	string Role;

	Company carCompany;

	ofstream manufacturingInventory;
	ofstream dealershipInventory;
	ofstream maintenaceInventory;

	manufacturingInventory.open("manufacturing_database");
	dealershipInventory.open("dealership_database");
	maintenaceInventory.open("maintenace_database");

	do
	{
		cout << "Enter Username: ";
		cin >> Username;
		cout << "\n";
		cout << "Enter Password: ";
		cin >> Password;
		cout << "\n";
		cout << "Enter your role: ";
		cin >> Role;
		cout << "\n";


		if (verify_login(Username, Password, Role) == 1) {
			cout << "Manufacturing stuff";
		}
		if (verify_login(Username, Password, Role) == 2) {
			cout << "Dealership stuff";
		}
		if (verify_login(Username, Password, Role) == 3) {
			cout << "Maintenace stuff";
		}
		if (verify_login(Username, Password, Role) == 4) {
			cout << "Customer stuff";

		}
	} while (verify_login(Username, Password, Role) < 1 || verify_login(Username, Password, Role) > 4);

	manufacturingInventory.close();
	dealershipInventory.close();
	maintenaceInventory.close();
	return 0;
}