#include<iostream>
#include<string>

using namespace std;

class Person{
public:
    string name;
    int age;

    Person (string name,int age){
        this->name = name;
        this->age = age;
    }

    Person(){
        cout << "Parent" << endl;
    }

};

class Student : public Person{
public:
    int rollNo;
    string researchTopic;

    Student() : Person(){
        this->rollNo = 0;
        cout << "Child" << endl;
    }

    Student(string name, int age, int rollNo) : Person(name, age){
        this->rollNo = rollNo;
        cout << "Child" << endl;
    }

    void getInfo(){
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Roll No: " << rollNo << endl;
    }
};

class gradStudent: public Student{
    string researchTopic;
};

//multiple inherticne

class TA : public Student, public Teacher{
    string researchTopic;
};

int main(){
    Student s1;
    s1.name = "pranav";
    s1.age = 20;
    s1.rollNo = 101;
    s1.researchTopic = "AI";
    s1.getInfo();
    cout << s1.researchTopic << endl;
    return 0;
}