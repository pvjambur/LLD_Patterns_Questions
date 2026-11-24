#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include <bits/stdc++.h>
#include "../models/Order.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickUpOrder.h"
#include "../models/User.h"
using namespace std;

class OrderFactory{
public:
    static Order* createOrder(const string& orderType, Restaurant* rest, User* usr, const string& addrOrLoc){
        if (orderType == "Delivery"){
            return new DeliveryOrder(rest, usr, addrOrLoc);
        } else if (orderType == "PickUp"){
            return new PickUpOrder(rest, usr, addrOrLoc);
        } else {
            throw invalid_argument("Invalid order type");
        }
    }

};

#endif // ORDER_FACTORY_H