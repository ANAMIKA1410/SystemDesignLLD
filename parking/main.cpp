#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>

using namespace std;

// Enum for vehicle types
enum class VehicleType { MOTORCYCLE, CAR, TRUCK };

// Enum for parking spot types
enum class SpotType { COMPACT, LARGE, MOTORCYCLE };

// Vehicle class
class Vehicle {
public:
    string licensePlate;
    VehicleType type;
    time_t entryTime;

    Vehicle(string plate, VehicleType vType) : licensePlate(plate), type(vType) {
        entryTime = time(0);
    }
};

// Parking Spot class
class ParkingSpot {
public:
    int id;
    SpotType type;
    bool isOccupied;
    Vehicle* parkedVehicle;

    ParkingSpot(int spotId, SpotType sType) : id(spotId), type(sType), isOccupied(false), parkedVehicle(nullptr) {}

    bool parkVehicle(Vehicle* vehicle) {
        if (!isOccupied) {
            parkedVehicle = vehicle;
            isOccupied = true;
            return true;
        }
        return false;
    }

    void removeVehicle() {
        isOccupied = false;
        parkedVehicle = nullptr;
    }
};

// Parking Lot class
class ParkingLot {
private:
    vector<ParkingSpot> spots;
    unordered_map<string, ParkingSpot*> parkedVehicles;
    int compactCount, largeCount, motorcycleCount;

public:
    ParkingLot(int compact, int large, int motorcycle) {
        compactCount = compact;
        largeCount = large;
        motorcycleCount = motorcycle;
        int id = 1;

        for (int i = 0; i < compact; i++)
            spots.push_back(ParkingSpot(id++, SpotType::COMPACT));
        for (int i = 0; i < large; i++)
            spots.push_back(ParkingSpot(id++, SpotType::LARGE));
        for (int i = 0; i < motorcycle; i++)
            spots.push_back(ParkingSpot(id++, SpotType::MOTORCYCLE));
    }

    bool parkVehicle(Vehicle* vehicle) {
        for (auto& spot : spots) {
            if (!spot.isOccupied && isSpotSuitable(spot.type, vehicle->type)) {
                spot.parkVehicle(vehicle);
                parkedVehicles[vehicle->licensePlate] = &spot;
                cout << "Vehicle " << vehicle->licensePlate << " parked at Spot " << spot.id << endl;
                return true;
            }
        }
        cout << "No parking spot available for " << vehicle->licensePlate << endl;
        return false;
    }

    void removeVehicle(string licensePlate) {
        if (parkedVehicles.find(licensePlate) != parkedVehicles.end()) {
            ParkingSpot* spot = parkedVehicles[licensePlate];
            double charge = calculateCharge(spot->parkedVehicle);
            cout << "Vehicle " << licensePlate << " removed. Charge: $" << charge << endl;
            spot->removeVehicle();
            parkedVehicles.erase(licensePlate);
        } else {
            cout << "Vehicle " << licensePlate << " not found." << endl;
        }
    }

    void displayAvailableSpots() {
        int compact = 0, large = 0, motorcycle = 0;
        for (auto& spot : spots) {
            if (!spot.isOccupied) {
                if (spot.type == SpotType::COMPACT) compact++;
                else if (spot.type == SpotType::LARGE) large++;
                else if (spot.type == SpotType::MOTORCYCLE) motorcycle++;
            }
        }
        cout << "Available Spots: Compact: " << compact << ", Large: " << large << ", Motorcycle: " << motorcycle << endl;
    }

private:
    bool isSpotSuitable(SpotType spot, VehicleType vehicle) {
        if (vehicle == VehicleType::MOTORCYCLE) return true;
        if (vehicle == VehicleType::CAR && (spot == SpotType::COMPACT || spot == SpotType::LARGE)) return true;
        if (vehicle == VehicleType::TRUCK && spot == SpotType::LARGE) return true;
        return false;
    }

    double calculateCharge(Vehicle* vehicle) {
        time_t exitTime = time(0);
        double hours = difftime(exitTime, vehicle->entryTime) / 3600;
        double rate = (vehicle->type == VehicleType::MOTORCYCLE) ? 2.0 : (vehicle->type == VehicleType::CAR) ? 5.0 : 10.0;
        return hours * rate;
    }
};

int main() {
    ParkingLot lot(5, 3, 2);
    int choice;

    while (true) {
        cout << "\nParking Lot System:\n1. Park Vehicle\n2. Remove Vehicle\n3. Display Available Spots\n4. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string plate;
            int type;
            cout << "Enter License Plate: ";
            cin >> plate;
            cout << "Enter Vehicle Type (0: Motorcycle, 1: Car, 2: Truck): ";
            cin >> type;
            Vehicle* vehicle = new Vehicle(plate, static_cast<VehicleType>(type));
            lot.parkVehicle(vehicle);
        } else if (choice == 2) {
            string plate;
            cout << "Enter License Plate: ";
            cin >> plate;
            lot.removeVehicle(plate);
        } else if (choice == 3) {
            lot.displayAvailableSpots();
        } else if (choice == 4) {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}
