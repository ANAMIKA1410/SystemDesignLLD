#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Class representing a single poll option
class Option {
public:
    string description;
    int votes;

    Option(const string& desc) : description(desc), votes(0) {}
};

// Class representing a poll
class Poll {
private:
    string question;
    vector<Option> options;
    unordered_map<string, bool> voters; // Tracks if a user has voted

public:
    Poll(const string& q, const vector<string>& opts) : question(q) {
        for (const auto& opt : opts) {
            options.emplace_back(opt);
        }
    }

    // Display the poll question and options
    void display() const {
        cout << "Poll: " << question << "\n";
        for (size_t i = 0; i < options.size(); ++i) {
            cout << i + 1 << ". " << options[i].description << "\n";
        }
    }

    // Cast a vote for a given option by a user
    bool castVote(const string& user, int optionNumber) {
        if (voters.find(user) != voters.end()) {
            cout << "User '" << user << "' has already voted.\n";
            return false;
        }
        if (optionNumber < 1 || optionNumber > options.size()) {
            cout << "Invalid option number.\n";
            return false;
        }
        options[optionNumber - 1].votes++;
        voters[user] = true;
        cout << "Vote cast successfully.\n";
        return true;
    }

    // Display the current results of the poll
    void displayResults() const {
        cout << "Poll Results for: " << question << "\n";
        for (const auto& opt : options) {
            cout << opt.description << ": " << opt.votes << " votes\n";
        }
    }
};

// Function to create a new poll
Poll createPoll() {
    string question;
    int numOptions;
    vector<string> options;

    cout << "Enter the poll question: ";
    cin.ignore(); // Clear input buffer
    getline(cin, question);

    cout << "Enter the number of options: ";
    cin >> numOptions;
    cin.ignore(); // Clear input buffer

    for (int i = 0; i < numOptions; ++i) {
        string option;
        cout << "Enter option " << i + 1 << ": ";
        getline(cin, option);
        options.push_back(option);
    }

    return Poll(question, options);
}

// Main function to run the polling system
int main() {
    Poll poll = createPoll();
    int choice;
    string username;

    while (true) {
        cout << "\n1. Display Poll\n2. Cast Vote\n3. Display Results\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                poll.display();
                break;
            case 2:
                cout << "Enter your username: ";
                cin >> username;
                int optionNumber;
                cout << "Enter option number to vote for: ";
                cin >> optionNumber;
                poll.castVote(username, optionNumber);
                break;
            case 3:
                poll.displayResults();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
