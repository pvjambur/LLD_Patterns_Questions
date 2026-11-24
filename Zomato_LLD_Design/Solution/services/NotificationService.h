#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVCE_H

#include "../models/User.h"
#include "../models/Order.h"
#include <bits/stdc++.h>
using namespace std;


class NotifcationService{
public:
    NotifcationService(){
        cout << "Notification Service Initialized" << endl;
    }

    static void sendNotification(User* user, Order* order){
        cout << "Notification sent to user " << user->getName() << " for order " << order->getOrderId() << endl;
    }
};

#endif // NOTIFCAITON SERVICE_H