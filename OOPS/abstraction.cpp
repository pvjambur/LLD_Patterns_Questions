#include <iostream>
#include <string>

using namespace std;

class Car{
public:

    virtual void startEngine() = 0;
    virtual void shiftGear(int gear) = 0;
    virtual void accelerate() = 0;
    virtual void brake() = 0;
    virtual ~Car() {}

};

class SportsCar : public Car {
public:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;
    int cuurentGear;

    SportsCar(string b, string m){
        this->brand = b;
        this->model = m;
        isEngineOn = false;
        currentSpeed = 0;
        cuurentGear = 0;
    }

    void startEngine() override {
        isEngineOn = true;
    }

    void shiftGear(int gear) override {
        cuurentGear = gear;
    }

    void accelerate() override {
        if (isEngineOn) {
            currentSpeed += 10;
        }
    }

    void brake() override {
        currentSpeed = 0;
    }
};

int main(){
    Car* myCar = new SportsCar("Ford","Mustang");
}