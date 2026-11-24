#ifndef ORDER_H
#define ORDER_H

#include <bits/stdc++.h>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "TimeUtils.h"
#include "../stratergies/PaymentStratergy.h"
using namespace std;

class Order{
protected:
    int orderId;
    static int nextOrderId;
    vector<MenuItem*> items;
    Restaurant* restaurant;
    User* user;
    double total;
    string orderTime;
    PaymentStratergy* paymentMethod;
    string orderType;

public:
    Order(Restaurant* rest, User* usr){
        this->restaurant = rest;
        this->user = usr;
        this->orderId = ++nextOrderId;
        this->total = 0.0;
        this->orderTime = TimeUtils::getCurrentTime();
        this->paymentMethod = nullptr;
        this->orderType = "Delivery";
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
            cout << "Item not found in order" << endl;
        }
    }

    int getOrderId() const{
        return orderId;
    }

    void setPaymentMethod(PaymentStratergy* method){
        //i want to list the available payment options only, there are only three options, so i will check if the method is one of them, if not, i will throw an error
        if (dynamic_cast<CreditCardPayment*>(method) || dynamic_cast<UPIPayment*>(method) || dynamic_cast<NetBankingPayment*>(method)){
            this->paymentMethod = method;
        } else {
            throw invalid_argument("Invalid payment method");
        }

    }

    void changeRestaurant(Restaurant* newRestaurant){
        this->restaurant = newRestaurant;
        this->items.clear();
        this->total = 0.0;
    }

    void changeOrderType(const string& newType){
        if (newType == "Delivery" || newType == "Pickup"){
            this->orderType = newType;
        } else {
            throw invalid_argument("Invalid order type");
        }
    }

    virtual void placeOrder(){
        if (items.empty()){
            throw runtime_error("Cannot place order with no items");
        }
        if (!paymentMethod){
            throw runtime_error("Payment method not set");
        }
        paymentMethod->pay(total);
        cout << "Order placed successfully at " << orderTime << endl;
    }

    virtual string getOrderType(){
        return orderType;
    }

    User* getUser() const{
        return user;
    }

};

int Order::nextOrderId = 0;

#endif // ORDER_H