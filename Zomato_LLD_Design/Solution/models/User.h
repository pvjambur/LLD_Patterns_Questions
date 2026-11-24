#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
#include "Cart.h"
using namespace std;

class User{
private:
    static int nextuserId;
    int userId;
    string name;
    string addr;
    Cart* cart;

public:
    User(const string& name, const string& addr){
        this->name = name;
        this->addr = addr;
        this->userId = ++nextuserId;
        this->cart = new Cart();
    }

    ~User(){
        cout << "Destroyed User " << name << endl;
        if (cart){
            delete cart;
            cart = nullptr;
        }
    }

    string getName() const{
        return name;
    }

    void setName(const string& n){
        name = n;
    }

    string getAddr() const{
        return addr;
    }

    void setAddr(const string& a){
        addr = a;
    }

    Cart* getCart() const{
        return cart;
    }


};

int User::nextuserId = 0;


#endif // USER_H