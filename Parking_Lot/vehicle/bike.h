#pragma once 
#include "vehicle_interface.h"

class Bike : public Vehicle{
    public:
    Bike(string number):Vehicle(number,VehicleType::BIKE){}

    virtual ~Bike()=default;
};