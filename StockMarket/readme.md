# the Stock Trading System:

### Stock Class<br/>

- Represents a stock with a unique symbol and price.<br/>
- Attributes:<br/>
- symbol: The stock's identifier (e.g., "AAPL").<br/>
- price: The current price of the stock.<br/>
- Constructor: Initializes stock attributes.<br/>
- Trader Class<br/>

## Represents a trader who buys and sells stocks.
Attributes:<br/>
- name: Trader's name.<br/>
- portfolio: A map storing stock symbols and their respective quantities owned by the trader.
##### Methods:<br/>
- buyStock(symbol, quantity): Adds stocks to the trader's portfolio.<br/>
- sellStock(symbol, quantity): Removes stocks from the portfolio if enough shares are available.<br/>
- showPortfolio(): Displays the stocks owned by the trader.<br/>
- StockTradingPlatform Class<br/>

## Manages stocks and traders, allowing trading activities.
Attributes:
- stocks: A map of stock symbols to Stock objects.
- traders: A map of trader names to Trader objects.
Methods:
- addStock(symbol, price): Adds a new stock to the platform.
- showStockPrice(symbol): Displays the price of a stock.
- addTrader(name): Adds a new trader to the platform.
- tradeStock(traderName, symbol, quantity, isBuy): Executes a buy or sell order for a trader.
- showTraderPortfolio(traderName): Displays a trader's portfolio.


## Choose an operation:
1. Add Stock
2. Show Stock Price
3. Add Trader
4. Buy Stock
5. Sell Stock
6. Show Portfolio
7. Exit
Enter choice: 
