#pragma once
#include "spot.h"
#include "../enum/vehicle_typ.h"
class BikeSpot :public ParkingSpot{
    public:
    BikeSpot(int id):ParkingSpot(id){}

     VehicleType getSpotType() override{
        return VehicleType::BIKE;
     };

     virtual ~BikeSpot()=default;

};