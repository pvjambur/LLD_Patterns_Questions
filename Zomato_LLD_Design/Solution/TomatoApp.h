#ifndef TOMATO_APP_H
#define TOMATO_APP_H

#include <bits/stdc++.h>
#include "models/User.h"
#include "models/Restaurant.h"
#include "models/MenuItem.h"
#include "models/Cart.h"
#include "managers/RestaurantManager.h"
#include "managers/OrderManager.h"
#include "stratergies/PaymentStratergy.h"
#include "factories/OrderFactory.h"
#include "factories/NowOrderFactory.h"
#include "factories/ScheduleOrderFactory.h"
#include "services/NotificationService.h"
using namespace std;


class TomatoApp{
public:
    TomatoApp(){
        initializeRestaurants();
    }

    void initializeRestaurants(){
        Restaurant* r1 = new Restaurant("PizzaHut", "New York");
        r1->addMenuItem(MenuItem("PZ001", "Pepperoni Pizza", 12.99));
        r1->addMenuItem(MenuItem("PZ002", "Margherita Pizza", 10.99));
        r1->addMenuItem(MenuItem("PZ003", "BBQ Chicken Pizza", 14.99));

        Restaurant* r2 = new Restaurant("SushiWorld", "San Francisco");
        r2->addMenuItem(MenuItem("SU001", "California Roll", 8.99));
        r2->addMenuItem(MenuItem("SU002", "Spicy Tuna Roll", 9.99));
        r2->addMenuItem(MenuItem("SU003", "Dragon Roll", 11.99));

        RestaurantManager::getInstance()->addRestaurant(r1);
        RestaurantManager::getInstance()->addRestaurant(r2);
    }

    vector<Restaurant*> searchRestaurantsByLocation(const string& location){
        return RestaurantManager::getInstance()->searchByLoc(location);
    }

    void selectRestaurant(Restaurant* restaurant){
        cout << "Selected Restaurant: " << restaurant->getName() << endl;
        const vector<MenuItem>& menu = restaurant->getMenu();
        cout << "Menu:" << endl;
        for (const auto& item : menu){
            cout << item.getCode() << " - " << item.getName() << " - $" << item.getPrice() << endl;
        }
    }

    void addItemToCart(User* user, MenuItem* item){
        user->getCart()->addItem(item);
        cout << "Added " << item->getName() << " to cart. Total: $" << user->getCart()->getTotal() << endl;
    }

    Order* placeOrder(User* user, Restaurant* restaurant, const string& orderType, const string& addrOrLoc, PaymentStratergy* paymentMethod){
        Order* order = OrderFactory::createOrder(orderType, restaurant, user, addrOrLoc);
        for (auto item : user->getCart()->getCartItems()){
            order->addItem(item);
        }
        order->setPaymentMethod(paymentMethod);
        order->placeOrder();
        OrderManager::getInstance()->addOrder(order);
        user->getCart()->clearCart();
        return order;
    }

    Order* placeNowOrder(User* user, Restaurant* restaurant, const string& orderType, const string& addrOrLoc, PaymentStratergy* paymentMethod){
        Order* order = NowOrderFactory::createOrder(orderType, restaurant, user, addrOrLoc);
        for (auto item : user->getCart()->getCartItems()){
            order->addItem(item);
        }
        order->setPaymentMethod(paymentMethod);
        order->placeOrder();
        OrderManager::getInstance()->addOrder(order);
        user->getCart()->clearCart();
        return order;
    }

    Order* placeScheduledOrder(User* user, Restaurant* restaurant, const string& orderType, const string& addrOrLoc, PaymentStratergy* paymentMethod){
        Order* order = ScheduleOrderFactory::createOrder(orderType, restaurant, user, addrOrLoc);
        for (auto item : user->getCart()->getCartItems()){
            order->addItem(item);
        }
        order->setPaymentMethod(paymentMethod);
        order->placeOrder();
        OrderManager::getInstance()->addOrder(order);
        user->getCart()->clearCart();
        return order;
    }

    void payForOrder(Order* order, PaymentStratergy* paymentMethod){
        order->setPaymentMethod(paymentMethod);
        order->placeOrder();
        NotifcationService::sendNotification(order->getUser(), order);
    }

};



#endif // TOMATO_APP_H
