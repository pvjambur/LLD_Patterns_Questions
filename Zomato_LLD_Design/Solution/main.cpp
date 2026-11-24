#include <bits/stdc++.h>
#include "TomatoApp.h"

int main(){
    TomatoApp* app = new TomatoApp();
    
    //simulate
    User* user1 = new User("Alice", "123 Main St, New York");    

    //order
    Order* order1 = app->placeOrder(user1, nullptr, "Delivery", "123 Main St, New York", nullptr);

    //add items to cart
    Restaurant* selectedRestaurant = app->searchRestaurantsByLocation("New York")[0];
    MenuItem* item1 = new MenuItem(selectedRestaurant->getMenu()[0]);
    app->addItemToCart(user1, item1);

    //place order and pay
    PaymentStratergy* paymentMethod = new CreditCardPayment("1234-5678-9012-3456", "Alice", "12/25", "123");
    app->payForOrder(order1, paymentMethod);

    //exit
    delete app;
    delete user1;
    delete order1;
    delete selectedRestaurant;
    delete item1;
    delete paymentMethod;
    return 0;
}