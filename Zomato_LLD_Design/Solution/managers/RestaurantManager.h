#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include <bits/stdc++.h>
#include "../models/Restaurant.h"

class RestaurantManager{
private:
    vector<Restaurant*> restaurants;
    static RestaurantManager* instance;

public:
    static RestaurantManager* getInstance(){
        if (!instance){
            instance = new RestaurantManager();
        }
        return instance;
    }

    void addRestaurant(Restaurant* restaurant){
        restaurants.push_back(restaurant);
    }

    vector<Restaurant*> searchByLoc(const string& location){
        vector<Restaurant*> res;
        for (auto r: restaurants){
            if (r->getLocation() == location){
                res.push_back(r);
            }
        }
        return res;
    }



};

RestaurantManager* RestaurantManager::instance = nullptr;


#endif //RESTAURANT_MANAGER_H
