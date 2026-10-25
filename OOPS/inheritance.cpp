#include <iostream>
#include <string>

using namespace std;

class Car{
protected:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string b, string m){
        this->brand = b;
        this->model = m;
        isEngineOn = false;
        currentSpeed = 0;
    }

    void startEngine(){
        isEngineOn = true;
        cout << brand << " " << model << " : Engine On" << endl;
    }

    void stopEngine(){
        isEngineOn = false;
        cout << brand << " " << model << " : Engine Off" << endl;
    }

    void accelerate(){
        currentSpeed += 20;
    }

    void brake(){
        currentSpeed -= 20;
    }

};

class ManualCar : public Car{
private:
    int gear;

public:
    ManualCar(string b, string m) : Car(b,m){
        gear = 0;
    }

    void shiftGear(int newGear){
        gear = newGear;
    }
};

class ElectricCar : public Car{
private:
    int battery;

public:
    ElectricCar(string b, string m) : Car(b,m){
        battery = 100;
    }

    void chargeBattery(int newBat){
        battery = newBat;
    }
};

int main(){
    ManualCar* myCar = new ManualCar("Suzuki","Wagonar");
    ElectricCar* mycar1 = new ElectricCar("Tesla","Model Y");
}