#pragma once
#include<iostream>
using namespace std;
#include "payment.h"

class CashPayment:public Payment{
    public:
    void pay()override{
        cout<<"Cash Payment Recieved, Please collect your bill..."<<endl;
    }

    virtual ~CashPayment()=default;
};