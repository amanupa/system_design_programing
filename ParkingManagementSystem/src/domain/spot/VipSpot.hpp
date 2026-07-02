#pragma once

#include "domain/spot/ParkingSpot.hpp"

namespace pms {

/// Premium spot (Large + charging). Physically open to any vehicle; *who is
/// allowed* to use it (VIP-only access) is allocation policy decided by the
/// Strategy in Phase 4, deliberately kept out of this entity.
class VipSpot final : public ParkingSpot {
public:
    VipSpot(std::string id, int floorNumber)
        : ParkingSpot(std::move(id), floorNumber, SpotType::Vip,
                      VehicleSize::Large, /*hasCharging=*/true) {}
};

}  // namespace pms
