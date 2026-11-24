#ifndef PICKUP_ORDER_H
#define PICKUP_ORDER_H

#include "Order.h"
#include <bits/stdc++.h>
using namespace std;

class PickUpOrder : public Order{
private:
    string pickUpLocation;

public:
    PickUpOrder(Restaurant* rest, User* usr, const string& loc) : Order(rest, usr){
        this->pickUpLocation = loc;
    }

    void setPickUpLocation(const string& loc){
        this->pickUpLocation = loc;
    }

    string getPickUpLocation() const{
        return pickUpLocation;
    }

    void placeOrder() override{
        if (items.empty()){
            throw runtime_error("Cannot place order with no items");
        }
        if (!paymentMethod){
            throw runtime_error("Payment method not set");
        }
        paymentMethod->pay(total);
        cout << "Pick Up Order placed successfully at " << orderTime << " from location: " << pickUpLocation << endl;
    }

};

#endif // PICKUP_ORDER_H