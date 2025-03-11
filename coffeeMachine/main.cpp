#include <iostream>
#include <unordered_map>
#include <memory>

using namespace std;

// Coffee types
enum class CoffeeType { ESPRESSO, CAPPUCCINO, LATTE };

// Strategy Pattern: Base class for different coffee brewing strategies
class CoffeeStrategy {
public:
    virtual void brew() = 0;
    virtual ~CoffeeStrategy() {}
};

// Concrete Strategies for Coffee Types
class Espresso : public CoffeeStrategy {
public:
    void brew() override { cout << "Brewing a strong Espresso!\n"; }
};

class Cappuccino : public CoffeeStrategy {
public:
    void brew() override { cout << "Brewing a creamy Cappuccino!\n"; }
};

class Latte : public CoffeeStrategy {
public:
    void brew() override { cout << "Brewing a smooth Latte!\n"; }
};

// Factory Pattern: Coffee Factory
class CoffeeFactory {
public:
    static unique_ptr<CoffeeStrategy> createCoffee(CoffeeType type) {
        switch (type) {
            case CoffeeType::ESPRESSO: return make_unique<Espresso>();
            case CoffeeType::CAPPUCCINO: return make_unique<Cappuccino>();
            case CoffeeType::LATTE: return make_unique<Latte>();
            default: return nullptr;
        }
    }
};

// Singleton Pattern: Coffee Machine
class CoffeeMachine {
private:
    static CoffeeMachine* instance;
    unordered_map<string, int> ingredients;

    // Private constructor
    CoffeeMachine() {
        ingredients["Water"] = 1000;  // in ml
        ingredients["Coffee"] = 500;  // in grams
        ingredients["Milk"] = 800;    // in ml
    }

public:
    // Get Singleton Instance
    static CoffeeMachine* getInstance() {
        if (!instance) instance = new CoffeeMachine();
        return instance;
    }

    // Display Ingredient Levels
    void displayIngredients() {
        cout << "\n--- Ingredients Status ---\n";
        for (const auto& item : ingredients) {
            cout << item.first << ": " << item.second << "\n";
        }
    }

    // Brew Coffee
    void brewCoffee(CoffeeType type) {
        if (ingredients["Water"] < 50 || ingredients["Coffee"] < 20) {
            cout << "Not enough ingredients! Please refill.\n";
            return;
        }

        auto coffee = CoffeeFactory::createCoffee(type);
        coffee->brew();

        // Reduce Ingredients
        ingredients["Water"] -= 50;
        ingredients["Coffee"] -= 20;
        if (type != CoffeeType::ESPRESSO) ingredients["Milk"] -= 30;
    }

    // Refill Ingredients
    void refill() {
        ingredients["Water"] = 1000;
        ingredients["Coffee"] = 500;
        ingredients["Milk"] = 800;
        cout << "Ingredients refilled!\n";
    }
};

// Define static instance
CoffeeMachine* CoffeeMachine::instance = nullptr;

// Main function
int main() {
    CoffeeMachine* machine = CoffeeMachine::getInstance();
    int choice;

    while (true) {
        cout << "\n1. Brew Espresso\n2. Brew Cappuccino\n3. Brew Latte\n4. Show Ingredients\n5. Refill Ingredients\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: machine->brewCoffee(CoffeeType::ESPRESSO); break;
            case 2: machine->brewCoffee(CoffeeType::CAPPUCCINO); break;
            case 3: machine->brewCoffee(CoffeeType::LATTE); break;
            case 4: machine->displayIngredients(); break;
            case 5: machine->refill(); break;
            case 6: return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
