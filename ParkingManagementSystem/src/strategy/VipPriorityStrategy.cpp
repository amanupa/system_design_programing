#include "strategy/VipPriorityStrategy.hpp"

#include <utility>

#include "common/enums/SpotType.hpp"
#include "common/exceptions/ParkingException.hpp"

namespace pms {

namespace {

std::vector<ParkingSpot*> filterVip(const std::vector<ParkingSpot*>& spots,
                                    bool keepVip) {
    std::vector<ParkingSpot*> result;
    result.reserve(spots.size());
    for (ParkingSpot* spot : spots) {
        const bool isVip = spot->type() == SpotType::Vip;
        if (isVip == keepVip) {
            result.push_back(spot);
        }
    }
    return result;
}

}  // namespace

VipPriorityStrategy::VipPriorityStrategy(
    std::unique_ptr<ISpotAllocationStrategy> inner)
    : inner_(std::move(inner)) {
    if (!inner_) {
        throw InvalidArgumentException("VipPriorityStrategy: inner strategy is null");
    }
}

ParkingSpot* VipPriorityStrategy::selectSpot(
    const Vehicle& vehicle,
    const std::vector<ParkingSpot*>& candidates) const {
    if (vehicle.isPrivileged()) {
        // Give VIPs first claim on VIP spots; otherwise let them use anything.
        const std::vector<ParkingSpot*> vipSpots = filterVip(candidates, /*keepVip=*/true);
        if (!vipSpots.empty()) {
            return inner_->selectSpot(vehicle, vipSpots);
        }
        return inner_->selectSpot(vehicle, candidates);
    }
    // Ordinary vehicles never consume a reserved VIP spot.
    const std::vector<ParkingSpot*> nonVip = filterVip(candidates, /*keepVip=*/false);
    return inner_->selectSpot(vehicle, nonVip);
}

std::string VipPriorityStrategy::name() const {
    return "VipPriority(" + inner_->name() + ")";
}

}  // namespace pms
