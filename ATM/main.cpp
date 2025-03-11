#include <iostream>
#include <map>
#include <string>

using namespace std;

// User class representing a bank account holder
class User {
public:
    std::string name;
    std::string pin;
    double balance;

    User() : name(""), pin(""), balance(0.0) {} // Default constructor
    User(std::string name, std::string pin) : name(name), pin(pin), balance(0.0) {}
};


// ATM System
class ATM {
private:
    map<string, User> users; // User storage with account number as key

public:
    void addUser(string accountNumber, string name, string pin) {
        if (users.find(accountNumber) == users.end()) {
            users[accountNumber] = User(name, pin);
            cout << "User " << name << " added successfully!\n";
        } else {
            cout << "Account number already exists!\n";
        }
    }

    bool authenticateUser(string accountNumber, string pin) {
        if (users.find(accountNumber) != users.end() && users[accountNumber].pin == pin) {
            return true;
        }
        return false;
    }

    void deposit(string accountNumber, double amount) {
        if (amount > 0) {
            users[accountNumber].balance += amount;
            cout << "Deposited Rs. " << amount << " successfully!\n";
        } else {
            cout << "Invalid deposit amount!\n";
        }
    }

    void withdraw(string accountNumber, double amount) {
        if (amount > 0 && users[accountNumber].balance >= amount) {
            users[accountNumber].balance -= amount;
            cout << "Withdrew Rs. " << amount << " successfully!\n";
        } else {
            cout << "Invalid withdrawal amount or insufficient balance!\n";
        }
    }

    void checkBalance(string accountNumber) {
        cout << "Current balance: Rs. " << users[accountNumber].balance << "\n";
    }
};

// Interactive menu
void interactiveMenu() {
    ATM atm;
    int choice;
    string accountNumber, name, pin;
    double amount;

    while (true) {
        cout << "\nChoose an operation:\n";
        cout << "1. Create New User\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account number: "; cin >> accountNumber;
                cout << "Enter user name: "; cin >> name;
                cout << "Enter PIN: "; cin >> pin;
                atm.addUser(accountNumber, name, pin);
                break;
            case 2:
                cout << "Enter account number: "; cin >> accountNumber;
                cout << "Enter PIN: "; cin >> pin;
                if (atm.authenticateUser(accountNumber, pin)) {
                    cout << "Enter amount to deposit: "; cin >> amount;
                    atm.deposit(accountNumber, amount);
                } else {
                    cout << "Authentication failed!\n";
                }
                break;
            case 3:
                cout << "Enter account number: "; cin >> accountNumber;
                cout << "Enter PIN: "; cin >> pin;
                if (atm.authenticateUser(accountNumber, pin)) {
                    cout << "Enter amount to withdraw: "; cin >> amount;
                    atm.withdraw(accountNumber, amount);
                } else {
                    cout << "Authentication failed!\n";
                }
                break;
            case 4:
                cout << "Enter account number: "; cin >> accountNumber;
                cout << "Enter PIN: "; cin >> pin;
                if (atm.authenticateUser(accountNumber, pin)) {
                    atm.checkBalance(accountNumber);
                } else {
                    cout << "Authentication failed!\n";
                }
                break;
            case 5:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}

int main() {
    interactiveMenu();
    return 0;
}
