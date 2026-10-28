#include<bits/stdc++.h>
using namespace std;

class DepositOnlyAccount{
public:
    virtual void deposit(double ammount) = 0;
};

class WithdrawAccount: public DepositOnlyAccount{
public:
    virtual void withdraw(double ammount) = 0;
};

class SavingAccount: public WithdrawAccount{
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

class CurrentAccount: public WithdrawAccount{
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

class FDAccount: public DepositOnlyAccount{
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
    vector<DepositOnlyAccount*> account1;
    vector<WithdrawAccount*> account2;

public:
    BankClient(vector<DepositOnlyAccount*> accounts1, vector<WithdrawAccount*> accounts2){
        this->account1 = accounts1;
        this->account2 = accounts2;
    }

    void proccesTransaction(){
        for (DepositOnlyAccount* acc: account1){
            acc->deposit(1000);
        }

        for (WithdrawAccount* acc: account2){
            acc->deposit(1000);
            acc->withdraw(500);
        }
    }
};

int main(){
    vector<WithdrawAccount*> accounts_a;
    vector<DepositOnlyAccount*> accounts_b;
    accounts_a.push_back(new SavingAccount());
    accounts_a.push_back(new CurrentAccount());
    accounts_b.push_back(new FDAccount());

    BankClient* bc = new BankClient(accounts_b,accounts_a);
    bc->proccesTransaction();

    return 0;
}



