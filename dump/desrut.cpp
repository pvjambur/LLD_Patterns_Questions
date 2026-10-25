#include<iostream>
#include<string>
using namespace std;

class Student{
public:
    string name;
    double* cgpaPtr;

    Student(string name, double cgpa){
        this->name = name;
        cgpaPtr = new double;
        *cgpaPtr = cgpa;
    }

    ~Student(){
        cout << "Hi, I deleted everything" << endl;
        delete cgpaPtr;
    }

    void getInfo(){
        cout << "Name: " << name << endl;
        cout << "CGPA: " << *cgpaPtr << endl;
    }   
};

int main(){
    Student s1{"pranav", 9.5};
    s1.getInfo();
    return 0;
}