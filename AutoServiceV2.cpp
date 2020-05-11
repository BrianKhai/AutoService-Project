#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

/*
terials and need a software tool to track all the car parts and materials (e.g. glass, bolts,
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
		~ Show different dealerships with different cars?
			- Give them locations?
	GRAD Portion
	* Customers want manager to show cost of all parts, as well as, show profit to customers and repair/auto shops
		~ Show parts and cost
		~ Show profits
------------------------------------------------------------------------------------------------
*/

const string MAN_CAR_FILE = "manufacturing_car_database";
const string MAN_MAT_FILE = "manufacturing_mat_database";
const string MAN_PART_FILE = "manufacturing_part_database";
const string MAN_SUP_FILE = "manufacturing_sup_database";

const string DEALERSHIP_FILE = "manufacturing_database";
const string MAINTENANCE_FILE = "manufacturing_database";
const string PROFIT_FILE = "profit_database.txt";

class Company {
	ifstream manufacturingInventoryIn;
	ifstream dealershipInventoryIn;
	ifstream maintenaceInventoryIn;
	ifstream profitIn;

	ofstream manufacturingInventoryOut;
	ofstream dealershipInventoryOut;
	ofstream maintenaceInventoryOut;
	ofstream tempOut;
public:
	void manufacturing();
	void dealership();
	void maintenace();
	void customer();
	void manager(); //grad portion
} carCompany;

int verify_login(string username, string password, string role);


int main() {
	string Username;
	string Password;
	string Role;


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
			carCompany.manufacturing();
		}
		if (verify_login(Username, Password, Role) == 2) {
			cout << "Dealership stuff" << endl;
		}
		if (verify_login(Username, Password, Role) == 3) {
			cout << "Maintenace stuff" << endl;
		}
		if (verify_login(Username, Password, Role) == 4) {
			cout << "Customer stuff" << endl;
			carCompany.customer();
		}
		if (verify_login(Username, Password, Role) == 5) {
			cout << "Manager stuff" << endl;
			carCompany.manager();
		}
	} while (verify_login(Username, Password, Role) < 1 || verify_login(Username, Password, Role) > 4);

	return 0;
}

