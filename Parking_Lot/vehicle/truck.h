#pragma once 
#include "vehicle_interface.h"

class Truck : public Vehicle{
    public:
    Truck(string number):Vehicle(number,VehicleType::TRUCK){}

    virtual ~Truck()=default;
};