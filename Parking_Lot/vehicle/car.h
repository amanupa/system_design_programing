#pragma once 
#include "vehicle_interface.h"

class Car : public Vehicle{
    public:
    Car(string number):Vehicle(number,VehicleType::CAR){}

    virtual ~Car()=default;
};