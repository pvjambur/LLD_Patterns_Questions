#include<iostream>
#include<string>
using namespace std;

class Student{
public:

    string name;
    double* marksPtr;

    Student (string name, double marks){
        this->name = name;
        marksPtr = new double;
        *marksPtr = marks;
    } 

    Student (Student &s){
        cout << "Copy constructor called" << endl;
        this->name = s.name;
        this->marksPtr = new double;
        *this->marksPtr = *s.marksPtr;
    }

    // Assignment operator (for deep copy)
    Student& operator=(Student &s){
        cout << "Assignment operator called" << endl;
        if(this != &s){
            this->name = s.name;
            if(this->marksPtr != NULL){
                delete this->marksPtr;
            }
            this->marksPtr = new double;
            *this->marksPtr = *s.marksPtr;
        }
        return *this;
    }

    // Destructor (to free allocated memory)
    ~Student(){
        cout << "Destructor called" << endl;
        delete marksPtr;
    }

    void getInfo(){
        cout << "Name: " << name << endl;
        cout << "Marks: " << *marksPtr << endl;
    }
};

int main(){
    Student s1("pranav", 95.5);
    s1.getInfo();
    Student s2(s1);
    *(s2.marksPtr) = 85.0; // Modifying marks through s2
    s1.getInfo();
    return 0;
}