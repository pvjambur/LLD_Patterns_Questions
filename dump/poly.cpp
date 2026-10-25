#include<iostream>
#include<string>

using namespace std;

class Student{
public:
string name;

Student(){
    cout << "non-parama constructor called" << endl;
}

Student(string name){
    this->name = name;
    cout << "parama constructor called" << endl;
}
};

int main(){
    Student s1("pranav");
    return 0;
}