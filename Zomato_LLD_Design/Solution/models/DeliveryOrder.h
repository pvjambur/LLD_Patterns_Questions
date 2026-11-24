#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H

#include "Order.h"
#include <bits/stdc++.h>
using namespace std;

class DeliveryOrder : public Order{
private:
    string deliveryAddress;

public:
    DeliveryOrder(Restaurant* rest, User* usr, const string& addr) : Order(rest, usr){
        this->deliveryAddress = addr;
    }

    void setDeliveryAddress(const string& addr){
        this->deliveryAddress = addr;
    }

    string getDeliveryAddress() const{
        return deliveryAddress;
    }

    void placeOrder() override{
        if (items.empty()){
            throw runtime_error("Cannot place order with no items");
        }
        if (!paymentMethod){
            throw runtime_error("Payment method not set");
        }
        paymentMethod->pay(total);
        cout << "Delivery Order placed successfully at " << orderTime << " to address: " << deliveryAddress << endl;
    }

};


#endif // DELIVERY_ORDER_H