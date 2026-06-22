#pragma once 
using namespace std;
#include<iostream>
#include "transport_interface.h"

class Ship : public ITransport{
    public:
    void delivery() override{
        cout<<"Delivery by Sea Logistic using ship"<<endl;
    }

    virtual ~Ship()=default;
};