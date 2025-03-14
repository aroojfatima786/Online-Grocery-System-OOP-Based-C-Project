  #include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Login {
protected:
    string username;
    string password;
    string address;
    string creditCardNumber;
    string cvc;
    string exp;

public:
    void registerUser();
    bool isUsernameTaken(const string& username);
};

void Login::registerUser() {
    cout << endl << "\n\n\n\n\n\n\n\n\t\t\t Enter Username: ";
    cin >> username;

    while (isUsernameTaken(username)) {
        cout << endl << "\t\t\t Username already taken. Choose another: ";
        cin >> username;
    }

    cout << endl << "\t\t\t Enter Password: ";
    cin >> password;
    cout << endl << "\t\t\t Enter Address: ";
    cin >> address;
    cout << endl << "\t\t\t Enter Credit Card Number: ";
    cin >> creditCardNumber;
    cout << endl << "\t\t\t Enter CVC: ";
    cin >> cvc;
    cout << endl << "\t\t\t Enter Expiry: ";
    cin >> exp;

    ofstream file("accounts.txt", ios::app);
    file << username << " " << password << " " << address << " " << creditCardNumber << " " << cvc << " " << exp << endl;
    file.close();
    cout << "\t\t\t Registration Successful!!!";
}

bool Login::isUsernameTaken(const string& username) {
    ifstream file("accounts.txt");
    string existingUsername;

    while (file >> existingUsername) {
        if (existingUsername == username) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

class ForgotPassword : public Login {
public:
    void forgotPassword();
};

void ForgotPassword::forgotPassword() {
    string inputUsername;
    cout << endl << "\n\n\n\n\n\n\n\n\t\t\t Enter Username: ";
    cin >> inputUsername;

    if (isUsernameTaken(inputUsername)) {
        string newPassword;
        cout << endl << "\t\t\t Enter New Password: ";
        cin >> newPassword;

        // Update the password in the file
        ifstream inFile("accounts.txt");
        ofstream outFile("temp.txt");

        string fileUsername, filePassword, fileAddress, fileCreditCardNumber, fileCVC, fileExp;

        while (inFile >> fileUsername >> filePassword >> fileAddress >> fileCreditCardNumber >> fileCVC >> fileExp) {
            if (fileUsername == inputUsername) {
                filePassword = newPassword;
            }
            outFile << fileUsername << " " << filePassword << " " << fileAddress << " " << fileCreditCardNumber << " " << fileCVC << " " << fileExp << endl;
        }

        inFile.close();
        outFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        cout << "\t\t\t Password updated successfully!";
    } else {
        cout << "\t\t\t Username does not exist!";
    }
}


class CartItem {
public:
    string name;
    int quantity;
    int ratePerItem;
};

class Items : public Login {
private:
    vector<CartItem> selectedItems;
    int grandTotal;

public:
    void display();
    void generateReceipt();
    void addCartItem(const string& name, int quantity, int ratePerItem);
    void GeneralItems();
    void Electronics();
    void MainHouseholds();
};

void Items::display() {
   static bool registrationShown = false; 

    if (!registrationShown) {
        string chose;
        cout << endl << "\n\n\n\n\n\n\n\n\t\t\t Would you like to register before Shopping (y/n) : ";
        cin >> chose;

        if (chose == "Y" || chose == "y") {
            registerUser();
        } else {
            system("cls");
        }

        registrationShown = true; 
    } else {
        system("cls");
    }
    system("cls");
	
    cout<<endl<<"_____________________________________________________________________________"<<endl<<endl
	<<"                             Online Shooping System "<<
	endl<<"                            Made By *** The Code Squad ***"<<endl<<endl;
	cout<<"_____________________________________________________________________"<<endl<<endl;
	cout<<"                      ** ----- GENERAL CATEGORIES ----- **"<<endl<<endl<<endl<<endl;
	cout<<" Please Select one of the Following ."<<endl<<" Choose with serial number"<<endl;
	cout<<"________________________________________________________________________________"<<endl<<
		  endl<< " S.No  | Name Of Categories...                     |"<<endl<<
		  "---------------------------------------------------|"<<endl<<
		  endl<< "    1. |	General Items...                   |"<<endl<<
		  "---------------------------------------------------|"<<endl<<
		  endl<< "    2. |	Electronics...                     |"<<endl<<
		  "---------------------------------------------------|"<<endl<<
		  endl<< "    3. |	Main HouseHolds...                 |"<<endl<<
		  "---------------------------------------------------|"<<endl<<endl;

    int option;
    cout << "Select a category (1-5): ";
    cin >> option;
  
    switch (option) {
        case 1:
            GeneralItems();
            break;
        case 2:
            Electronics();
            break;
        case 3:
            MainHouseholds();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
    }
}

void Items::addCartItem(const string& name, int quantity, int ratePerItem) {
    CartItem item;
    item.name = name;
    item.quantity = quantity;
    item.ratePerItem = ratePerItem;

    selectedItems.push_back(item);
}

void Items::generateReceipt() {
	char address;
    system("cls");

    int op;

    cout << "\n\n\n\t\t\tHow would you like to Pay: " << endl << endl;
    cout << "\t\t\t1. Credit Card ... " << endl << endl;
    cout << "\t\t\t2. Cash On Delivery... " << endl << endl;
    cout << "\t\t\tChoose: ";
    cin >> op;

    switch (op) {
        case 1: {
            fstream file;
            cout << "\t\t\tEnter Username: ";
            cin >> username;
            file.open("accounts.txt");
            string existingusername;
            while (file >> existingusername) {
                if (existingusername == username) {
                    file >> creditCardNumber >> cvc >> exp;
                }
            }
            break;
        }
        case 2:
        	{
        		cout << "Enter Address : ";
        		cin >> address;
			}
		default:
		{
			cout << "Invalid Choice.";
		}
        
    }


    cout << setw(70) << "Receipt" << endl << endl;
    cout << left << setw(30) << "Item"
         << right << setw(10) << "Rate"
         << setw(10) << "Quantity"
         << setw(10) << "Total" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;

    grandTotal = 0;
    fstream purchaseditems("purchased.txt", ios::app);
    for (size_t i = 0; i < selectedItems.size(); i++) {
        const CartItem& item = selectedItems[i];
        int total = item.quantity * item.ratePerItem;
        grandTotal += total;

        cout << left << setw(30) << item.name
             << right << setw(10) << item.ratePerItem
             << setw(10) << item.quantity
             << setw(10) << total << endl;
             
         purchaseditems << item.name << " " << item.ratePerItem << " " << item.quantity << " " << total << endl;
    }

    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    cout << right << setw(50) << "Grand Total: RS/= " << grandTotal << endl;
    cout << "***************************************" << endl;
}


void Items::GeneralItems() {
	
	string choose;
	
    cout << " 1.  Gum Bottle...            RS/= 500" << endl;
    cout << " 2.  Punching Machine...      RS/= 1500" << endl;
    cout << " 3.  Sealing wax...           RS/= 1000" << endl;
    cout << " 4.  Tea set...               RS/= 2000" << endl;
    cout << " 5.  Cleaning powder vim..    RS/= 200" << endl;
    cout << endl;

    int option;
    cout << "Select an item (1-5): ";
    cin >> option;

    switch (option) {
        case 1: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Gum Bottle", quantity, 500);
            break;
        }
        case 2: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Punching Machine", quantity, 1500);
            break;
        }
        case 3: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Sealing wax", quantity, 1000);
            break;
        }
        case 4: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Tea set", quantity, 2000);
            break;
        }
        case 5: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Cleaning powder vim", quantity, 200);
            break;
        }
        default: {
            cout << "Invalid option. Please try again." << endl;
            break;}
              } 
          cout << "Would you like to buy something else (y/n): ";
