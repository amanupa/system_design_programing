#pragma once
#include "../vehicle/vehicle_interface.h"

class ParkingSpot{
    private:
    int spotId;
    bool occupied;
    Vehicle* vehicle;

    public:
    ParkingSpot(int id):spotId(id),occupied(false),vehicle(nullptr){}
    void parkVehicle(Vehicle* v){
        this->vehicle=v;
        this->occupied=true;
    }

    void removeVehicle(){
        this->vehicle=nullptr;
        this->occupied=false;

    }
    int getSpotId()const{
        return spotId;
    }
    bool isOccupied()const{
        return occupied;
    }
    virtual VehicleType getSpotType() = 0;

    virtual ~ParkingSpot()=default;

};