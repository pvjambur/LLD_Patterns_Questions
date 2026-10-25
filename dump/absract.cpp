#include<iostream>
#include<string>
using namespace std;

class Shape{
    virtual void draw() = 0;
};

class circle: public Shape{
    public:
    void draw(){
        cout << "Drawing a circle" << endl;
    }
};  

int main(){
    circle c;
    c.draw();
    return 0;
}