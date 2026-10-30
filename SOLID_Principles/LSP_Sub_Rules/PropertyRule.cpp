#include <bits/stdc++.h>
using namespace std;

class Account{
private:
    int balance = 0;
    //Rule 1-> balance cannot be zero

public:
    Account(int ammt){
        this->balance = ammt;
    }

    void checkBalance(){
        if (balance<0){
            throw runtime_error("Negative balance");
        }
    }

    virtual void deposit(int ammt) = 0;
    virtual void withdraw(int ammt) = 0;
};

class myAccount: public Account{
private:
    int balance = 0;

public:
    myAccount(int ammt) : Account(ammt){
        this->balance = ammt;
    }

    void deposit(int ammt){
        balance += ammt;
    }

    void withdraw(int ammt){
        if (ammt>balance){
            throw out_of_range("Balance cannot be negative");
        }
        balance -= ammt;
    }


};

int main(){
    myAccount* mc = new myAccount(1000);
    mc->deposit(133);
    mc->withdraw(20000);
}
