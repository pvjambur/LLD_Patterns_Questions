#include<iostream>
#include<string>
using namespace std;

void fun(){
    static int count = 0; // Static variable to keep track of the count
    count++;
    cout << "Function called " << count << " times" << endl;
}

class A{
    public:
    static int x;

    void incX(){
        x = x + 1;
    }
};

// Initialize static member variable
int A::x = 0;

int main(){
    fun();
    fun();
    fun();

    A a1, a2;
    a1.x = 5;
    a2.x = 10;

    cout << "a1.x: " << a1.x << endl; // Output: 5
    cout << "a2.x: " << a2.x << endl; // Output: 10

    a1.incX();
    cout << "After incrementing a1.x:" << endl;
    cout << "a1.x: " << a1.x << endl; // Output: 6
    cout << "a2.x: " << a2.x << endl; // Output: 10 (unchanged)

    return 0;
}