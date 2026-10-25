#include <iostream>
#include <string>

using namespace std;

class Car{
protected:
    int curSpeed;
    bool engineOn;
    string brand,model;

public:
    Car(string b, string m){
        this->brand = b;
        this->model = m;
        engineOn = false;
        curSpeed = 0;
    }

    virtual void accelerate() = 0;
    virtual void accelerate(int speed) = 0;
    virtual void brake() = 0;
    virtual ~Car() {}

    void start(){
        engineOn = true;
        cout << brand << " " << model << " : Engine On!!" << endl;
    }

    void stop(){
        engineOn = false;
        cout << brand << " " << model << " : Engine Off!!" << endl;
    }
};

class ManualCar : public Car{
private:
    int gear;

public:
    ManualCar(string b, string m) : Car(b,m){
        gear = 0;
    }
    //overidding
    void accelerate(){
        curSpeed += 20;
    }
    //overloading
    void accelerate(int speed){
        curSpeed += speed;
    }

    void shiftGear(int newGear){
        gear = newGear;
    }

    void brake(){
        curSpeed -= 20;
    }
};

int main(){
    ManualCar* myCar = new ManualCar("A","B");
    myCar->start();
    myCar->accelerate();
    myCar->shiftGear(3);
    myCar->stop();
}