#pragma once
#include <iostream>
#include "transport_interface.h"
using namespace std;


class Truck : public ITransport{
    public:
    void delivery() override{
        cout<<"Delivery by road logistic using truck"<<endl;
    }

    virtual ~Truck()=default;

};
