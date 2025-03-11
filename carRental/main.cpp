#include <iostream>
#include <map>
#include <string>

using namespace std;

// Car class to represent a car entity
class Car {
public:
    string id;
    string model;
    string brand;
    double pricePerDay;
    bool isAvailable;

    Car() {}
    Car(string id, string model, string brand, double pricePerDay) 
        : id(id), model(model), brand(brand), pricePerDay(pricePerDay), isAvailable(true) {}
};

// Car Rental System class
class CarRentalSystem {
private:
    map<string, Car> cars; // Car ID -> Car object

public:
    void addCar(string id, string model, string brand, double pricePerDay) {
        cars.emplace(id, Car(id, model, brand, pricePerDay));
        cout << "Car added successfully!\n";
    }
    
    void rentCar(string id) {
        if (cars.find(id) != cars.end()) {
            if (cars[id].isAvailable) {
                cars[id].isAvailable = false;
                cout << "Car " << id << " rented successfully!\n";
            } else {
                cout << "Car is already rented.\n";
            }
        } else {
            cout << "Car not found.\n";
        }
    }
    
    void returnCar(string id) {
        if (cars.find(id) != cars.end()) {
            if (!cars[id].isAvailable) {
                cars[id].isAvailable = true;
                cout << "Car " << id << " returned successfully!\n";
            } else {
                cout << "Car was not rented.\n";
            }
        } else {
            cout << "Car not found.\n";
        }
    }
    
    void showAvailableCars() {
        cout << "Available Cars:\n";
        for (auto &pair : cars) {
            if (pair.second.isAvailable) {
                cout << "ID: " << pair.second.id << ", Model: " << pair.second.model 
                     << ", Brand: " << pair.second.brand << ", Price/Day: $" 
                     << pair.second.pricePerDay << "\n";
            }
        }
    }
};

// Interactive menu
int main() {
   
    CarRentalSystem rentalSystem;
    int choice;
    string id, model, brand;
    double pricePerDay;
    
    while (true) {
        cout << "\nChoose an operation:\n";
        cout << "1. Add Car\n2. Rent Car\n3. Return Car\n4. Show Available Cars\n5. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter Car ID: "; cin >> id;
                cout << "Enter Model: "; cin >> model;
                cout << "Enter Brand: "; cin >> brand;
                cout << "Enter Price Per Day: "; cin >> pricePerDay;
                rentalSystem.addCar(id, model, brand, pricePerDay);
                break;
            case 2:
                cout << "Enter Car ID to rent: "; cin >> id;
                rentalSystem.rentCar(id);
                break;
            case 3:
                cout << "Enter Car ID to return: "; cin >> id;
                rentalSystem.returnCar(id);
                break;
            case 4:
                rentalSystem.showAvailableCars();
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
