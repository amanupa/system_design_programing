#pragma once 
#include "../parking_spot/spot.h"
#include "../enum/vehicle_typ.h"
#include<vector>
using namespace std;

class ParkingFloor{
    private: 
    int floorNumber;
    vector<ParkingSpot*>parkingSpots;
    public:
    ParkingFloor(int num):floorNumber(num){}
    void addSpot(ParkingSpot* spot){
        parkingSpots.push_back(spot);
    }
    ParkingSpot* getAvailableSpots(VehicleType type){
        for(auto spot: parkingSpots){
            if(!spot->isOccupied() && spot->getSpotType()==type ){
                return spot;
            }
        }
        return nullptr;
    }
    int getFloorNumber(){
        return floorNumber;
    }

}