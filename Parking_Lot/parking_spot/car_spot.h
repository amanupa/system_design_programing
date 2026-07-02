#pragma once
#include "spot.h"
#include "../enum/vehicle_typ.h"
class CarSpot :public ParkingSpot{
    public:
    CarSpot(int id):ParkingSpot(id){}

     VehicleType getSpotType() override{
        return VehicleType::CAR;
     };

     virtual ~CarSpot()=default;

};