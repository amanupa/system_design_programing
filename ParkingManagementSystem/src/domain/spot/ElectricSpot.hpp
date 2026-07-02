#pragma once

#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/// Medium spot equipped with a charging point. Fits EVs (and non-EVs, which
/// simply won't charge — the base canFit already permits that).
class ElectricSpot final : public ParkingSpot {
public:
    ElectricSpot(std::string id, int floorNumber)
        : ParkingSpot(std::move(id), floorNumber, SpotType::Electric,
                      VehicleSize::Medium, /*hasCharging=*/true) {}
};

}  // namespace pms
