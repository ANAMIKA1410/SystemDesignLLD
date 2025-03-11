#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// MenuItem class to represent an individual food item
class MenuItem {
public:
    string name;
    double price;

    MenuItem(string n, double p) : name(n), price(p) {}
};

// Restaurant class to store menu and orders
class Restaurant {
public:
    string name;
    vector<MenuItem> menu;

    // Default constructor
    Restaurant() {}

    // Constructor with name
    Restaurant(string n) : name(n) {}

    // Add a menu item
    void addMenuItem(string itemName, double price) {
        menu.emplace_back(itemName, price);
        cout << "✅ " << itemName << " added to " << name << "'s menu!\n";
    }

    // Display menu
    void displayMenu() {
        cout << "📜 Menu for " << name << ":\n";
        if (menu.empty()) {
            cout << "❌ No items available!\n";
        } else {
            for (const auto& item : menu) {
                cout << "🍽️ " << item.name << " - ₹" << item.price << endl;
            }
        }
    }
};

// FoodOrderingSystem to manage restaurants
class FoodOrderingSystem {
private:
    unordered_map<string, Restaurant> restaurants;

public:
    // Add a restaurant
    void addRestaurant(string name) {
        if (restaurants.find(name) == restaurants.end()) {
            restaurants.emplace(name, Restaurant(name));
            cout << "🏠 Restaurant " << name << " added successfully!\n";
        } else {
            cout << "⚠️ Restaurant already exists!\n";
        }
    }

    // Add menu item to a specific restaurant
    void addMenuItem(string restaurantName, string itemName, double price) {
        if (restaurants.find(restaurantName) != restaurants.end()) {
            restaurants[restaurantName].addMenuItem(itemName, price);
        } else {
            cout << "❌ Restaurant not found!\n";
        }
    }

    // Display restaurant menu
    void displayMenu(string restaurantName) {
        if (restaurants.find(restaurantName) != restaurants.end()) {
            restaurants[restaurantName].displayMenu();
        } else {
            cout << "❌ Restaurant not found!\n";
        }
    }

    // Show all available restaurants
    void showAllRestaurants() {
        if (restaurants.empty()) {
            cout << "🚫 No restaurants available!\n";
            return;
        }
        cout << "🍽️ Available Restaurants:\n";
        for (const auto& pair : restaurants) {
            cout << "🏠 " << pair.first << endl;
        }
    }
};

// Interactive menu function
void interactiveMenu(FoodOrderingSystem &zomato) {
    int choice;
    string restaurantName, itemName;
    double price;

    do {
        cout << "\n========== Zomato Ordering System ==========\n";
        cout << "1️⃣ Add Restaurant\n";
        cout << "2️⃣ Add Menu Item\n";
        cout << "3️⃣ Show All Restaurants\n";
        cout << "4️⃣ Show Restaurant Menu\n";
        cout << "5️⃣ Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "🏠 Enter Restaurant Name: ";
                cin.ignore();
                getline(cin, restaurantName);
                zomato.addRestaurant(restaurantName);
                break;

            case 2:
                cout << "🏠 Enter Restaurant Name: ";
                cin.ignore();
                getline(cin, restaurantName);
                cout << "🍽️ Enter Dish Name: ";
                getline(cin, itemName);
                cout << "💰 Enter Price: ";
                cin >> price;
                zomato.addMenuItem(restaurantName, itemName, price);
                break;

            case 3:
                zomato.showAllRestaurants();
                break;

            case 4:
                cout << "🏠 Enter Restaurant Name: ";
                cin.ignore();
                getline(cin, restaurantName);
                zomato.displayMenu(restaurantName);
                break;

            case 5:
                cout << "🚪 Exiting system. Have a great day! 🎉\n";
                break;

            default:
                cout << "❌ Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 5);
}

int main() {
    FoodOrderingSystem zomato;
    interactiveMenu(zomato);
    return 0;
}
