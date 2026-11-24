#ifndef PAY_STRAT_H
#define PAY_STRAT_H

#include <bits/stdc++.h>
using namespace std;


class PaymentStratergy{

public:
    virtual void pay(double ammount) = 0; //pure virtual function -> abstract class


};

class CreditCardPayment : public PaymentStratergy{
private:
    string cardNumber;
    string cardHolderName;
    string expiryDate;
    string cvv;

public:
    CreditCardPayment(const string& cardNumber, const string& cardHolderName, const string& expiryDate, const string& cvv){
        
        this->cardNumber = cardNumber;
        this->cardHolderName = cardHolderName;
        this->expiryDate = expiryDate;
        this->cvv = cvv;
    }

    void pay(double ammount) override{
        cout << "Paid " << ammount << " using Credit card " << cardNumber << endl;
    }

};

class UPIPayment : public PaymentStratergy{
private:
    string upiId;

public:
    UPIPayment(const string& upiId){
        this->upiId = upiId;
    }

    void pay(double ammount) override{
        cout << "Paid " << ammount << " using UPI " << upiId << endl;
    }

};

class NetBankingPayment : public PaymentStratergy{
private:
    string bankName;
    string accountNumber;
    string ifscCode;

public:
    NetBankingPayment(const string& bankName, const string& accountNumber, const string& ifscCode){
        this->bankName = bankName;
        this->accountNumber = accountNumber;
        this->ifscCode = ifscCode;
    }

    void pay(double ammount) override{
        cout << "Paid " << ammount << " using Net Banking from " << bankName << endl;
    }
};


#endif //PAY_STRAT_H