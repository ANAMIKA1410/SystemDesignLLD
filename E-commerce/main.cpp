#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
using namespace std;

class Product{
    public:
    int productId;
    string name;
    int stock;
    float price;
    
    Product(int id,string n,int s,float p):productId(id),name(n),stock(s),price(p){}
    
      void display() {
        cout << "Product: " << name << " | Price: ₹" << price << " | Stock: " << stock << endl;
    }
};

class CartItem
{
    public:
    Product* product;
    int quantity;
    
    CartItem(Product*p,int q):product(p),quantity(q){}
    
};



class Cart{
    public:
    vector<CartItem>items;
    void addToCart(Product* product, int quantity) {
        if (product->stock < quantity) {
            cout << "Not enough stock for " << product->name << endl;
            return;
        }
        items.push_back(CartItem(product, quantity));
        cout << "Added " << quantity << " " << product->name << "(s) to cart." << endl;
    }
    
    void removeFromCart(string productName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->product->name == productName) {
                items.erase(it);
                cout << "Removed " << productName << " from cart." << endl;
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }
    double calculateTotal() {
        double total = 0;
        for (auto& item : items) {
            total += item.quantity * item.product->price;
        }
        return total;
    }
};


class Buyer
{
    public:
    int buyerId;
    string name;
    string contact;
    Cart cart;
    vector<int> orderHistory;
    
    Buyer(int id,string n,string c):buyerId(id),name(n),contact(c){}
};


class Order{
    public:
    int orderId;
    int buyerId;
    vector<CartItem> items;
   double totalAmount;
    string status;
    
    Order(int id, int bId, vector<CartItem> cartItems, double total) : orderId(id), buyerId(bId), items(cartItems), totalAmount(total) {
        status = "Processing";
    }

    void displayOrder() {
        cout << "Order #" << orderId << " | Status: " << status << " | Total: ₹" << totalAmount << endl;
    }
};

class EcommerceSystem {
public:
    vector<Product*> products;
    unordered_map<int, Buyer*> buyers;
    vector<Order*> orders;
    int orderCounter = 1;

    void addProduct(int id, string name, int stock, float price) {
        products.push_back(new Product(id, name, stock, price));
    }

    void updateStock(int id, int stock) {
        for (auto& product : products) {
            if (product->productId == id) {
                product->stock = stock;
                return;
            }
        }
    }

    void checkInventory(int id) {
        for (auto& product : products) {
            if (product->productId == id) {
                product->display();
                return;
            }
        }
        cout << "Product not found!" << endl;
    }

    void addBuyer(int id, string name, string contact) {
        buyers[id] = new Buyer(id, name, contact);
    }

    void getBuyer(int id) {
        if (buyers.find(id) != buyers.end()) {
            cout << "Buyer Name: " << buyers[id]->name << ", Contact: " << buyers[id]->contact << endl;
        } else {
            cout << "Buyer not found!" << endl;
        }
    }

    void addOrder(int buyerId) {
        if (buyers.find(buyerId) == buyers.end()) {
            cout << "Buyer not found!" << endl;
            return;
        }
        Buyer* buyer = buyers[buyerId];
        if (buyer->cart.items.empty()) {
            cout << "Cart is empty. Add items first." << endl;
            return;
        }
        double total = buyer->cart.calculateTotal();
        orders.push_back(new Order(orderCounter++, buyerId, buyer->cart.items, total));
        buyer->orderHistory.push_back(orderCounter - 1);
        for (auto& item : buyer->cart.items) {
            item.product->stock -= item.quantity;
        }
        buyer->cart.items.clear();
        cout << "Order placed successfully!" << endl;
    }

    void getOrder(int id) {
        for (auto& order : orders) {
            if (order->orderId == id) {
                order->displayOrder();
                return;
            }
        }
        cout << "Order not found!" << endl;
    }
};

int main() {
    EcommerceSystem system;
    system.addProduct(1, "Laptop", 10, 50000);
    system.addProduct(2, "Phone", 15, 20000);
    system.addProduct(3, "Headphones", 20, 2000);
    system.addBuyer(1, "Anamika", "9876543210");
    system.addBuyer(2, "John", "1234567890");

    int choice, userId, productId, quantity;
    while (true) {
        cout << "\n1. Check Inventory\n2. Add to Cart\n3. Remove from Cart\n4. Place Order\n5. View Orders\n6. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter product ID: ";
                cin >> productId;
                system.checkInventory(productId);
                break;
            case 2:
                cout << "Enter buyer ID and product ID, quantity: ";
                cin >> userId >> productId >> quantity;
                if (system.buyers.find(userId) != system.buyers.end()) {
                    system.buyers[userId]->cart.addToCart(system.products[productId - 1], quantity);
                }
                break;
            case 3:
            {
                cout << "Enter buyer ID and product name to remove: ";
                cin >> userId;
                string prodName;
                cin >> prodName;
                if (system.buyers.find(userId) != system.buyers.end()) {
                    system.buyers[userId]->cart.removeFromCart(prodName);
                }
                break;
            }
            case 4:
                {cout << "Enter buyer ID: ";
                cin >> userId;
                system.addOrder(userId);
                break;}
            case 5:
                {cout << "Enter order ID: ";
                cin >> productId;
                system.getOrder(productId);
                break;}
            case 6:
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}


















