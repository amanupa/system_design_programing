#pragma once 
#include<iostream>
#include "logistic.h"
#include "../transport/transport_interface.h"
#include "../transport/truck_transport.h"
#include <memory>
using namespace std;

class RoadLogidtic : public ILogistic{
    public:
    unique_ptr<ITransport> createTransport() const override{
        return make_unique<Truck>();
    }
    virtual ~RoadLogidtic() =default;

};