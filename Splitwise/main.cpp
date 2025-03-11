#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// User class representing a participant in expenses
class User {
public:
    string name;
    map<string, double> balances; // Amount user owes to others

    User() = default; // Default constructor
    User(const string& name) : name(name) {}
};

// Splitwise System
class Splitwise {
private:
    map<string, User> users; // User storage

public:
    void addUser(const string& name) {
        if (users.find(name) == users.end()) {
            users[name] = User(name);
        } else {
            cout << "User already exists!\n";
        }
    }

    void addExpense(const string& paidBy, double amount, const vector<string>& participants, const vector<double>& shares) {
        if (users.find(paidBy) == users.end()) {
            cout << "Payer not found!\n";
            return;
        }
        double totalShare = 0;
        for (double share : shares) totalShare += share;
        if (totalShare != amount) {
            cout << "Shares do not sum up to the total amount!\n";
            return;
        }
        
        for (size_t i = 0; i < participants.size(); i++) {
            const string& participant = participants[i];
            if (users.find(participant) == users.end()) {
                cout << "User " << participant << " not found!\n";
                return;
            }
            if (participant != paidBy) {
                users[participant].balances[paidBy] += shares[i];
                users[paidBy].balances[participant] -= shares[i];
            }
        }
    }

    void showBalances() const {
        for (const auto& user : users) {
            for (const auto& balance : user.second.balances) {
                if (balance.second > 0) {
                    cout << user.first << " owes " << balance.first << " Rs. " << balance.second << "\n";
                }
            }
        }
    }
};

// Interactive menu


int main() {
    
    Splitwise splitwise;
    int choice;
    string name, paidBy, participant;
    double amount;
    int numParticipants;
    vector<string> participants;
    vector<double> shares;

    while (true) {
        cout << "\nChoose an operation:\n";
        cout << "1. Add User\n2. Add Expense\n3. Show Balances\n4. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter user name: "; cin >> name;
                splitwise.addUser(name);
                break;
            case 2:
                cout << "Enter payer name: "; cin >> paidBy;
                cout << "Enter amount: "; cin >> amount;
                cout << "Enter number of participants: "; cin >> numParticipants;
                participants.clear(); shares.clear();
                for (int i = 0; i < numParticipants; i++) {
                    cout << "Enter participant name: "; cin >> participant;
                    participants.push_back(participant);
                }
                for (int i = 0; i < numParticipants; i++) {
                    double share;
                    cout << "Enter amount for " << participants[i] << ": "; cin >> share;
                    shares.push_back(share);
                }
                splitwise.addExpense(paidBy, amount, participants, shares);
                break;
            case 3:
                splitwise.showBalances();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
