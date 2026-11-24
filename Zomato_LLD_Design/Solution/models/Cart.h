#ifndef CART_H
#define CART_H

#include <bits/stdc++.h>
#include "MenuItem.h"

class Cart{
private:
    vector<MenuItem*> items;
    static int nextCartId;
    double total;

public:
    Cart(){
        this->total = 0.0;
    }

    ~Cart(){
        cout << "Destoyed Cart" << endl;
    }

    void addItem(MenuItem* item){
        items.push_back(item);
        total += item->getPrice();
    }

    void removeItem(MenuItem* item){
        bool flag = false;
        for (auto it = items.begin(); it != items.end(); ++it){
            if (*it == item){
                total -= item->getPrice();
                items.erase(it);
                flag = true;
                break;
            }
        }
        if (!flag){
            cout << "Item not found in cart" << endl;
        }
    }

    void clearCart(){
        items.clear();
        total = 0.0;
    }

    bool isEmpty() const{
        return items.empty();
    }

    //we use const after a method to indicate that this method does not modify the state of the object. It can be called on const instances of the class.

    double getTotal() const{
        return total;
    }
};

int Cart::nextCartId = 0;

#endif //CART_H
