#include <bits/stdc++.h>
#include <string>

using namespace std;

class SportCar{
private:
    //charecters
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;
    int cuurentGear;


public:
    //constructor
    SportCar(string b, string m){
        this->brand = b;
        this->model = m;
        isEngineOn = false;
        currentSpeed = 0;
        cuurentGear = 0;
    }


    //behaviors
    void startEngine() {
        isEngineOn = true;
    }

    void shiftGear(int gear) {
        cuurentGear = gear;
    }

    void accelerate() {
        if (isEngineOn) {
            currentSpeed += 10;
        }
    }

    //getters
    int getCurSpeed(){
        return currentSpeed;
    }

    //setters
    void setCurSpeed(int speed){
        currentSpeed += speed;
    }

    void brake() {
        currentSpeed = 0;
    }
};

int main(){
    SportCar* myCar = new SportCar("Ford", "Mustang");
    myCar->startEngine();
    myCar->shiftGear(2);
    myCar->accelerate();
    myCar->brake();

    // myCar->currentSpeed = 500; // This will cause a compilation error due to private access
}