#pragma once

#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/// Accessible spot (Medium capacity) reserved for permit holders. The reservation
/// (permit checking) is allocation policy handled by the Strategy in Phase 4; the
/// spot itself only models the physical footprint.
class HandicappedSpot final : public ParkingSpot {
public:
    HandicappedSpot(std::string id, int floorNumber)
        : ParkingSpot(std::move(id), floorNumber, SpotType::Handicapped,
                      VehicleSize::Medium, /*hasCharging=*/false) {}
};

}  // namespace pms
