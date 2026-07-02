#pragma once

#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/// Smallest spot; only Small vehicles (bikes) fit. No charging.
class BikeSpot final : public ParkingSpot {
public:
    BikeSpot(std::string id, int floorNumber)
        : ParkingSpot(std::move(id), floorNumber, SpotType::Bike,
                      VehicleSize::Small, /*hasCharging=*/false) {}
};

}  // namespace pms
