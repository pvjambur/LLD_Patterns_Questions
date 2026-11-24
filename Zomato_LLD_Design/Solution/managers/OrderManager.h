#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <bits/stdc++.h>
#include "../models/Order.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickUpOrder.h"
#include "../models/User.h"
#include "../models/Restaurant.h"
#include "../stratergies/PaymentStratergy.h"
#include "../utils/TimeUtils.h"
using namespace std;

class OrderManager{
private:
    vector<Order*> orders;
    static OrderManager* instance;
    OrderManager();


public:
    static OrderManager* getInstance(){
        if (!instance){
            instance = new OrderManager();
        }
        return instance;
    }
    

    void addOrder(Order* order){
        orders.push_back(order);
    }

    void removeOrder(Order* order){
        bool flag = false;
        for (auto it = orders.begin(); it != orders.end(); ++it){
            if (*it == order){
                orders.erase(it);
                flag = true;
                break;
            }
        }
        if (!flag){
            cout << "Order not found" << endl;
        }
    }

    const vector<Order*>& getOrders() const{
        return orders;
    }

};

OrderManager* OrderManager::instance = nullptr;
#endif //ORDER_MANAGER_H