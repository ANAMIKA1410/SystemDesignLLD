#include <iostream>
#include <vector>
using namespace std;

// Wallet class
class Wallet {
public:
    int userId;
    string name;
    double balance;

    Wallet(int id, string userName, double initialBalance) {
        userId = id;
        name = userName;
        balance = initialBalance;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited ₹" << amount << " successfully!\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        cout << "Withdrawn ₹" << amount << " successfully!\n";
        return true;
    }

    void displayBalance() const {
        cout << "User: " << name << " | Balance: ₹" << balance << "\n";
    }
};

// Digital Wallet Manager
class WalletManager {
private:
    vector<Wallet> wallets;
    int nextUserId = 1;

public:
    void createWallet(string name, double initialBalance) {
        wallets.push_back(Wallet(nextUserId++, name, initialBalance));
        cout << "Wallet created successfully!\n";
    }

    Wallet* findWallet(int userId) {
        for (auto &wallet : wallets) {
            if (wallet.userId == userId)
                return &wallet;
        }
        return nullptr;
    }

    void depositMoney(int userId, double amount) {
        Wallet* wallet = findWallet(userId);
        if (wallet) {
            wallet->deposit(amount);
        } else {
            cout << "Wallet not found!\n";
        }
    }

    void withdrawMoney(int userId, double amount) {
        Wallet* wallet = findWallet(userId);
        if (wallet) {
            wallet->withdraw(amount);
        } else {
            cout << "Wallet not found!\n";
        }
    }

    void transferMoney(int senderId, int receiverId, double amount) {
        Wallet* sender = findWallet(senderId);
        Wallet* receiver = findWallet(receiverId);

        if (!sender || !receiver) {
            cout << "Invalid sender or receiver ID!\n";
            return;
        }
        if (sender->withdraw(amount)) {
            receiver->deposit(amount);
            cout << "Transfer of ₹" << amount << " from User " << sender->name 
                 << " to " << receiver->name << " was successful!\n";
        }
    }

    void showWallets() {
        if (wallets.empty()) {
            cout << "No wallets available!\n";
            return;
        }
        for (const auto &wallet : wallets) {
            wallet.displayBalance();
        }
    }
};

// Main Function
int main() {
    WalletManager manager;
    int choice;

    while (true) {
        cout << "\nDigital Wallet System\n";
        cout << "1. Create Wallet\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Show Wallets\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            double initialBalance;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ₹";
            cin >> initialBalance;
            manager.createWallet(name, initialBalance);
        } 
        else if (choice == 2) {
            int userId;
            double amount;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Amount to Deposit: ₹";
            cin >> amount;
            manager.depositMoney(userId, amount);
        } 
        else if (choice == 3) {
            int userId;
            double amount;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Amount to Withdraw: ₹";
            cin >> amount;
            manager.withdrawMoney(userId, amount);
        } 
        else if (choice == 4) {
            int senderId, receiverId;
            double amount;
            cout << "Enter Sender User ID: ";
            cin >> senderId;
            cout << "Enter Receiver User ID: ";
            cin >> receiverId;
            cout << "Enter Amount to Transfer: ₹";
            cin >> amount;
            manager.transferMoney(senderId, receiverId, amount);
        } 
        else if (choice == 5) {
            manager.showWallets();
        } 
        else if (choice == 6) {
            cout << "Exiting Digital Wallet System...\n";
            break;
        } 
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
