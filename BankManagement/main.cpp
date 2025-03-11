#include <iostream>
#include <vector>
#include <unordered_map>
#include<string>
#include <limits> // For numeric_limits

using namespace std;

class Account
{
    public:
    string accountNumber;
    double balance;
    
    Account(string accNum, double intialBalance):accountNumber(accNum),balance(intialBalance){}
    
    void deposit(double amount)
    {
        balance+=amount;
        cout<<"Deposited "<<amount<<" . New Balance :"<<balance<<endl;
    }
    bool withdraw(double amount)
    {
        if(balance>=amount)
        {
            balance-=amount;
            cout<<"Withdrew "<<amount<<" . New Balance : "<< balance<<endl;
            return true;
        }
        else{
            cout<<"Insufficient balance! "<<endl;
            return false;
        }
    }
    
};

class User
{
    public:
    string name;
    vector<Account*>accounts;
    
    User(string n):name(n){}
    
    void createAccount(string accNum, double initialDeposit)
    {
        Account* acc=new Account(accNum,initialDeposit);
        accounts.push_back(acc);
        cout<<"Acoount created for "<<name<<" with balance "<<initialDeposit<<endl;
    }
    Account*getAccount(string accNum)
    {
        for(Account*acc:accounts)
        {
            if(acc->accountNumber==accNum)
            {
                return acc;
            }
        }
        return nullptr;
    }
    
};

class Bank{
    public:
    unordered_map<string,Account*>accounts;
    
    void addAccount(Account* account)
    {
        accounts[account->accountNumber]=account;
    }
    Account* getAccount(string accNum)
    {
        return accounts.count(accNum)? accounts[accNum]:nullptr;
    }
};


int main()
{
    Bank bank;
    User alice("Alice");
    
    while(true){
        cout<<"\nchoose an action:\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Exit\n";
        
        int choice;
        cin>>choice;
        
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input, please enter a number \n";
            continue;
        }
        switch(choice)
        {
            case 1:
            {
                string accNum;
                double initialDeposit;
                cout<<"Enter account Number :";
                cin>>accNum;
                cout<<"Enter intial Deposit : ";
                cin>>initialDeposit;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout<<"Invalid input for deposit amount"<<endl;
                    break;
                }
                alice.createAccount(accNum,initialDeposit);
                bank.addAccount(alice.getAccount(accNum));
                break;
            }
            case 2:
            {
                string accNum;
                double amount;
                cout<<"Enter account Number :";
                cin>>accNum;
                cout<<"Enter deposit amount : ";
                cin>>amount;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout<<"Invalid input for deposit amount "<<endl;
                    break;
                }
                Account* acc=bank.getAccount(accNum);
                if(acc)
                {
                    acc->deposit(amount);
                }
                else{
                    cout<<"Account not found "<<endl;
                }
                break;
            }
            
            case 3:
            {
                string accNum;
                double amount;
                cout << "Enter account number: ";
                cin >> accNum;
                cout << "Enter withdrawal amount: ";
                cin >> amount; 
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout<<"Invalid input for amount withdraw "<<endl;
                    break;
                }
                Account* acc=bank.getAccount(accNum);
                if(acc)
                {
                    acc->withdraw(amount);
                }
                else
                {
                    cout<<"Account not found \n";
                }
                break;
            }
            
            case 4:
            {
            string accNum;
            cout<<"Enter account Number :";
            cin>>accNum;
            Account* acc=bank.getAccount(accNum);
            if(acc)
            {
                cout << "Account Balance: " << acc->balance << endl;
            }
            else {
                    cout << "Account not found.\n";
                }
            break;
            }
            case 5:
            {
                cout<<"EXIT... "<<endl;
                return 0;
            }
            default:
            cout<<"Invalid choice please try again "<<endl;
        }
        
    }
    return 0;
}


















