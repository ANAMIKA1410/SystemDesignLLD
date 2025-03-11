#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Stock class to represent a stock entity
class Stock {
public:
    string symbol;
    double price;

    Stock() {}
    Stock(string symbol, double price) : symbol(symbol), price(price) {}
};

// Trader class to represent an individual trader
class Trader {
public:
    string name;
    map<string, int> portfolio; // Stock symbol -> Quantity

    Trader() {}
    Trader(string name) : name(name) {}
    
    void buyStock(string symbol, int quantity) {
        portfolio[symbol] += quantity;
    }
    
    void sellStock(string symbol, int quantity) {
        if (portfolio[symbol] >= quantity) {
            portfolio[symbol] -= quantity;
            if (portfolio[symbol] == 0) {
                portfolio.erase(symbol);
            }
        } else {
            cout << "Not enough stocks to sell!\n";
        }
    }

    void showPortfolio() {
        cout << "Portfolio of " << name << ":\n";
        for (auto &stock : portfolio) {
            cout << stock.first << " : " << stock.second << " shares\n";
        }
    }
};

// Stock Trading Platform
class StockTradingPlatform {
private:
    map<string, Stock> stocks;
    map<string, Trader> traders;

public:
    void addStock(string symbol, double price) {
        stocks[symbol] = Stock(symbol, price);
    }
    
    void showStockPrice(string symbol) {
        if (stocks.find(symbol) != stocks.end()) {
            cout << "Stock: " << symbol << " Price: $" << stocks[symbol].price << "\n";
        } else {
            cout << "Stock not found.\n";
        }
    }
    
    void addTrader(string name) {
        traders.emplace(name, Trader(name));
    }
    
    void tradeStock(string traderName, string symbol, int quantity, bool isBuy) {
        if (traders.find(traderName) == traders.end()) {
            cout << "Trader not found!\n";
            return;
        }
        if (stocks.find(symbol) == stocks.end()) {
            cout << "Stock not found!\n";
            return;
        }
        
        if (isBuy) {
            traders[traderName].buyStock(symbol, quantity);
            cout << traderName << " bought " << quantity << " shares of " << symbol << "\n";
        } else {
            traders[traderName].sellStock(symbol, quantity);
            cout << traderName << " sold " << quantity << " shares of " << symbol << "\n";
        }
    }
    
    void showTraderPortfolio(string traderName) {
        if (traders.find(traderName) != traders.end()) {
            traders[traderName].showPortfolio();
        } else {
            cout << "Trader not found.\n";
        }
    }
};

// Interactive menu function
// void interactiveMenu() {
//     StockTradingPlatform stockPlatform;
//     int choice;
//     string symbol, traderName;
//     double price;
//     int quantity;

//     while (true) {
//         cout << "\nChoose an operation:\n";
//         cout << "1. Add Stock\n2. Show Stock Price\n3. Add Trader\n4. Buy Stock\n5. Sell Stock\n6. Show Portfolio\n7. Exit\nEnter choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1:
//                 cout << "Enter stock symbol: "; cin >> symbol;
//                 cout << "Enter stock price: "; cin >> price;
//                 stockPlatform.addStock(symbol, price);
//                 break;
//             case 2:
//                 cout << "Enter stock symbol: "; cin >> symbol;
//                 stockPlatform.showStockPrice(symbol);
//                 break;
//             case 3:
//                 cout << "Enter trader name: "; cin >> traderName;
//                 stockPlatform.addTrader(traderName);
//                 break;
//             case 4:
//                 cout << "Enter trader name: "; cin >> traderName;
//                 cout << "Enter stock symbol: "; cin >> symbol;
//                 cout << "Enter quantity: "; cin >> quantity;
//                 stockPlatform.tradeStock(traderName, symbol, quantity, true);
//                 break;
//             case 5:
//                 cout << "Enter trader name: "; cin >> traderName;
//                 cout << "Enter stock symbol: "; cin >> symbol;
//                 cout << "Enter quantity: "; cin >> quantity;
//                 stockPlatform.tradeStock(traderName, symbol, quantity, false);
//                 break;
//             case 6:
//                 cout << "Enter trader name: "; cin >> traderName;
//                 stockPlatform.showTraderPortfolio(traderName);
//                 break;
//             case 7:
//                 cout << "Exiting...\n";
//                 return;
//             default:
//                 cout << "Invalid choice, try again.\n";
//         }
//     }
// }

int main() {
    
    StockTradingPlatform stockPlatform;
    int choice;
    string symbol, traderName;
    double price;
    int quantity;

    while (true) {
        cout << "\nChoose an operation:\n";
        cout << "1. Add Stock\n2. Show Stock Price\n3. Add Trader\n4. Buy Stock\n5. Sell Stock\n6. Show Portfolio\n7. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter stock symbol: "; cin >> symbol;
                cout << "Enter stock price: "; cin >> price;
                stockPlatform.addStock(symbol, price);
                break;
            case 2:
                cout << "Enter stock symbol: "; cin >> symbol;
                stockPlatform.showStockPrice(symbol);
                break;
            case 3:
                cout << "Enter trader name: "; cin >> traderName;
                stockPlatform.addTrader(traderName);
                break;
            case 4:
                cout << "Enter trader name: "; cin >> traderName;
                cout << "Enter stock symbol: "; cin >> symbol;
                cout << "Enter quantity: "; cin >> quantity;
                stockPlatform.tradeStock(traderName, symbol, quantity, true);
                break;
            case 5:
                cout << "Enter trader name: "; cin >> traderName;
                cout << "Enter stock symbol: "; cin >> symbol;
                cout << "Enter quantity: "; cin >> quantity;
                stockPlatform.tradeStock(traderName, symbol, quantity, false);
                break;
            case 6:
                cout << "Enter trader name: "; cin >> traderName;
                stockPlatform.showTraderPortfolio(traderName);
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
