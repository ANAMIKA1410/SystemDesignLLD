#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Vehicle {
public:
    string id;
    string type;
    Vehicle(string id, string type) : id(id), type(type) {}
};

class TrafficSignal {
public:
    string location;
    string state; // Red, Green, Yellow
    TrafficSignal() {}
    TrafficSignal(string location, string state) : location(location), state(state) {}
    void changeState(string newState) { state = newState; }
};

class Road {
public:
    string name;
    vector<Vehicle> vehicles;
    Road() {}
    Road(string name) : name(name) {}
    void addVehicle(Vehicle v) { vehicles.push_back(v); }
};

class TrafficManagement {
private:
    map<string, TrafficSignal> signals;
    map<string, Road> roads;
    vector<string> accidentLocations;
public:
    void addSignal(string location, string state) {
        signals[location] = TrafficSignal(location, state);
    }
    void changeSignal(string location, string state) {
        if (signals.find(location) != signals.end())
            signals[location].changeState(state);
    }
    void addRoad(string name) {
        roads[name] = Road(name);
    }
    void addVehicleToRoad(string roadName, string id, string type) {
        if (roads.find(roadName) != roads.end())
            roads[roadName].addVehicle(Vehicle(id, type));
    }
    void reportAccident(string location) {
        accidentLocations.push_back(location);
    }
    void showTrafficStatus() {
        cout << "Traffic Signals:\n";
        for (auto &s : signals)
            cout << "Location: " << s.first << " | State: " << s.second.state << "\n";
        cout << "\nRoads:\n";
        for (auto &r : roads) {
            cout << "Road: " << r.first << " | Vehicles: ";
            for (auto &v : r.second.vehicles)
                cout << v.id << "(" << v.type << ") ";
            cout << "\n";
        }
        cout << "\nAccidents Reported:\n";
        for (auto &loc : accidentLocations)
            cout << "Accident at " << loc << "\n";
    }
};

int main() {
    TrafficManagement system;
    int choice;
    string location, state, roadName, id, type;

    while (true) {
        cout << "\nBangalore Traffic Management System\n";
        cout << "1. Add Traffic Signal\n2. Change Signal State\n3. Add Road\n4. Add Vehicle to Road\n5. Report Accident\n6. Show Traffic Status\n7. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter signal location: ";
                cin >> location;
                cout << "Enter initial state (Red/Green/Yellow): ";
                cin >> state;
                system.addSignal(location, state);
                break;
            case 2:
                cout << "Enter signal location: ";
                cin >> location;
                cout << "Enter new state (Red/Green/Yellow): ";
                cin >> state;
                system.changeSignal(location, state);
                break;
            case 3:
                cout << "Enter road name: ";
                cin >> roadName;
                system.addRoad(roadName);
                break;
            case 4:
                cout << "Enter road name: ";
                cin >> roadName;
                cout << "Enter vehicle ID: ";
                cin >> id;
                cout << "Enter vehicle type: ";
                cin >> type;
                system.addVehicleToRoad(roadName, id, type);
                break;
            case 5:
                cout << "Enter accident location: ";
                cin >> location;
                system.reportAccident(location);
                break;
            case 6:
                system.showTrafficStatus();
                break;
            case 7:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}
