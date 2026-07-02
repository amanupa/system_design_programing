#pragma once

#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/// Large spot that accommodates any size (SUVs, vans). No charging.
class LargeSpot final : public ParkingSpot {
public:
    LargeSpot(std::string id, int floorNumber)
        : ParkingSpot(std::move(id), floorNumber, SpotType::Large,
                      VehicleSize::Large, /*hasCharging=*/false) {}
};

}  // namespace pms
