#include<iostream>
#include<string>
using namespace std;

class Account{


private:
    string password;
    double balance; //data hiding

public:
//non parameterized constructor
Account(){
    cout << "Hi, I am bank" << endl;
    accountid = "1234";
}
    string username;
    string accountid;
};

int main(){
    Account n;
    n.username = "pranav";

    cout << n.username << endl;
    cout << n.accountid << endl; 
    return 0;

}