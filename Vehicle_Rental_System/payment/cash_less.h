#pragma once
#include<iostream>
using namespace std;
#include "payment.h"

class OnlinePayment:public Payment{
    public:
    void pay()override{
        cout<<"Online Payment Recieved, Please collect your bill..."<<endl;
    }

    virtual ~OnlinePayment()=default;
};