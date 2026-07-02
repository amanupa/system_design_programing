#pragma once
#include "spot.h"
#include "../enum/vehicle_typ.h"
class TruckSpot :public ParkingSpot{
    public:
    TruckSpot(int id):ParkingSpot(id){}

     VehicleType getSpotType() override{
        return VehicleType::TRUCK;
     };

     virtual ~TruckSpot()=default;

};