#pragma once 
#include "../transport/transport_interface.h"
#include <memory>

using namespace std;
#include <iostream>

class ILogistic{
    public:
    virtual unique_ptr<ITransport> createTransport()const=0;

    void planDelivery()const{
        unique_ptr<ITransport> transport= createTransport();
        transport->delivery();
    }
    
    virtual ~ILogistic()=default;
};