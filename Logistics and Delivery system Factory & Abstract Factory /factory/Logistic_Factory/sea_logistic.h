#pragma once 
#include "../transport/transport_interface.h"
#include "../transport/ship_transport.h"
#include "logistic.h"
#include <iostream>
#include <memory>
using namespace std;

class SeaLogistic : public ILogistic {
    public:
    unique_ptr<ITransport> createTransport() const override{
        return make_unique<Ship>();
    }
    virtual ~SeaLogistic()=default;


};