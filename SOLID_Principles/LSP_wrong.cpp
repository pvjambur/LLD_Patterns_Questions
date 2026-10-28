#include<bits/stdc++.h>
using namespace std;

class Account{
public:
    virtual void deposit(double ammount) = 0;
    virtual void withdraw(double ammount) = 0;
};

class SavingAccount: public Account{
private:
    double balance;

public:
    SavingAccount(){
        balance = 0.0;
    }

    void deposit(double ammount){
        balance += ammount;
        cout << "Current balance: " << balance << endl;
    }

    void withdraw(double ammount){
        if (ammount>balance){
            cout << "Insuffecient funds" << endl;
        }
        else{
            balance -= ammount;
            cout << "Current balance: " << balance << endl;
        }
    }
};

class CurrentAccount: public Account{
private:
    double balance;

public:
    CurrentAccount(){
        balance = 0.0;
    }

    void deposit(double ammount){
        balance += ammount;
        cout << "Current balance: " << balance << endl;
    }

    void withdraw(double ammount){
        if (ammount>balance){
            cout << "Insuffecient funds" << endl;
        }
        else{
            balance -= ammount;
            cout << "Current balance: " << balance << endl;
        }
    }
};

class FDAccount: public Account{
private:
    double balance;

public:
    FDAccount(){
        balance = 0.0;
    }

    void deposit(double ammount){
        balance += ammount;
        cout << "Current balance: " << balance << endl;
    }

    void withdraw(double ammount){
        throw logic_error("Cannot withdraw");
    }
};

class BankClient{
private:
    vector<Account*> account;

public:
    BankClient(vector<Account*> accounts){
        this->account = accounts;
    }

    void proccesTransaction(){
        for (Account* acc: account){
            acc->deposit(1000);

            try{
                acc->withdraw(500);
            }
            catch (const logic_error& e){
                cout << "Exception: " << e.what() << endl;
            }
        }
    }
};

int main(){
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FDAccount());

    BankClient* bc = new BankClient(accounts);
    bc->proccesTransaction();

    return 0;
}



