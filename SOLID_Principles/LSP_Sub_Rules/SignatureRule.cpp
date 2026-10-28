#include <bits/stdc++.h>
using namespace std;


//Mehtod - argument rule
class P{
    void solve(string s) {}
};

class C: public P{
private: 
    P* p;
public:
    C(P* p1){
        this->p = p1;
    }

    void solve(string s, string a) {}
}; 

// Return-type rule

class Animal{

};

class Dog: public Animal{

};

class client{
    Dog name(Dog d){
        return d;
    }

    Animal nam1e(Dog d){
        return d;
    }
};

//Excpetion-rule

class A{
public:
    virtual void getValue() noexcept(false){
        throw logic_error("Parent error");
    }
};

class B: public A{
    void getValue() noexcept(false){
        throw out_of_range("Child error");
    }
};

class cust{
private:
    A* a;
public:
    cust(A* a){
        this->a = a;
    }

    void takeValue(){
        try{
            a->getValue();
        }
        catch (const logic_error& e){
            cout << "logic error: " << e.what() << endl;
        }
    }
};

