# Key Classes and Responsibilities:
User → Represents a customer.<br/>
Account → Stores user’s account details.<br/>
Transaction → Records deposits, withdrawals, and transfers.<br/>
Bank → Manages all accounts and transactions.<br/>



# Class Diagram:

User<br/>
 ├── name: string<br/>
 ├── accounts: list<Account><br/>
 ├── createAccount(bank, initialDeposit)<br/>
 │<br/>


Account<br/>
 ├── accountNumber: string<br/>
 ├── balance: double<br/>
 ├── deposit(amount)<br/>
 ├── withdraw(amount)<br/>
 ├── transfer(toAccount, amount)<br/>
 │<br/>
 
Transaction<br/>
 ├── fromAccount: Account<br/>
 ├── toAccount: Account<br/>
 ├── amount: double<br/>
 ├── type: Deposit/Withdraw/Transfer<br/>
 │<br/>
Bank<br/>
 ├── users: list<User><br/>
 ├── accounts: list<Account><br/>
 ├── createAccount(user, initialDeposit)<br/>
 ├── processTransaction(transaction)<br/>


 # Output

 choose an action:
1. Create Account
2. Deposit
3. Withdraw
4. Check Balance
5. Exit
1
Enter account Number :123
Enter intial Deposit : 12
Acoount created for Alice with balance 12

choose an action:
1. Create Account
2. Deposit
3. Withdraw
4. Check Balance
5. Exit
2
Enter account Number :123
Enter deposit amount : 12
Deposited 12 . New Balance :24