int verify_login(string username, string password, string role) {
	int verify;

	if (username == "Bob" && password == "123" && role == "M") {
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
	else if (username == "ManagerMan" && password == "Moneyheh" && role == "Manager") {
		verify = 5;
	}
	else {
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

void Company::manufacturing() {
	int input = 0;
	int carInput = 0;
	int partInput = 0;
	int matInput = 0;
	int supInput = 0;

	// Current date stuff
	char buffer[80];
	time_t t = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &t);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y|%H:%M:%S", &timeinfo);	// Date Format
	string date = buffer;

	while (input != 4) {
		do {
			cout << "Manufacturing Main Menu" << endl;
			cout << "[0] Cars" << endl;
			cout << "[1] Parts" << endl;
			cout << "[2] Materials" << endl;
			cout << "[3] Show Supplier" << endl;
			cout << "[4] Exit" << endl;
			cin >> input;
			system("CLS");
		} while (input < 0 || input > 4);

		if (input == 0) {
			string stock, year, make, model, color, condition, price, srchMake, srchModel;


			//Display cars/////
			manufacturingInventoryIn.open(MAN_CAR_FILE);
			if (manufacturingInventoryIn.is_open()) {
				cout << setw(20) << "Last Updated" << setw(20) << "Stock" << setw(20) << "Year" << setw(20) << "Make" << setw(20) << "Model" << setw(20) << "Color" << setw(20) << "Condition" << setw(20) << "Price" << endl;
				while (manufacturingInventoryIn >> date >> stock >> year >> make >> model >> color >> condition >> price) {
					cout << setw(20) << date << setw(20) << stock << setw(20) << year << setw(20) << make << setw(20) << model << setw(20) << color << setw(20) << condition << setw(20) << price << endl;
				}
			}
			else {
				cout << "Error opening " << MAN_CAR_FILE << endl;
			}
			manufacturingInventoryIn.close();
			//////////////////

			while (carInput != 3) {

				// Cars Submenu
				do {
					cout << "Cars Submenu" << endl << endl;
					cout << "[0] Add New Cars" << endl;
					cout << "[1] Search" << endl;
					cout << "[2] Update Stock" << endl;
					cout << "[3] Return" << endl;
					cin >> carInput;
					system("CLS");
				} while (carInput < 0 || carInput > 3);

				// Cars submenu
				if (carInput == 0) {										// Add new car
					cout << "Year: ";
					cin >> year;
					cout << "Make: ";
					cin >> make;
					cout << "Model: ";
					cin >> model;
					cout << "Available colors: ";
					cin >> color;
					cout << "Stock: ";
					cin >> stock;
					cout << "Condition: ";
					cin >> condition;
					cout << "Price: ";
					cin >> price;

					manufacturingInventoryOut.open(MAN_CAR_FILE, ios::app);
					manufacturingInventoryOut << date << " " << stock << " " << year << " " << make << " " << model << " " << color << " " << condition << " " << price << endl;
					manufacturingInventoryOut.close();
					cout << "Car added" << endl << endl << endl;
				}
				else if (carInput == 1) {								// Search for car
					bool isFound = false;
					cout << "Make: ";
					cin >> srchMake;
					cout << "Model: ";
					cin >> srchModel;

					manufacturingInventoryIn.open(MAN_CAR_FILE);
					if (manufacturingInventoryIn.is_open()) {
						while (manufacturingInventoryIn >> date >> stock >> year >> make >> model >> color >> condition >> price) {
							if (srchMake == make || srchModel == model) {
								isFound = true;
								cout << setw(20) << "Last Updated" << setw(20) << "Stock" << setw(20) << "Year" << setw(20) << "Make" << setw(20) << "Model" << setw(20) << "Color" << setw(20) << "Condition" << setw(20) << "Price" << endl;
								cout << setw(20) << date << setw(20) << stock << setw(20) << year << setw(20) << make << setw(20) << model << setw(20) << color << setw(20) << condition << setw(20) << price << endl << endl << endl;
							}
						}
					}
					else {
						cout << "Error opening " << MAN_CAR_FILE << endl;
					}
					if (!isFound) {
						cout << "Item could not be found!" << endl << endl << endl;
					}
					manufacturingInventoryIn.close();
				}
				else if (carInput == 2) {										// Update car database
					cout << "Give a Make and Model to update" << endl;
					cout << "Make: ";
					cin >> srchMake;
					cout << "Model: ";
					cin >> srchModel;

					tempOut.open("temp_file");
					manufacturingInventoryIn.open(MAN_CAR_FILE);
					if (manufacturingInventoryIn.is_open()) {
						bool isFound = false;
						bool keepEntry = true;
						while (manufacturingInventoryIn >> date >> stock >> year >> make >> model >> color >> condition >> price) {
							if (srchMake == make && srchModel == model) {
								isFound = true;
								cout << "New Stock: ";
								cin >> stock;
								if (stoi(stock) == 0) {
									string userDelResponse;
									cout << "Would you like to delete this item form the database? (Yes, y)" << endl;
									cin >> userDelResponse;

									if (userDelResponse == "Yes" || userDelResponse == "Y" || userDelResponse == "yes" || userDelResponse == "y") {
										cout << make << " " << model << " deleted" << endl;
										keepEntry = false;
									}
								}
							}
							if (keepEntry) {
								tempOut << date << " " << stock << " " << year << " " << make << " " << model << " " << color << endl;
							}
							else {
								keepEntry = true;
							}
						}
						if (!isFound) {
							cout << "Item could not be found!" << endl;
						}
					}

					tempOut.close();
					manufacturingInventoryIn.close();
					if (remove("manufacturing_car_database")) {
						cout << "Error deleting file" << endl;
					}
					else {
						cout << "File successfully deleted" << endl;
					}

					if (rename("temp_file", "manufacturing_car_database")) {
						cout << "Error renaming file" << endl;
					}
					else {
						cout << "File successfully renamed" << endl;
					}
				}
			}
		}
		else if (input == 1) {							// Part submenu
			string stock, part, price, srch;

			// Display database
			manufacturingInventoryIn.open(MAN_PART_FILE);
			if (manufacturingInventoryIn.is_open()) {
				cout << setw(20) << "Last Updated" << setw(20) << "Stock" << setw(20) << "Part" << setw(20) << "Price" << endl;
				while (manufacturingInventoryIn >> date >> stock >> part >> price) {
					cout << setw(20) << date << setw(20) << stock << setw(20) << part << setw(20) << price << endl;
				}
			}
			else {
				cout << "Error opening " << MAN_PART_FILE << endl;
			}
			manufacturingInventoryIn.close();

			while (partInput != 3) {
				do {
					cout << "Parts Submenu" << endl;
					cout << "[0] Add Parts" << endl;
					cout << "[1] Search Parts" << endl;
					cout << "[2] Update Stock" << endl;
					cout << "[3] Return" << endl;
					cin >> partInput;
					system("CLS");
				} while (partInput < 0 || partInput > 3);
				// Stuff

				if (partInput == 0) {					// Add Parts
					cout << "Part name: ";
					cin >> part;
					cout << "Stock: ";
					cin >> stock;
					cout << "Price: ";
					cin >> price;

					manufacturingInventoryOut.open(MAN_PART_FILE, ios::app);
					manufacturingInventoryOut << date << " " << stock << " " << part << " " << price << endl;
					manufacturingInventoryOut.close();
					cout << "Part added" << endl << endl << endl;
				}
				else if (partInput == 1) {			// Search Parts
					bool isFound = false;
					cout << "Part name: ";
					cin >> srch;

					manufacturingInventoryIn.open(MAN_PART_FILE);
					if (manufacturingInventoryIn.is_open()) {
						while (manufacturingInventoryIn >> date >> stock >> part >> price) {
							if (srch == part) {
								isFound = true;
								cout << setw(20) << "Last Updated" << setw(20) << "Stock" << setw(20) << "Part" << endl;
								cout << setw(20) << date << setw(20) << stock << setw(20) << part << setw(20) << price << endl << endl << endl;
							}
						}
					}
					else {
						cout << "Error opening " << MAN_CAR_FILE << endl;
					}
					if (!isFound) {
						cout << "Item could not be found!" << endl << endl << endl;
					}
					manufacturingInventoryIn.close();
				}
				else if (partInput == 2) {
					cout << "Give a Part to update" << endl;
					cout << srch;
					tempOut.open("temp_file");
					manufacturingInventoryIn.open(MAN_PART_FILE);
					if (manufacturingInventoryIn.is_open()) {
						bool isFound = false;
						bool keepEntry = true;
						while (manufacturingInventoryIn >> date >> stock >> part >> price) {
							if (srch == part) {
								isFound = true;
								cout << "New Stock ";
								cin >> stock;

								if (stoi(stock) == 0) {
									string userDelResponse;
									cout << "Would you like to delete this item form the database? (Yes, y)" << endl;
									cin >> userDelResponse;

									if (userDelResponse == "Yes" || userDelResponse == "Y" || userDelResponse == "yes" || userDelResponse == "y") {
										cout << part << " deleted" << endl;
										keepEntry = false;
									}
								}
							}
							if (keepEntry) {
								cout << setw(20) << date << setw(20) << stock << setw(20) << part << setw(20) << price << endl << endl << endl;
							}
							else {
								keepEntry = true;
							}
						}
						if (!isFound) {
							cout << "Item could not be found!" << endl;
						}
					}

					tempOut.close();
					manufacturingInventoryIn.close();
					if (remove("manufacturing_part_database")) {
						cout << "Error deleting file" << endl;
					}
					else {
						cout << "File successfully deleted" << endl;
					}

					if (rename("temp_file", "manufacturing_part_database")) {
						cout << "Error renaming file" << endl;
					}
					else {
						cout << "File successfully renamed" << endl;
					}
				}
			}
		}
		else if (input == 2) {							// Materials submenu
			string stock, mat, srch;

			manufacturingInventoryIn.open(MAN_MAT_FILE);
			if (manufacturingInventoryIn.is_open()) {
				cout << setw(20) << "Last Updated" << setw(20) << "Stock" << setw(20) << "Materials" << endl;
				while (manufacturingInventoryIn >> date >> stock >> mat) {
					cout << setw(20) << date << setw(20) << stock << setw(20) << mat << endl;
				}
			}
			else {
				cout << "Error opening " << MAN_MAT_FILE << endl;
			}
			manufacturingInventoryIn.close();

			while (matInput != 3) {
				do {
					cout << "Materials Submenu" << endl;
					cout << "[0] Add Materials" << endl;
					cout << "[1] Search Materials" << endl;
					cout << "[2] Update Stock" << endl;
					cout << "[3] Return" << endl;
					cin >> matInput;
					system("CLS");
				} while (input < 0 || input > 3);
				// Stuff
			}
		}
		else if (input == 3) {							// Suppliers submenu
			string sup;

			while (supInput != 3) {
				do {
					manufacturingInventoryIn.open(MAN_SUP_FILE);
					if (manufacturingInventoryIn.is_open()) {
						cout << setw(20) << "Last Updated" << setw(20) << "Supplier" << endl;
						while (manufacturingInventoryIn >> date >> sup) {
							cout << setw(20) << date << setw(20) << sup << endl;
						}
					}
					else {
						cout << "Error opening " << MAN_SUP_FILE << endl;
					}

					manufacturingInventoryIn.close();
					cout << "Suppliers Submenu" << endl;
					cout << "[0] Add Suppliers" << endl;
					cout << "[1] Search Suppliers" << endl;
					cout << "[2] Remove Supplier" << endl;
					cout << "[3] Return" << endl;
					cin >> supInput;
					system("CLS");
				} while (partInput < 0 || partInput > 3);

				if (input == 0) {
				}
			}
		}

	}
}

void Company::dealership() {
	dealershipInventoryOut.open(DEALERSHIP_FILE);

	dealershipInventoryOut.close();
}

void Company::maintenace() {
	maintenaceInventoryOut.open(MAINTENANCE_FILE);

	maintenaceInventoryOut.close();
}

void Company::customer() {
	int choice;
	string ship;
	
	//read file
	string year;
	string make;
	string model;
	string color;
	string stock;
	string date;
	string condition;
	string price;

	//user input
	string item_year;
	string item_make;
	string item_model;
	string item_color;
	string item_condition;

		// ask customer to choose if they want a new or used car
		cout << "What type of condition do you want your car?" << endl;
		cout << "[0] New" << endl;
		cout << "[1] Used" << endl;
		cin >> choice;



		if (choice == 0) {
			manufacturingInventoryIn.open(MAN_CAR_FILE);
			item_condition = "New";

			// get desired car from customer (year, make, model, color)
			cout << endl << "Enter desired year: ";
			cin >> item_year;
			cout << endl << "Enter desired make: ";
			cin >> item_make;
			cout << endl << "Enter desired model: ";
			cin >> item_model;
			cout << endl << "Enter desired color: ";
			cin >> item_color;

			// use inputs to search for matching values and display
			if (manufacturingInventoryIn.is_open()) {
				while (manufacturingInventoryIn >> date >> stock >> year >> make >> model >> color >> condition) {
					if (item_make == make && item_model == model && item_color == color && item_year == year && item_condition == condition) {
						cout << setw(20) << "Year" << setw(20) << "Color" << setw(20) << "Make" << setw(20) << "Model" << setw(20) << "Stock" << endl;
						cout << setw(20) << year << setw(20) << color << setw(20) << make << setw(20) << model << setw(20) << stock << endl;
						cout << "Would you like to have this car shipped to a dealership near you?" << endl;
						cin >> ship;
						if (ship == "Yes" || ship == "Y" || ship == "yes" || ship == "y") {
							cout << "Thank you for ordering! You're vehicle should arrive within 2 weeks to a dealership near you!" << endl;
						}
						else if (ship == "No" || ship == "N" || ship == "no" || ship == "n") {
							cout << "Exiting..." << endl;
						}
					}
					else {
						cout << "Car unavailable." << endl;
					}
				}
			}

			manufacturingInventoryIn.close();

		}
		else if (choice == 1) {
			manufacturingInventoryIn.open(MAN_CAR_FILE);
			item_condition = "Used";

			// get desired car from customer (year, make, model, color)
			cout << endl << "Enter desired year: ";
			cin >> item_year;
			cout << endl << "Enter desired make: ";
			cin >> item_make;
			cout << endl << "Enter desired model: ";
			cin >> item_model;
			cout << endl << "Enter desired color: ";
			cin >> item_color;

			if (manufacturingInventoryIn.is_open()) {
				while (manufacturingInventoryIn >> date >> stock >> year >> make >> model >> color >> condition) {
					if (item_make == make && item_model == model && item_color == color && item_year == year && item_condition == condition) {
						cout << setw(20) << "Year" << setw(20) << "Color" << setw(20) << "Make" << setw(20) << "Model" << setw(20) << "Stock" << endl;
						cout << setw(20) << year << setw(20) << color << setw(20) << make << setw(20) << model << setw(20) << stock << endl;
						cout << "Would you like to have this car shipped to a dealership near you?" << endl;
						cin >> ship;
						if (ship == "Yes" || ship == "Y" || ship == "yes" || ship == "y") {
							cout << "Thank you for ordering! You're vehicle should arrive within 2 weeks to a dealership near you!" << endl;
						}
						else if (ship == "No" || ship == "N" || ship == "no" || ship == "n") {
							cout << "Exiting..." << endl;
						}
					}
					else {
						cout << "Car unavailable." << endl;
					}
				}
			}

			
			}

			manufacturingInventoryIn.close();

		}


	

void Company::manager() {
	int choice;
	string quarternum;
	string quarter;
	string c_earning; //customer earning
	string da_earning; //dealership / auto store earning

	cout << "What would you like to do? " << endl;
	cout << "[0] Display Profits" << endl;
	cout << "[1] Check Cars and Parts Prices" << endl;
	cout << "[2] Exit" << endl;
	cin >> choice;
	cout << endl;

	if (choice == 0) {
		profitIn.open(PROFIT_FILE);
		cout << "Enter quarter for earnings (ex Quarter 1): ";
		cin >> quarternum;
		
		
		if (profitIn.is_open()) {
			while (profitIn >> quarter >> c_earning >> da_earning) {
				if (quarter == quarternum) {
					cout << setw(20) << "Quarter" << setw(20) << "Customer Sales" << setw(30) << "Dealership/AutoStore Earning" << endl;
					cout << setw(20) << quarter << setw(7) << c_earning << setw(23) << da_earning << endl;
				}
			}
		}
		else {
			cout << "Error opening file" << endl;
		}
		profitIn.close();


	} else if (choice == 1) {
		string year;
		string make;
		string model;
		string color;
		string stock;
		string date;
		string condition;
		string price;
		string part;

		manufacturingInventoryIn.open(MAN_CAR_FILE);
		
		cout << endl << "CARS" << endl;
		if (manufacturingInventoryIn.is_open()) {
			while (manufacturingInventoryIn >> date >> stock >> year >> make >> model >> color >> condition >> price) {
				cout << setw(20) << "Last Updated" << setw(20) << "Stock" << setw(20) << "Year" << setw(20) << "Make" << setw(20) << "Model" << setw(20) << "Color" << setw(20) << "Condition" << setw(20) << "Price" << endl;
				cout << setw(20) << date << setw(20) << stock << setw(20) << year << setw(20) << make << setw(20) << model << setw(20) << color << setw(20) << condition << setw(20) << price << endl << endl;
			}
		}
		manufacturingInventoryIn.close();
		
		cout << endl << "PARTS" << endl;
		manufacturingInventoryIn.open(MAN_PART_FILE);
		if (manufacturingInventoryIn.is_open()) {
			cout << setw(20) << "Last Updated" << setw(20) << "Stock" << setw(20) << "Part" << setw(20) << "Price" << endl;
			while (manufacturingInventoryIn >> date >> stock >> part >> price) {
				cout << setw(20) << date << setw(20) << stock << setw(20) << part << setw(20) << price << endl;
			}
		}

		manufacturingInventoryIn.close();
	}
}