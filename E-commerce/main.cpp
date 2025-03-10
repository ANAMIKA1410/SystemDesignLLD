#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Product {
public:
    int id;
    string name;
    double price;
    int stock;

    Product(int id, string name, double price, int stock)
        : id(id), name(name), price(price), stock(stock) {}

    void display() {
        cout << "🛍️ " << name << " (₹" << price << ") - Stock: " << stock << endl;
    }
};

class CartItem {
public:
    Product* product;
    int quantity;

    CartItem(Product* p, int qty) : product(p), quantity(qty) {}
};

class Cart {
public:
    vector<CartItem> items;

    void addToCart(Product* product, int quantity) {
        if (product->stock < quantity) {
            cout << "❌ Not enough stock for " << product->name << endl;
            return;
        }
        items.push_back(CartItem(product, quantity));
        cout << "✅ Added " << quantity << " " << product->name << "(s) to cart.\n";
    }

    void removeFromCart(string productName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->product->name == productName) {
                items.erase(it);
                cout << "🛑 Removed " << productName << " from cart.\n";
                return;
            }
        }
        cout << "⚠️ Product not found in cart.\n";
    }

    double calculateTotal() {
        double total = 0;
        for (auto& item : items) {
            total += item.quantity * item.product->price;
        }
        return total;
    }
};

class Order {
public:
    static int orderCounter;
    int orderId;
    vector<CartItem> items;
    double totalAmount;
    string status;

    Order(vector<CartItem> cartItems, double total)
        : items(cartItems), totalAmount(total) {
        orderId = ++orderCounter;
        status = "Processing";
    }

    void displayOrder() {
        cout << "📦 Order #" << orderId << " | Status: " << status << " | Total: ₹" << totalAmount << endl;
    }
};
int Order::orderCounter = 0;

class User {
public:
    string username;
    Cart cart;
    vector<Order> orderHistory;

    User(string name) : username(name) {}

    void placeOrder() {
        if (cart.items.empty()) {
            cout << "⚠️ Cart is empty. Add items first.\n";
            return;
        }
        double total = cart.calculateTotal();
        orderHistory.push_back(Order(cart.items, total));

        for (auto& item : cart.items) {
            item.product->stock -= item.quantity;
        }

        cart.items.clear();
        cout << "✅ Order placed successfully!\n";
    }

    void viewOrders() {
        if (orderHistory.empty()) {
            cout << "📭 No orders placed yet.\n";
            return;
        }
        cout << "🛒 Order History:\n";
        for (auto& order : orderHistory) {
            order.displayOrder();
        }
    }
};

class ECommerce {
public:
    unordered_map<string, User*> users;
    unordered_map<int, Product*> products;

    void addUser(string username) {
        if (users.find(username) == users.end()) {
            users[username] = new User(username);
            cout << "👤 User \"" << username << "\" registered!\n";
        }
    }

    void addProduct(int id, string name, double price, int stock) {
        products[id] = new Product(id, name, price, stock);
    }

    void browseProducts() {
        cout << "\n🛍️ Available Products:\n";
        for (auto& p : products) {
            p.second->display();
        }
    }
};

// Main function
int main() {
    ECommerce store;

    store.addUser("Anamika");
    store.addUser("John");

    store.addProduct(1, "Laptop", 50000, 10);
    store.addProduct(2, "Phone", 20000, 15);
    store.addProduct(3, "Headphones", 2000, 20);

    store.browseProducts();

    User* user = store.users["Anamika"];
    user->cart.addToCart(store.products[1], 1);
    user->cart.addToCart(store.products[2], 2);
    user->cart.removeFromCart("Laptop");

    user->placeOrder();
    user->viewOrders();

    return 0;
}
