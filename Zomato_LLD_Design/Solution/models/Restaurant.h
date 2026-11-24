#ifndef RESTAURANT_H
#define RESTAURANT_H

//ifndef means "if not defined". It is a preprocessor directive used to prevent multiple inclusions of the same header file in a C++ program. When the header file is included for the first time, the macro RESTAURANT_H is not defined, so the code between #ifndef and #endif is included. If the header file is included again, the macro RESTAURANT_H will already be defined, and the code will be skipped, preventing redefinition errors.

#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"
using namespace std;

class Restaurant {
private:
    static int nextRestaurantId;
    int restaurantId;
    string name;
    string location;
    vector<MenuItem> menu;

public:
    Restaurant(const string& name, const string& location){
        this->name = name;
        this->location = location;
        this->restaurantId = ++nextRestaurantId;
    }

    ~Restaurant(){
        cout << "Destroyed Restaurant " << name << " and cleared menu" << endl;
        menu.clear();
    }

    //getters and setters

    string getName() const{
        return name;
    }

    void setName(const string& n){
        name = n;
    }

    string getLocation() const{
        return location;
    }

    void setLocation(const string& l){
        location = l;
    }

    void addMenuItem(const MenuItem& item){
        menu.push_back(item);
    }

    const vector<MenuItem>& getMenu() const{
        return menu;
    }



};

int Restaurant::nextRestaurantId = 0;
//the above line initializes the static member variable nextRestaurantId to 0. This variable is shared among all instances of the Restaurant class and is used to assign unique IDs to each restaurant.

#endif // RESTAURANT_H