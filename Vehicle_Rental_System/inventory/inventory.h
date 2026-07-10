#pragma once
#include "../vehicle/vehicle.h"
#include<memory>
#include <iostream>
#include <vector>
using namespace std;


class Inventory{
    private:
    vector<unique_ptr<Vehicle>>vehicles;
    public:
    void addVehicle(unique_ptr<Vehicle> vehicle){
        vehicles.push_back(move(vehicle));
    }
    void removeVehicle(int vehicleId){
        auto it = remove_if(
            vehicles.begin(),
            vehicles.end(),
            [&](auto& vehicle ){
                return vehicle->getVehicleId() == vehicleId;
            }
        );

        vehicles.erase(it, vehicles.end());
    }

    vector<Vehicle*> getAllVehicles(){
        vector<Vehicle*> result;

        for(auto& vehicle: vehicles)
            result.push_back(vehicle.get());

        return result;
    }
    Vehicle* getVehicle(int vehicleId){
        for(auto &vehicle: vehicles){
            if(vehicle->getVehicleId()==vehicleId){
                return vehicle.get();
            }

        }
        return nullptr;
    }

    virtual ~Inventory()=default;

};