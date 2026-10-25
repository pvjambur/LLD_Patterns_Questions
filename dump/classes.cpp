#include <iostream>
#include <string>
using namespace std;

class Teacher{
private:
    double salary;

public:
Teacher(string name, string dept, string subject, double salary){
    this->name = name;
    this->dept = dept;
    this->subject = subject;
    this->salary = salary;

}
/*
Teacher(string n, string d, string s, double sal){
    name = n;
    dept = d;
    subject = s;
salary = sal;


}
*/

Teacher (Teacher &t){
    cout << "Copy constructor called" << endl;
    this->name = t.name;
    this->dept = t.dept;
    this->subject = t.subject;
    this->salary = t.salary;
}

    string name;
    string dept;
    string subject;

    void changeDept(string newDept){
        dept = newDept;
    }

    void setSalary(double s){
        salary = s;
    }

    double getSalary(){
        return salary;
    }
};

class Student{
    public:
    string name;
    int rollNo;
};

int main(){
    Teacher t1("pranav", "CSE", "DSA", 50000);
    Teacher t2(t1);

    cout << t1.name << endl;
    cout << t1.getSalary() << endl;
    cout << t2.name << endl;
    cout << t2.getSalary() << endl;
    return 0;
}
