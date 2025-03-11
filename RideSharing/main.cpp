#include <iostream>
#include <vector>
using namespace std;

// Ride class
class Ride {
public:
    int rideId;
    string riderName;
    string pickup;
    string destination;
    bool isCompleted;
    string driverName;

    Ride(int id, string rider, string pickupLoc, string dest)
        : rideId(id), riderName(rider), pickup(pickupLoc), destination(dest), isCompleted(false), driverName("") {}

    void completeRide() {
        isCompleted = true;
    }

    void displayRide() const {
        cout << "Ride ID: " << rideId
             << " | Rider: " << riderName
             << " | Pickup: " << pickup
             << " | Destination: " << destination
             << " | Status: " << (isCompleted ? "Completed" : "Pending")
             << " | Driver: " << (driverName.empty() ? "None" : driverName)
             << endl;
    }
};

// User class
class User {
public:
    int userId;
    string name;
    string role; // "Rider" or "Driver"

    User(int id, string userName, string userRole) {
        userId = id;
        name = userName;
        role = userRole;
    }

    void displayUser() const {
        cout << "User ID: " << userId << " | Name: " << name << " | Role: " << role << endl;
    }
};

// Ride-Sharing Manager
class RideManager {
private:
    vector<User> users;
    vector<Ride> rides;
    int nextUserId = 1;
    int nextRideId = 1;

public:
    void registerUser(string name, string role) {
        if (role != "Rider" && role != "Driver") {
            cout << "Invalid role! Choose 'Rider' or 'Driver'.\n";
            return;
        }
        users.push_back(User(nextUserId++, name, role));
        cout << name << " registered successfully as a " << role << "!\n";
    }

    void requestRide(int userId, string pickup, string destination) {
        User* rider = findUser(userId, "Rider");
        if (!rider) {
            cout << "Rider not found!\n";
            return;
        }
        rides.push_back(Ride(nextRideId++, rider->name, pickup, destination));
        cout << "Ride requested successfully!\n";
    }

    void acceptRide(int userId, int rideId) {
        User* driver = findUser(userId, "Driver");
        if (!driver) {
            cout << "Driver not found!\n";
            return;
        }

        Ride* ride = findRide(rideId, false);
        if (!ride) {
            cout << "Ride not found or already accepted!\n";
            return;
        }

        ride->driverName = driver->name;
        cout << "Ride ID " << rideId << " accepted by " << driver->name << "!\n";
    }

    void completeRide(int rideId) {
        Ride* ride = findRide(rideId, true);
        if (!ride) {
            cout << "Ride not found or not yet accepted!\n";
            return;
        }

        ride->completeRide();
        cout << "Ride ID " << rideId << " completed successfully!\n";
    }

    void showRides(bool completed = false) {
        if (rides.empty()) {
            cout << "No rides available!\n";
            return;
        }
        for (const auto& ride : rides) {
            if (ride.isCompleted == completed) {
                ride.displayRide();
            }
        }
    }

    void showUsers() {
        if (users.empty()) {
            cout << "No users registered!\n";
            return;
        }
        for (const auto& user : users) {
            user.displayUser();
        }
    }

private:
    User* findUser(int userId, string role) {
        for (auto& user : users) {
            if (user.userId == userId && user.role == role)
                return &user;
        }
        return nullptr;
    }

    Ride* findRide(int rideId, bool requireAccepted) {
        for (auto& ride : rides) {
            if (ride.rideId == rideId && (requireAccepted ? !ride.driverName.empty() : ride.driverName.empty()))
                return &ride;
        }
        return nullptr;
    }
};

// Main Function
int main() {
    RideManager manager;
    int choice;

    while (true) {
        cout << "\nRide-Sharing System\n";
        cout << "1. Register User\n";
        cout << "2. Request a Ride\n";
        cout << "3. Accept a Ride\n";
        cout << "4. Complete a Ride\n";
        cout << "5. Show Pending Rides\n";
        cout << "6. Show Completed Rides\n";
        cout << "7. Show Users\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, role;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Role (Rider/Driver): ";
            cin >> role;
            manager.registerUser(name, role);
        } 
        else if (choice == 2) {
            int userId;
            string pickup, destination;
            cout << "Enter Rider User ID: ";
            cin >> userId;
            cout << "Enter Pickup Location: ";
            cin.ignore();
            getline(cin, pickup);
            cout << "Enter Destination: ";
            getline(cin, destination);
            manager.requestRide(userId, pickup, destination);
        } 
        else if (choice == 3) {
            int userId, rideId;
            cout << "Enter Driver User ID: ";
            cin >> userId;
            cout << "Enter Ride ID to Accept: ";
            cin >> rideId;
            manager.acceptRide(userId, rideId);
        } 
        else if (choice == 4) {
            int rideId;
            cout << "Enter Ride ID to Complete: ";
            cin >> rideId;
            manager.completeRide(rideId);
        } 
        else if (choice == 5) {
            manager.showRides(false);
        } 
        else if (choice == 6) {
            manager.showRides(true);
        } 
        else if (choice == 7) {
            manager.showUsers();
        } 
        else if (choice == 8) {
            cout << "Exiting Ride-Sharing System...\n";
            break;
        } 
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
