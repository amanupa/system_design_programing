#pragma once
using namespace std;
#include<string>
#include "../enum/vehicle_typ.h"


class Vehicle{
    private:
    string vehicleNumber;
    VehicleType vType;

    public:
    Vehicle(string vNo, VehicleType type): vehicleNumber(vNo), vType(type){}

    string getVehicleNumber() const{
        return vehicleNumber;
    }

    VehicleType getVehicleType()const{
        return vType;
    }
    virtual ~Vehicle()=default;

};