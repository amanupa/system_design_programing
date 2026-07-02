#include "strategy/BestFitStrategy.hpp"

#include <tuple>

#include "common/enums/SpotType.hpp"

namespace pms {

namespace {

/// Lower tuple = better fit. Built per candidate from the ranking rules.
std::tuple<int, int, int, int, std::string> rankKey(const Vehicle& vehicle,
                                                     const ParkingSpot& spot) {
    const int capacityGap =
        static_cast<int>(spot.capacity()) - static_cast<int>(vehicle.size());
    const int chargingWaste =
        (spot.hasCharging() && !vehicle.requiresCharging()) ? 1 : 0;
    const int premiumWaste =
        (spot.type() == SpotType::Vip && !vehicle.isPrivileged()) ? 1 : 0;
    return {capacityGap, chargingWaste, premiumWaste, spot.floorNumber(), spot.id()};
}

}  // namespace

ParkingSpot* BestFitStrategy::selectSpot(
    const Vehicle& vehicle,
    const std::vector<ParkingSpot*>& candidates) const {
    ParkingSpot* best = nullptr;
    std::tuple<int, int, int, int, std::string> bestKey;
    for (ParkingSpot* spot : candidates) {
        auto key = rankKey(vehicle, *spot);
        if (best == nullptr || key < bestKey) {
            best = spot;
            bestKey = std::move(key);
        }
    }
    return best;
}

}  // namespace pms
