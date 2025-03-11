#include <iostream>
#include <map>
#include <string>

using namespace std;

// Item class to represent a vending machine product
class Item {
public:
    string name;
    double price;
    int quantity;

    Item() {}
    Item(string name, double price, int quantity) : name(name), price(price), quantity(quantity) {}
};

// Vending Machine class
class VendingMachine {
private:
    map<int, Item> inventory;
    double balance;

public:
    VendingMachine() : balance(0.0) {}
    
    void addItem(int code, string name, double price, int quantity) {
        inventory[code] = Item(name, price, quantity);
    }
    
    void showItems() {
        cout << "\nAvailable Items:" << endl;
        for (auto &item : inventory) {
            cout << "Code: " << item.first << " | " << item.second.name << " | $" << item.second.price << " | Stock: " << item.second.quantity << endl;
        }
    }
    
    void insertMoney(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Current balance: $" << balance << endl;
        } else {
            cout << "Invalid amount. Please enter a positive value." << endl;
        }
    }
    
    void buyItem(int code) {
        if (inventory.find(code) == inventory.end()) {
            cout << "Invalid item code." << endl;
            return;
        }
        
        Item &item = inventory[code];
        if (item.quantity == 0) {
            cout << "Item out of stock." << endl;
            return;
        }
        
        if (balance >= item.price) {
            balance -= item.price;
            item.quantity--;
            cout << "Purchased " << item.name << " for $" << item.price << endl;
            cout << "Remaining balance: $" << balance << endl;
        } else {
            cout << "Insufficient balance. Please insert more money." << endl;
        }
    }
    
    void refund() {
        cout << "Refunded: $" << balance << endl;
        balance = 0.0;
    }
};

// Interactive menu function

int main() {
    
    VendingMachine machine;
    machine.addItem(1, "Soda", 1.5, 10);
    machine.addItem(2, "Chips", 1.0, 5);
    machine.addItem(3, "Candy", 0.75, 8);
    
    int choice;
    double amount;
    int code;
    
    while (true) {
        cout << "\n1. Show Items\n2. Insert Money\n3. Buy Item\n4. Refund\n5. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                machine.showItems();
                break;
            case 2:
                cout << "Enter amount: ";
                cin >> amount;
                machine.insertMoney(amount);
                break;
            case 3:
                cout << "Enter item code: ";
                cin >> code;
                machine.buyItem(code);
                break;
            case 4:
                machine.refund();
                break;
            case 5:
                cout << "Thank you! Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice, try again." << endl;
        }
    }

    return 0;
}
