#pragma once

#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/// Standard car spot (Medium capacity). No charging.
class CarSpot final : public ParkingSpot {
public:
    CarSpot(std::string id, int floorNumber)
        : ParkingSpot(std::move(id), floorNumber, SpotType::Car,
                      VehicleSize::Medium, /*hasCharging=*/false) {}
};

}  // namespace pms
