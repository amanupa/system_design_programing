#pragma once
#include "../location/location.h"
#include<vector>
#include<iostream>
#include <memory>
using namespace std;

class VehicleRentalSystem {

private:

    vector<unique_ptr<Location>> locations;


public:

    void addLocation(unique_ptr<Location> location)
    {
        locations.push_back(move(location));
    }


    vector<unique_ptr<Location>>& getLocations()
    {
        return locations;
    }

};