#pragma once

#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/// Compact spot for small/medium vehicles. No charging.
class CompactSpot final : public ParkingSpot {
public:
    CompactSpot(std::string id, int floorNumber)
        : ParkingSpot(std::move(id), floorNumber, SpotType::Compact,
                      VehicleSize::Medium, /*hasCharging=*/false) {}
};

}  // namespace pms
