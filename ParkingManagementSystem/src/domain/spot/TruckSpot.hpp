#pragma once

#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/// Oversized spot for trucks (Large capacity). No charging.
class TruckSpot final : public ParkingSpot {
public:
    TruckSpot(std::string id, int floorNumber)
        : ParkingSpot(std::move(id), floorNumber, SpotType::Truck,
                      VehicleSize::Large, /*hasCharging=*/false) {}
};

}  // namespace pms
