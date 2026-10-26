#include <iostream>
#include <string>

class A{
public:
    void method1() {}
};

class B{
public:
    A* a;
    B() {a = new A();}
    void method2() {}
};

int main(){
    B* b = new B();
    b->method2();
    b->a->method1();
}