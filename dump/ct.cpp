#include<iostream>
#include<string>
using namespace std;

class Print{
public:
    void show(int x){
        cout << "Integer: " << x << endl;   

    }

    void show(string s){
        cout << "String: " << s << endl;   

    }
};

class Parent{
    public:
    virtual void show(){
        cout << "Parent class" << endl;
    }
};

class Child : public Parent{
    public:
    void show(){
        cout << "Child class" << endl;
    }
};

int main(){
    Print p;
    p.show(5);
    p.show("Hello");
    Parent c1;   
    c1.show();
    
    Child c2;
    c2.show();
    return 0;
}