cin >> choose;
if (choose == "Y" || choose == "y") {
    display();
}
else {
    generateReceipt();
}
}

void Items::Electronics() {
	
	string choose;
	
    cout << " 1.  FAN...             RS/= 5000" << endl;
    cout << " 2.  Mobile..           RS/= 15000" << endl;
    cout << " 3.  AC..               RS/= 50000" << endl;
    cout << " 4.  Fridge..           RS/= 40000" << endl;
    cout << " 5.  TV..               RS/= 30000" << endl;
    cout << endl;

    int option;
    cout << "Select an item (1-5): ";
    cin >> option;

    switch (option) {
        case 1: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("FAN", quantity, 5000);
            break;
        }
        case 2: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Mobile", quantity, 15000);
            break;
        }
        case 3: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("AC", quantity, 50000);
            break;
        }
        case 4: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Fridge", quantity, 40000);
            break;
        }
        case 5: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("TV", quantity, 30000);
            break;
        }
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
    }
    
    cout << "Would you like to buy something else (y/n): ";
    cin >> choose;
    if(choose == "Y" || choose == "y") {
    	display();
	}
	else {
		generateReceipt();
	} 
}

void Items::MainHouseholds() {
	
	string choose;
    cout << " 1.  BED...                   RS/= 5000" << endl;
    cout << " 2.  Chair...                 RS/= 15000" << endl;
    cout << " 3.  Couch...                 RS/= 50000" << endl;
    cout << " 4.  Table...                 RS/= 40000" << endl;
    cout << " 5.  Washing Machine...       RS/= 30000" << endl;
    cout << endl;

    int option;
    cout << "Select an item (1-5): ";
    cin >> option;

    switch (option) {
        case 1: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("BED", quantity, 5000);
            break;
        }
        case 2: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Chair", quantity, 15000);
            break;
        }
        case 3: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Couch", quantity, 50000);
            break;
        }
        case 4: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Table", quantity, 40000);
            break;
        }
        case 5: {
            int quantity;
            cout << "Enter the quantity: ";
            cin >> quantity;
            addCartItem("Washing Machine", quantity, 30000);
            break;
        }
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
    }
    
    cout << "Would you like to buy something else (y/n): ";
    cin >> choose;
    if(choose == "Y" || choose == "y") {
    	display();
	}
	else {
		generateReceipt();
	} 
}

int main() {
	
	system("color 0b");
	ForgotPassword forgotPassword;
    forgotPassword.forgotPassword();
    Items shoppingCart;
    shoppingCart.display();

    return 0;
}
/*  It's a simple command-line application for an online shopping system, and it may not directly connect to the internet.
 To connect our application to the internet, we would typically need to integrate networking functionality into the relevant
parts of our code, such as when communicating with a server or retrieving data from the internet.*/
/* Also for credit card payments we would need to connect to relevent credit card provider.*/

